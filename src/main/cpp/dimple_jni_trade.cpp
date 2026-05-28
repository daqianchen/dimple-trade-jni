#include "dimple_jni_trade.h"

#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

using std::string;

// 交易 SDK 中文字段通常使用 GBK；固定 936 避免受系统 ACP 影响。
static UINT sdkCodePage() {
    static UINT cp = 0;
    if (cp != 0) {
        return cp;
    }
    const char* v = std::getenv("DIMPLE_JNI_CODEPAGE");
    if (v && *v) {
        char* end = nullptr;
        unsigned long parsed = std::strtoul(v, &end, 10);
        if (end != v && parsed > 0 && parsed <= 65535UL) {
            cp = static_cast<UINT>(parsed);
            return cp;
        }
    }
    cp = 936;
    return cp;
}

// 粗略判断字节序列是否是有效 UTF-8。
static bool isLikelyUtf8(const char* value) {
    if (!value) {
        return false;
    }
    const unsigned char* s = reinterpret_cast<const unsigned char*>(value);
    while (*s) {
        if (*s <= 0x7F) {
            ++s;
            continue;
        }
        if ((*s & 0xE0) == 0xC0) {
            if ((s[1] & 0xC0) != 0x80 || (*s & 0xFE) == 0xC0) {
                return false;
            }
            s += 2;
            continue;
        }
        if ((*s & 0xF0) == 0xE0) {
            if ((s[1] & 0xC0) != 0x80 || (s[2] & 0xC0) != 0x80) {
                return false;
            }
            if (*s == 0xE0 && s[1] < 0xA0) {
                return false;
            }
            if (*s == 0xED && s[1] >= 0xA0) {
                return false;
            }
            s += 3;
            continue;
        }
        if ((*s & 0xF8) == 0xF0) {
            if ((s[1] & 0xC0) != 0x80 || (s[2] & 0xC0) != 0x80 || (s[3] & 0xC0) != 0x80) {
                return false;
            }
            if (*s == 0xF0 && s[1] < 0x90) {
                return false;
            }
            if (*s > 0xF4 || (*s == 0xF4 && s[1] > 0x8F)) {
                return false;
            }
            s += 4;
            continue;
        }
        return false;
    }
    return true;
}

static bool charsetDebugEnabled() {
    static int enabled = -1;
    if (enabled == -1) {
        const char* p = std::getenv("DIMPLE_JNI_CHARSET_DEBUG");
        if (p && p[0] == '1') {
            enabled = 1;
            return true;
        }
        const char* v = std::getenv("DIMPLE_JNI_CHARSET_DEBUG");
        enabled = (v && v[0] == '1') ? 1 : 0;
    }
    return enabled == 1;
}

static bool preferUtf8Decode() {
    static int enabled = -1;
    if (enabled == -1) {
        const char* v = std::getenv("DIMPLE_JNI_PREFER_UTF8");
        enabled = (!v || v[0] != '0') ? 1 : 0;
    }
    return enabled == 1;
}

static void logCharset(const char* msg) {
    if (!charsetDebugEnabled() || !msg) {
        return;
    }
#ifdef _WIN32
    OutputDebugStringA(msg);
#endif
    std::fputs(msg, stderr);
    std::fflush(stderr);
}

static void logBytesHex(const char* tag, const char* value, size_t maxBytes) {
    if (!charsetDebugEnabled() || !value) {
        return;
    }
    const unsigned char* p = reinterpret_cast<const unsigned char*>(value);
    char buf[2048];
    int n = std::snprintf(buf, sizeof(buf), "[jni-charset] %s bytes:", tag);
    for (size_t i = 0; i < maxBytes && p[i] != 0 && n > 0 && n < static_cast<int>(sizeof(buf)) - 4; ++i) {
        n += std::snprintf(buf + n, sizeof(buf) - n, " %02X", p[i]);
    }
    std::snprintf(buf + (n > 0 ? n : 0), sizeof(buf) - (n > 0 ? n : 0), "\n");
    std::fputs(buf, stdout);
    std::fflush(stdout);
}

// 将 SDK 本地编码字符串转换为 Java String。
static jstring localCharsToJString(JNIEnv* env, const char* value) {
    if (!value || value[0] == '\0') {
        return env->NewStringUTF("");
    }
#ifdef _WIN32
    logBytesHex("incoming", value, 96);
    if (preferUtf8Decode() && isLikelyUtf8(value)) {
        if (charsetDebugEnabled()) {
            logCharset("[jni-charset] decode-path=UTF8(preferred)\n");
        }
        return env->NewStringUTF(value);
    }
    UINT cp = sdkCodePage();
    if (charsetDebugEnabled()) {
        char msg[128];
        std::snprintf(msg, sizeof(msg), "[jni-charset] decode-path=CP(%u)\n", cp);
        logCharset(msg);
    }
    int wideLen = MultiByteToWideChar(cp, 0, value, -1, nullptr, 0);
    if (wideLen <= 0) {
        // 回退系统代码页，兼容极少数非 GBK 环境。
        wideLen = MultiByteToWideChar(CP_ACP, 0, value, -1, nullptr, 0);
        if (wideLen <= 0) {
            return env->NewStringUTF("");
        }
        std::vector<wchar_t> wideBuffer(static_cast<size_t>(wideLen));
        MultiByteToWideChar(CP_ACP, 0, value, -1, wideBuffer.data(), wideLen);
        return env->NewString(reinterpret_cast<const jchar*>(wideBuffer.data()), wideLen - 1);
    }
    std::vector<wchar_t> wideBuffer(static_cast<size_t>(wideLen));
    MultiByteToWideChar(cp, 0, value, -1, wideBuffer.data(), wideLen);
    return env->NewString(reinterpret_cast<const jchar*>(wideBuffer.data()), wideLen - 1);
#else
    return env->NewStringUTF(value);
#endif
}

// 将 Java String 转换为 SDK 期望的本地编码字符串。
static string jStringToLocalChars(JNIEnv* env, jstring value) {
    if (!value) {
        return "";
    }
#ifdef _WIN32
    UINT cp = sdkCodePage();
    if (charsetDebugEnabled()) {
        char msg[128];
        std::snprintf(msg, sizeof(msg), "[jni-charset] encode-path=CP(%u)\n", cp);
        logCharset(msg);
    }
    const jchar* raw = env->GetStringChars(value, nullptr);
    if (!raw) {
        return "";
    }
    jsize jlen = env->GetStringLength(value);
    int localLen = WideCharToMultiByte(
            cp,
            0,
            reinterpret_cast<LPCWCH>(raw),
            static_cast<int>(jlen),
            nullptr,
            0,
            nullptr,
            nullptr);
    string result;
    if (localLen > 0) {
        result.resize(static_cast<size_t>(localLen));
        WideCharToMultiByte(
                cp,
                0,
                reinterpret_cast<LPCWCH>(raw),
                static_cast<int>(jlen),
                &result[0],
                localLen,
                nullptr,
                nullptr);
    } else {
        // 回退系统代码页，尽量避免请求中文丢失。
        localLen = WideCharToMultiByte(
                CP_ACP,
                0,
                reinterpret_cast<LPCWCH>(raw),
                static_cast<int>(jlen),
                nullptr,
                0,
                nullptr,
                nullptr);
        if (localLen > 0) {
            result.resize(static_cast<size_t>(localLen));
            WideCharToMultiByte(
                    CP_ACP,
                    0,
                    reinterpret_cast<LPCWCH>(raw),
                    static_cast<int>(jlen),
                    &result[0],
                    localLen,
                    nullptr,
                    nullptr);
        }
    }
    env->ReleaseStringChars(value, raw);
    return result;
#else
    const char* chars = env->GetStringUTFChars(value, nullptr);
    string result = chars ? chars : "";
    if (chars) {
        env->ReleaseStringUTFChars(value, chars);
    }
    return result;
#endif
}

// 由于 SDK 回调数据通常由底层线程持有，这里做一份堆内存拷贝，
// 交给 JNI 工作线程异步消费，避免回调返回后出现悬空指针。
template <typename T>
static T* copyData(const T* source) {
    if (!source) {
        return nullptr;
    }
    T* dest = static_cast<T*>(malloc(sizeof(T)));
    if (dest) {
        memcpy(dest, source, sizeof(T));
    }
    return dest;
}

// 兼容 Spring Boot fat jar 等类加载环境，优先从当前 Java 对象的 ClassLoader 中找类。
static jclass loadClassInContext(JNIEnv* env, jobject apiInstance, const char* classNameWithSlash) {
    string classNameDots = classNameWithSlash;
    std::replace(classNameDots.begin(), classNameDots.end(), '/', '.');

    jclass apiClass = env->GetObjectClass(apiInstance);
    jclass classClass = env->FindClass("java/lang/Class");
    jmethodID getClassLoader = env->GetMethodID(classClass, "getClassLoader", "()Ljava/lang/ClassLoader;");
    jobject classLoader = env->CallObjectMethod(apiClass, getClassLoader);

    jclass result = nullptr;
    if (classLoader) {
        jclass classLoaderClass = env->FindClass("java/lang/ClassLoader");
        jmethodID loadClass = env->GetMethodID(classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");
        jstring className = env->NewStringUTF(classNameDots.c_str());
        result = static_cast<jclass>(env->CallObjectMethod(classLoader, loadClass, className));
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
            result = nullptr;
        }
        env->DeleteLocalRef(className);
        env->DeleteLocalRef(classLoaderClass);
    }

    if (!result) {
        result = env->FindClass(classNameWithSlash);
        if (env->ExceptionCheck()) {
            env->ExceptionClear();
            result = nullptr;
        }
    }

    env->DeleteLocalRef(apiClass);
    env->DeleteLocalRef(classClass);
    if (classLoader) {
        env->DeleteLocalRef(classLoader);
    }
    return result;
}

// jstring -> 本地编码 string
static string getJString(JNIEnv* env, jstring value) {
    return jStringToLocalChars(env, value);
}

// 从 Java 对象中读取 String 字段。
static string getObjectStringField(JNIEnv* env, jobject object, const char* name) {
    jclass cls = env->GetObjectClass(object);
    jfieldID field = env->GetFieldID(cls, name, "Ljava/lang/String;");
    jstring value = static_cast<jstring>(env->GetObjectField(object, field));
    string result = getJString(env, value);
    if (value) {
        env->DeleteLocalRef(value);
    }
    env->DeleteLocalRef(cls);
    return result;
}

// 从 Java 对象中读取 int 字段。
static jint getObjectIntField(JNIEnv* env, jobject object, const char* name) {
    jclass cls = env->GetObjectClass(object);
    jfieldID field = env->GetFieldID(cls, name, "I");
    jint value = env->GetIntField(object, field);
    env->DeleteLocalRef(cls);
    return value;
}

// 从 Java 对象中读取 long 字段。
static jlong getObjectLongField(JNIEnv* env, jobject object, const char* name) {
    jclass cls = env->GetObjectClass(object);
    jfieldID field = env->GetFieldID(cls, name, "J");
    jlong value = env->GetLongField(object, field);
    env->DeleteLocalRef(cls);
    return value;
}

// 从 Java 对象中读取 double 字段。
static jdouble getObjectDoubleField(JNIEnv* env, jobject object, const char* name) {
    jclass cls = env->GetObjectClass(object);
    jfieldID field = env->GetFieldID(cls, name, "D");
    jdouble value = env->GetDoubleField(object, field);
    env->DeleteLocalRef(cls);
    return value;
}

// 安全写入 C 风格字符数组，确保末尾有 0。
static void copyToCharArray(char* target, size_t size, const string& value) {
    if (!target || size == 0) {
        return;
    }
    memset(target, 0, size);
    strncpy(target, value.c_str(), size - 1);
}

// 统一给 Java 对象写 String 字段。
static void setStringField(JNIEnv* env, jobject object, const char* name, const char* value) {
    jclass cls = env->GetObjectClass(object);
    jfieldID field = env->GetFieldID(cls, name, "Ljava/lang/String;");
    jstring text = localCharsToJString(env, value);
    env->SetObjectField(object, field, text);
    env->DeleteLocalRef(text);
    env->DeleteLocalRef(cls);
}

// 统一给 Java 对象写 int 字段。
static void setIntField(JNIEnv* env, jobject object, const char* name, jint value) {
    jclass cls = env->GetObjectClass(object);
    jfieldID field = env->GetFieldID(cls, name, "I");
    env->SetIntField(object, field, value);
    env->DeleteLocalRef(cls);
}

// 统一给 Java 对象写 long 字段。
static void setLongField(JNIEnv* env, jobject object, const char* name, jlong value) {
    jclass cls = env->GetObjectClass(object);
    jfieldID field = env->GetFieldID(cls, name, "J");
    env->SetLongField(object, field, value);
    env->DeleteLocalRef(cls);
}

// 统一给 Java 对象写 double 字段。
static void setDoubleField(JNIEnv* env, jobject object, const char* name, jdouble value) {
    jclass cls = env->GetObjectClass(object);
    jfieldID field = env->GetFieldID(cls, name, "D");
    env->SetDoubleField(object, field, value);
    env->DeleteLocalRef(cls);
}

// 通过默认无参构造创建 Java DTO。
static jobject newObject(JNIEnv* env, jobject apiInstance, const char* className) {
    jclass cls = loadClassInContext(env, apiInstance, className);
    if (!cls) {
        return nullptr;
    }
    jmethodID ctor = env->GetMethodID(cls, "<init>", "()V");
    jobject obj = env->NewObject(cls, ctor);
    env->DeleteLocalRef(cls);
    return obj;
}

// C++ 的响应错误结构 -> Java KsdRspInfo
static jobject makeRspInfo(JNIEnv* env, jobject apiInstance, const CKSD_RspInfoField* info) {
    if (!info) {
        return nullptr;
    }
    jobject obj = newObject(env, apiInstance, "com/dimple/trade/struct/KsdRspInfo");
    if (!obj) {
        return nullptr;
    }
    setIntField(env, obj, "errorID", info->ErrCode);
    setStringField(env, obj, "errorMsg", info->RspMsg);
    setStringField(env, obj, "timeStamp", info->TimeStamp);
    return obj;
}

JniTradeApi::JniTradeApi(JavaVM* jvm, jobject javaObj)
        : api_(nullptr), jvm_(jvm), javaObj_(nullptr), worker_(nullptr), active_(false) {
    JNIEnv* env = nullptr;
    if (jvm_->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) == JNI_OK) {
        // 保存 Java API 对象的全局引用，避免被 GC 回收。
        javaObj_ = env->NewGlobalRef(javaObj);
    }
}

JniTradeApi::~JniTradeApi() {
    // 析构时先停工作线程，再释放 Java 全局引用。
    stopThread();
    JNIEnv* env = nullptr;
    bool attached = false;
    if (jvm_->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        jvm_->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr);
        attached = true;
    }
    if (javaObj_) {
        env->DeleteGlobalRef(javaObj_);
        javaObj_ = nullptr;
    }
    if (attached) {
        jvm_->DetachCurrentThread();
    }
}

void JniTradeApi::createApi() {
    api_ = CKSDTradeApi::CreateKSDTradeApi();
    if (api_) {
        // 创建成功后立即注册 SPI，并启动专门的 JNI 事件派发线程。
        api_->RegisterSpi(this);
        startThread();
    }
}

void JniTradeApi::init() {
    if (api_) {
        api_->Init(true);
    }
}

void JniTradeApi::release() {
    if (api_) {
        api_->Release();
        api_ = nullptr;
    }
}

void JniTradeApi::join() {
    if (api_) {
        api_->Join();
    }
}

int JniTradeApi::registerServer(char* ip, int port) {
    if (!api_) {
        return -1;
    }
    api_->RegisterServer(ip, port);
    return 0;
}

int JniTradeApi::subscribePrivateFlow() {
    return api_ ? api_->SubscribePrivateFlow(false) : -1;
}

int JniTradeApi::subscribePublicFlow() {
    return api_ ? api_->SubscribePublicFlow(false) : -1;
}

int JniTradeApi::reqTraderLogin(CKSD_ReqTradeLoginField* req) {
    return api_ ? api_->ReqTraderLogin(req) : -1;
}

int JniTradeApi::reqTraderEncLogin(CKSD_ReqEncTradeLoginField* req) {
    return api_ ? api_->ReqTraderEncLogin(req) : -1;
}

int JniTradeApi::reqTraderLogout(CKSD_ReqTradeLogoutField* req) {
    return api_ ? api_->ReqTraderLogout(req) : -1;
}

int JniTradeApi::reqTraderQryPosi(unsigned int* seqNo, CKSD_ReqTraderQryPosi* req) {
    return api_ ? api_->ReqTraderQryPosi(seqNo, req) : -1;
}

int JniTradeApi::reqTraderQryMoney(unsigned int* seqNo, CKSD_ReqTraderQryMoney* req) {
    return api_ ? api_->ReqTraderQryMoney(seqNo, req) : -1;
}

int JniTradeApi::reqTraderPosiAllQry(unsigned int* seqNo, CKSD_ReqTraderPosiAllQry* req) {
    return api_ ? api_->ReqTraderPosiAllQry(seqNo, req) : -1;
}

int JniTradeApi::reqTraderQryStorage(unsigned int* seqNo, CKSD_ReqTraderQryStorage* req) {
    return api_ ? api_->ReqTraderQryStorage(seqNo, req) : -1;
}

int JniTradeApi::reqOrderAllQry(unsigned int* seqNo, CKSD_ReqOrderAllQry* req) {
    return api_ ? api_->ReqOrderAllQry(seqNo, req) : -1;
}

int JniTradeApi::reqTraderInsertOrders(unsigned int* seqNo, CKSD_ReqTraderInsertOrders* req) {
    return api_ ? api_->ReqTraderInsertOrders(seqNo, req) : -1;
}

int JniTradeApi::reqTraderQuitOrder(unsigned int* seqNo, CKSD_ReqTraderQuitOrder* req) {
    return api_ ? api_->ReqTraderQuitOrder(seqNo, req) : -1;
}

void JniTradeApi::startThread() {
    if (!worker_) {
        active_ = true;
        // 所有 Java 回调都统一在这个线程里执行，避免直接在 SDK 回调线程里碰 JNI。
        worker_ = new std::thread(&JniTradeApi::processTask, this);
    }
}

void JniTradeApi::stopThread() {
    if (worker_) {
        active_ = false;
        // 投递退出任务，让工作线程以同一流程安全退出。
        Task task = {TASK_EXIT, nullptr, nullptr, 0, false};
        queue_.push(task);
        worker_->join();
        delete worker_;
        worker_ = nullptr;
    }
}

void JniTradeApi::OnFrontConnected() {
    // SDK 线程只负责投递任务，不直接回调 Java。
    Task task = {TASK_FRONT_CONNECTED, nullptr, nullptr, 0, false};
    queue_.push(task);
}

void JniTradeApi::OnFrontDisconnected() {
    Task task = {TASK_FRONT_DISCONNECTED, nullptr, nullptr, 0, false};
    queue_.push(task);
}

void JniTradeApi::OnKickOff() {
    Task task = {TASK_KICK_OFF, nullptr, nullptr, 0, false};
    queue_.push(task);
}

void JniTradeApi::OnRspTraderLogin(const CKSD_RspInfoField* rspInfo, const CKSD_RspTradeLoginField* data, bool isLast) {
    Task task = {TASK_RSP_LOGIN, copyData(data), copyData(rspInfo), 0, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRspTraderLogout(const CKSD_RspInfoField* rspInfo, const CKSD_RspTradeLogoutField* data, bool isLast) {
    Task task = {TASK_RSP_LOGOUT, copyData(data), copyData(rspInfo), 0, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRspTraderQryPosi(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderQryPosi* data, bool isLast) {
    Task task = {TASK_RSP_QRY_POSI, copyData(data), copyData(rspInfo), seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRspTraderQryMoney(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderQryMoney* data, bool isLast) {
    Task task = {TASK_RSP_QRY_MONEY, copyData(data), copyData(rspInfo), seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRspTraderPosiAllQry(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderPosiAllQry* data, bool isLast) {
    Task task = {TASK_RSP_POSI_ALL_QRY, copyData(data), copyData(rspInfo), seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRspTraderQryStorage(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderQryStorage* data, bool isLast) {
    Task task = {TASK_RSP_QRY_STORAGE, copyData(data), copyData(rspInfo), seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRspOrderAllQry(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspOrderAllQry* data, bool isLast) {
    Task task = {TASK_RSP_ORDER_ALL, copyData(data), copyData(rspInfo), seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRspTraderInsertOrders(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderInsertOrders* data, bool isLast) {
    Task task = {TASK_RSP_INSERT_ORDER, copyData(data), copyData(rspInfo), seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRtnTraderInsertOrders(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RtnTraderInsertOrders* data, bool isLast) {
    Task task = {TASK_RTN_INSERT_ORDER, copyData(data), copyData(rspInfo), seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::OnRspTraderQuitOrder(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderQuitOrder* data, bool isLast) {
    Task task = {TASK_RSP_QUIT_ORDER, copyData(data), copyData(rspInfo), seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::OnNtyTraderMatch(unsigned int seqNo, const CKSD_NtyTraderMatch* data, bool isLast) {
    Task task = {TASK_NTY_TRADER_MATCH, copyData(data), nullptr, seqNo, isLast};
    queue_.push(task);
}

void JniTradeApi::processTask() {
    JNIEnv* env = nullptr;
    // 工作线程需要显式附着到 JVM，才能安全使用 JNI。
    jvm_->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr);
    jclass apiClass = env->GetObjectClass(javaObj_);

    jmethodID midFrontConnected = env->GetMethodID(apiClass, "onFrontConnected", "()V");
    jmethodID midFrontDisconnected = env->GetMethodID(apiClass, "onFrontDisconnected", "()V");
    jmethodID midKickOff = env->GetMethodID(apiClass, "onKickOff", "()V");
    jmethodID midRspTraderLogin = env->GetMethodID(apiClass, "onRspTraderLogin", "(Lcom/dimple/trade/struct/KsdRspTradeLogin;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRspTraderLogout = env->GetMethodID(apiClass, "onRspTraderLogout", "(Lcom/dimple/trade/struct/KsdRspTradeLogout;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRspTraderQryPosi = env->GetMethodID(apiClass, "onRspTraderQryPosi", "(ILcom/dimple/trade/struct/KsdRspTraderQryPosi;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRspTraderQryMoney = env->GetMethodID(apiClass, "onRspTraderQryMoney", "(ILcom/dimple/trade/struct/KsdRspTraderQryMoney;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRspTraderPosiAllQry = env->GetMethodID(apiClass, "onRspTraderPosiAllQry", "(ILcom/dimple/trade/struct/KsdRspTraderPosiAllQry;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRspTraderQryStorage = env->GetMethodID(apiClass, "onRspTraderQryStorage", "(ILcom/dimple/trade/struct/KsdRspTraderQryStorage;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRspOrderAllQry = env->GetMethodID(apiClass, "onRspOrderAllQry", "(ILcom/dimple/trade/struct/KsdRspOrderAllQry;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRspTraderInsertOrders = env->GetMethodID(apiClass, "onRspTraderInsertOrders", "(ILcom/dimple/trade/struct/KsdRspTraderInsertOrders;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRtnTraderInsertOrders = env->GetMethodID(apiClass, "onRtnTraderInsertOrders", "(ILcom/dimple/trade/struct/KsdRtnTraderInsertOrders;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midRspTraderQuitOrder = env->GetMethodID(apiClass, "onRspTraderQuitOrder", "(ILcom/dimple/trade/struct/KsdRspTraderQuitOrder;Lcom/dimple/trade/struct/KsdRspInfo;Z)V");
    jmethodID midNtyTraderMatch = env->GetMethodID(apiClass, "onNtyTraderMatch", "(ILcom/dimple/trade/struct/KsdNtyTraderMatch;Z)V");

    while (true) {
        Task task = queue_.waitAndPop();
        if (task.type == TASK_EXIT) {
            task.clear();
            break;
        }

        // 绝大多数应答都带错误对象，统一在这里先转换出来。
        jobject errorObj = makeRspInfo(env, javaObj_, static_cast<CKSD_RspInfoField*>(task.error));

        switch (task.type) {
            case TASK_FRONT_CONNECTED:
                env->CallVoidMethod(javaObj_, midFrontConnected);
                break;
            case TASK_FRONT_DISCONNECTED:
                env->CallVoidMethod(javaObj_, midFrontDisconnected);
                break;
            case TASK_KICK_OFF:
                env->CallVoidMethod(javaObj_, midKickOff);
                break;
            case TASK_RSP_LOGIN: {
                // 登录应答：把 C++ 结构体映射到 Java DTO，再分发给业务层。
                CKSD_RspTradeLoginField* data = static_cast<CKSD_RspTradeLoginField*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspTradeLogin");
                if (obj && data) {
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "loginTime", data->Time);
                    setStringField(env, obj, "tradingDay", data->Date);
                    setStringField(env, obj, "latestOrderNo", data->LatestOrderNo);
                    setStringField(env, obj, "latestQuoteOrderNo", data->LatestQuoteOrderNo);
                    setStringField(env, obj, "latestQuoteOrderBatchNo", data->LatestQuoteOrderBatchNo);
                    setIntField(env, obj, "isPwdExpirePrompt", data->IsPwdExpirePrompt);
                    setIntField(env, obj, "expireDays", static_cast<jint>(data->ExpireDays));
                }
                env->CallVoidMethod(javaObj_, midRspTraderLogin, obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RSP_LOGOUT: {
                CKSD_RspTradeLogoutField* data = static_cast<CKSD_RspTradeLogoutField*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspTradeLogout");
                if (obj && data) {
                    setStringField(env, obj, "traderNo", data->TraderNo);
                }
                env->CallVoidMethod(javaObj_, midRspTraderLogout, obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RSP_QRY_POSI: {
                // 持仓查询是典型的多条回包场景，因此保留 seqNo 和 isLast。
                CKSD_RspTraderQryPosi* data = static_cast<CKSD_RspTraderQryPosi*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspTraderQryPosi");
                if (obj && data) {
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "clientID", data->ClientID);
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "contractID", data->ContractID);
                    setStringField(env, obj, "shFlag", string(1, data->ShFlag).c_str());
                    setLongField(env, obj, "lastBuyQty", data->LastBuyQty);
                    setLongField(env, obj, "lastSellQty", data->LastSellQty);
                    setLongField(env, obj, "todayBuyQty", data->TodayBuyQty);
                    setLongField(env, obj, "todaySellQty", data->TodaySellQty);
                    setLongField(env, obj, "buyQty", data->BuyQty);
                    setLongField(env, obj, "sellQty", data->SellQty);
                    setDoubleField(env, obj, "buyAmt", data->BuyAmt);
                    setDoubleField(env, obj, "sellAmt", data->SellAmt);
                    setLongField(env, obj, "buyOpenQty", data->BuyOpenQty);
                    setLongField(env, obj, "sellOpenQty", data->SellOpenQty);
                    setLongField(env, obj, "buyOffsetQty", data->BuyOffsetQty);
                    setLongField(env, obj, "sellOffsetQty", data->SellOffsetQty);
                    setLongField(env, obj, "buyOffsetTodayFrozenQty", data->BuyOffsetTodayFrozenQty);
                    setLongField(env, obj, "sellOffsetTodayFrozenQty", data->SellOffsetTodayFrozenQty);
                    setLongField(env, obj, "buyOffsetLastFrozenQty", data->BuyOffsetLastFrozenQty);
                    setLongField(env, obj, "sellOffsetLastFrozenQty", data->SellOffsetLastFrozenQty);
                    setStringField(env, obj, "actArbiContractID", data->ActArbiContractID);
                    setStringField(env, obj, "tradePurpose", data->TradePurpose);
                }
                env->CallVoidMethod(javaObj_, midRspTraderQryPosi, static_cast<jint>(task.seqNo), obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RSP_QRY_MONEY: {
                CKSD_RspTraderQryMoney* data = static_cast<CKSD_RspTraderQryMoney*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspTraderQryMoney");
                if (obj && data) {
                    setStringField(env, obj, "currency", data->Currency);
                    setStringField(env, obj, "exchCode", data->ExchCode);
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setDoubleField(env, obj, "creditTot", data->CreditTot);
                    setDoubleField(env, obj, "creditUsed", data->CreditUsed);
                    setDoubleField(env, obj, "creditFrozen", data->CreditFrozen);
                    setDoubleField(env, obj, "creditRemain", data->CreditRemain);
                    setDoubleField(env, obj, "floatProfitLoss", data->FloatProfitLoss);
                    setDoubleField(env, obj, "offsetProfitLoss", data->OffsetProfitLoss);
                }
                env->CallVoidMethod(javaObj_, midRspTraderQryMoney, static_cast<jint>(task.seqNo), obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RSP_POSI_ALL_QRY: {
                CKSD_RspTraderPosiAllQry* data = static_cast<CKSD_RspTraderPosiAllQry*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspTraderPosiAllQry");
                if (obj && data) {
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "clientID", data->ClientID);
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "actArbiContractId", data->ActArbiContractId);
                    setStringField(env, obj, "contractID", data->ContractID);
                    setStringField(env, obj, "bsFlag", string(1, data->BsFlag).c_str());
                    setStringField(env, obj, "shFlag", string(1, data->ShFlag).c_str());
                    setLongField(env, obj, "lastQty", data->LastQty);
                    setLongField(env, obj, "qty", data->Qty);
                    setLongField(env, obj, "offsetQty", data->OffsetQty);
                    setLongField(env, obj, "offsetLastQty", data->OffsetLastQty);
                    setLongField(env, obj, "offsetTodayQty", data->OffsetTodayQty);
                    setDoubleField(env, obj, "exposure", data->Exposure);
                    setDoubleField(env, obj, "amt", data->Amt);
                    setDoubleField(env, obj, "margin", data->Margin);
                    setDoubleField(env, obj, "avePrice", data->AvePrice);
                    setDoubleField(env, obj, "lastPrice", data->LastPrice);
                    setDoubleField(env, obj, "profitFund", data->ProfitFund);
                    setDoubleField(env, obj, "floatProfitLoss", data->FloatProfitLoss);
                    setDoubleField(env, obj, "profitLossTodayFloating", data->ProfitLossTodayFloating);
                    setDoubleField(env, obj, "profitLossTotal", data->ProfitLossTotal);
                    setStringField(env, obj, "tradePurpose", data->TradePurpose);
                }
                env->CallVoidMethod(javaObj_, midRspTraderPosiAllQry, static_cast<jint>(task.seqNo), obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RSP_QRY_STORAGE: {
                CKSD_RspTraderQryStorage* data = static_cast<CKSD_RspTraderQryStorage*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspTraderQryStorage");
                if (obj && data) {
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "contractID", data->ContractID);
                    setStringField(env, obj, "varietyID", data->VarietyID);
                    setStringField(env, obj, "varietyName", data->VarietyName);
                    setDoubleField(env, obj, "totalStorage", data->TotalStorage);
                    setDoubleField(env, obj, "availableStorage", data->AvailableStorage);
                    setDoubleField(env, obj, "frozenStorage", data->FrozenStorage);
                    setDoubleField(env, obj, "pendStorage", data->PendStorage);
                    setDoubleField(env, obj, "impawnStorage", data->ImpawnStorage);
                    setDoubleField(env, obj, "lawFrozen", data->LawFrozen);
                    setStringField(env, obj, "tradePurpose", data->TradePurpose);
                    setDoubleField(env, obj, "setoffFrozen", data->SetoffFrozen);
                    setDoubleField(env, obj, "transferFrozen", data->TransferFrozen);
                }
                env->CallVoidMethod(javaObj_, midRspTraderQryStorage, static_cast<jint>(task.seqNo), obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RSP_ORDER_ALL: {
                CKSD_RspOrderAllQry* data = static_cast<CKSD_RspOrderAllQry*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspOrderAllQry");
                if (obj && data) {
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "clientID", data->ClientID);
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "actArbiContractId", data->ActArbiContractId);
                    setStringField(env, obj, "contractID", data->ContractID);
                    setStringField(env, obj, "bsFlag", string(1, data->BsFlag).c_str());
                    setStringField(env, obj, "shFlag", string(1, data->ShFlag).c_str());
                    setLongField(env, obj, "qty", data->Qty);
                    setLongField(env, obj, "offsetQty", data->OffsetQty);
                    setLongField(env, obj, "offsetLastQty", data->OffsetLastQty);
                    setLongField(env, obj, "offsetTodayQty", data->OffsetTodayQty);
                    setDoubleField(env, obj, "avePrice", data->AvePrice);
                    setDoubleField(env, obj, "price", data->Price);
                    setStringField(env, obj, "tradePurpose", data->TradePurpose);
                }
                env->CallVoidMethod(javaObj_, midRspOrderAllQry, static_cast<jint>(task.seqNo), obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RSP_INSERT_ORDER:
            {
                // 下单应答是“请求是否被接受”，真正的订单状态以后续回报为准。
                CKSD_RspTraderInsertOrders* data = static_cast<CKSD_RspTraderInsertOrders*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspTraderInsertOrders");
                if (obj && data) {
                    setStringField(env, obj, "localOrderNo", data->LocalOrderNo);
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "clientID", data->ClientID);
                    setStringField(env, obj, "contractID", data->ContractID);
                    setStringField(env, obj, "bsFlag", string(1, data->BsFlag).c_str());
                    setStringField(env, obj, "eoFlag", string(1, data->EoFlag).c_str());
                    setStringField(env, obj, "shFlag", string(1, data->ShFlag).c_str());
                    setDoubleField(env, obj, "stopPrice", data->StopPrice);
                    setDoubleField(env, obj, "price", data->Price);
                    setLongField(env, obj, "qty", data->Qty);
                    setStringField(env, obj, "orderType", string(1, data->OrderType).c_str());
                    setStringField(env, obj, "orderAttr", string(1, data->OrderAttr).c_str());
                    setStringField(env, obj, "orderTime", data->OrderTime);
                    setStringField(env, obj, "actArbiContractID", data->ActArbiContractID);
                    setStringField(env, obj, "tradePurpose", data->TradePurpose);
                }
                env->CallVoidMethod(javaObj_, midRspTraderInsertOrders, static_cast<jint>(task.seqNo), obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RTN_INSERT_ORDER: {
                // 委托回报反映订单真实流转状态。
                CKSD_RtnTraderInsertOrders* data = static_cast<CKSD_RtnTraderInsertOrders*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRtnTraderInsertOrders");
                if (obj && data) {
                    setStringField(env, obj, "sysOrderNo", data->SysOrderNo);
                    setStringField(env, obj, "localOrderNo", data->LocalOrderNo);
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "clientID", data->ClientID);
                    setStringField(env, obj, "contractID", data->ContractID);
                    setStringField(env, obj, "exchCode", data->ExchCode);
                    setStringField(env, obj, "bsFlag", string(1, data->BsFlag).c_str());
                    setStringField(env, obj, "eoFlag", string(1, data->EoFlag).c_str());
                    setStringField(env, obj, "shFlag", string(1, data->ShFlag).c_str());
                    setDoubleField(env, obj, "price", data->Price);
                    setLongField(env, obj, "qty", data->Qty);
                    setStringField(env, obj, "orderType", string(1, data->OrderType).c_str());
                    setStringField(env, obj, "orderAttr", string(1, data->OrderAttr).c_str());
                    setStringField(env, obj, "orderTime", data->OrderTime);
                    setLongField(env, obj, "orderBatchNo", data->OrderBatchNo);
                    setStringField(env, obj, "tradeType", string(1, data->TradeType).c_str());
                    setStringField(env, obj, "tradingDay", data->TradingDay);
                    setStringField(env, obj, "status", data->Status);
                    setStringField(env, obj, "actArbiContractID", data->ActArbiContractID);
                    setLongField(env, obj, "remainAmt", data->RemainAmt);
                    setStringField(env, obj, "type", string(1, data->Type).c_str());
                    setStringField(env, obj, "tradePurpose", data->TradePurpose);
                }
                env->CallVoidMethod(javaObj_, midRtnTraderInsertOrders, static_cast<jint>(task.seqNo), obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_RSP_QUIT_ORDER: {
                CKSD_RspTraderQuitOrder* data = static_cast<CKSD_RspTraderQuitOrder*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdRspTraderQuitOrder");
                if (obj && data) {
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "clientID", data->ClientID);
                    setLongField(env, obj, "orderBatchNo", data->OrderBatchNo);
                    setStringField(env, obj, "contractID", data->ContractID);
                    setStringField(env, obj, "cancelTraderNo", data->CancelTraderNo);
                    setStringField(env, obj, "localOrderNo", data->LocalOrderNo);
                    setStringField(env, obj, "sysOrderNo", data->SysOrderNo);
                    setStringField(env, obj, "exchCode", data->ExchCode);
                    setStringField(env, obj, "actionTime", data->ActionTime);
                    setLongField(env, obj, "orderCancelQty", data->OrderCancelQty);
                }
                env->CallVoidMethod(javaObj_, midRspTraderQuitOrder, static_cast<jint>(task.seqNo), obj, errorObj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
            case TASK_NTY_TRADER_MATCH: {
                // 成交通知为异步推送，没有错误对象。
                CKSD_NtyTraderMatch* data = static_cast<CKSD_NtyTraderMatch*>(task.data);
                jobject obj = newObject(env, javaObj_, "com/dimple/trade/struct/KsdNtyTraderMatch");
                if (obj && data) {
                    setStringField(env, obj, "contractID", data->ContractID);
                    setStringField(env, obj, "exchCode", data->ExchCode);
                    setStringField(env, obj, "matchNo", data->MatchNo);
                    setStringField(env, obj, "matchDate", data->MatchDate);
                    setStringField(env, obj, "matchTime", data->MatchTime);
                    setDoubleField(env, obj, "price", data->Price);
                    setLongField(env, obj, "qty", data->Qty);
                    setStringField(env, obj, "sysOrderNo", data->SysOrderNo);
                    setStringField(env, obj, "traderNo", data->TraderNo);
                    setStringField(env, obj, "bsFlag", string(1, data->BsFlag).c_str());
                    setStringField(env, obj, "eoFlag", string(1, data->EoFlag).c_str());
                    setStringField(env, obj, "shFlag", string(1, data->ShFlag).c_str());
                    setStringField(env, obj, "memberID", data->MemberID);
                    setStringField(env, obj, "clientID", data->ClientID);
                    setStringField(env, obj, "localID", data->LocalID);
                    setLongField(env, obj, "orderBatchNo", data->OrderBatchNo);
                    setStringField(env, obj, "tradingRole", string(1, data->TradingRole).c_str());
                    setStringField(env, obj, "actArbiContractID", data->ActArbiContractID);
                    setStringField(env, obj, "midFlag", string(1, data->MidFlag).c_str());
                    setStringField(env, obj, "tradePurpose", data->TradePurpose);
                    setStringField(env, obj, "matchType", string(1, data->MatchType).c_str());
                }
                env->CallVoidMethod(javaObj_, midNtyTraderMatch, static_cast<jint>(task.seqNo), obj, task.isLast);
                if (obj) env->DeleteLocalRef(obj);
                break;
            }
        }

        if (errorObj) {
            env->DeleteLocalRef(errorObj);
        }
        task.clear();
    }

    env->DeleteLocalRef(apiClass);
    // 线程退出前必须从 JVM 解附。
    jvm_->DetachCurrentThread();
}

// 单例式持有 JNI 桥对象，保持与 Java 侧使用方式一致。
static JniTradeApi* g_api = nullptr;

extern "C" {

JNIEXPORT void JNICALL Java_com_dimple_trade_KsdTradeApi_createKSDTradeApi(JNIEnv* env, jobject obj) {
    JavaVM* jvm = nullptr;
    env->GetJavaVM(&jvm);
    if (!g_api) {
        char msg[192];
        std::snprintf(msg, sizeof(msg), "[jni-charset] init codepage=%u preferUtf8=%d debug=%d\n",
                      sdkCodePage(), preferUtf8Decode() ? 1 : 0, charsetDebugEnabled() ? 1 : 0);
        logCharset(msg);
        g_api = new JniTradeApi(jvm, obj);
    }
    g_api->createApi();
}

// 以下导出函数负责把 Java 请求对象拆成 C 结构体，再转调到底层交易 API。
JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_registerServer(JNIEnv* env, jobject, jstring ip, jint port) {
    if (!g_api) {
        return -1;
    }
    string nativeIp = getJString(env, ip);
    return g_api->registerServer(const_cast<char*>(nativeIp.c_str()), port);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_subscribePrivateFlow(JNIEnv*, jobject) {
    return g_api ? g_api->subscribePrivateFlow() : -1;
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_subscribePublicFlow(JNIEnv*, jobject) {
    return g_api ? g_api->subscribePublicFlow() : -1;
}

JNIEXPORT void JNICALL Java_com_dimple_trade_KsdTradeApi_init(JNIEnv*, jobject) {
    if (g_api) {
        g_api->init();
    }
}

JNIEXPORT void JNICALL Java_com_dimple_trade_KsdTradeApi_join(JNIEnv*, jobject) {
    if (g_api) {
        g_api->join();
    }
}

JNIEXPORT void JNICALL Java_com_dimple_trade_KsdTradeApi_release(JNIEnv*, jobject) {
    if (g_api) {
        g_api->release();
    }
}

JNIEXPORT void JNICALL Java_com_dimple_trade_KsdTradeApi_exit(JNIEnv*, jobject) {
    if (g_api) {
        g_api->stopThread();
        g_api->release();
        delete g_api;
        g_api = nullptr;
    }
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderLogin(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    CKSD_ReqTradeLoginField req = {0};
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    copyToCharArray(req.Pwd, sizeof(req.Pwd), getObjectStringField(env, reqObj, "password"));
    req.IfWithoutPwd = static_cast<unsigned char>(getObjectIntField(env, reqObj, "ifWithoutPwd"));
    copyToCharArray(req.UmID, sizeof(req.UmID), getObjectStringField(env, reqObj, "umId"));
    copyToCharArray(req.UmPwd, sizeof(req.UmPwd), getObjectStringField(env, reqObj, "umPwd"));
    req.IfQuantify = static_cast<unsigned char>(getObjectIntField(env, reqObj, "ifQuantify"));
    return g_api->reqTraderLogin(&req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderEncLogin(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    CKSD_ReqEncTradeLoginField req = {0};
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    copyToCharArray(req.Pwd, sizeof(req.Pwd), getObjectStringField(env, reqObj, "password"));
    return g_api->reqTraderEncLogin(&req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderLogout(JNIEnv* env, jobject, jstring traderNo) {
    if (!g_api) {
        return -1;
    }
    CKSD_ReqTradeLogoutField req = {0};
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getJString(env, traderNo));
    return g_api->reqTraderLogout(&req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderQryPosi(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    unsigned int seqNo = 0;
    CKSD_ReqTraderQryPosi req = {0};
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    return g_api->reqTraderQryPosi(&seqNo, &req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderQryMoney(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    unsigned int seqNo = 0;
    CKSD_ReqTraderQryMoney req = {0};
    copyToCharArray(req.ExchCode, sizeof(req.ExchCode), getObjectStringField(env, reqObj, "exchCode"));
    copyToCharArray(req.MemberID, sizeof(req.MemberID), getObjectStringField(env, reqObj, "memberID"));
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    copyToCharArray(req.Currency, sizeof(req.Currency), getObjectStringField(env, reqObj, "currency"));
    return g_api->reqTraderQryMoney(&seqNo, &req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderPosiAllQry(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    unsigned int seqNo = 0;
    CKSD_ReqTraderPosiAllQry req = {0};
    copyToCharArray(req.MemberID, sizeof(req.MemberID), getObjectStringField(env, reqObj, "memberID"));
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    copyToCharArray(req.ContractId, sizeof(req.ContractId), getObjectStringField(env, reqObj, "contractId"));
    string contractType = getObjectStringField(env, reqObj, "contractType");
    req.ContractType = contractType.empty() ? 0 : contractType[0];
    copyToCharArray(req.ActArbiContractID, sizeof(req.ActArbiContractID), getObjectStringField(env, reqObj, "actArbiContractID"));
    copyToCharArray(req.TradePurpose, sizeof(req.TradePurpose), getObjectStringField(env, reqObj, "tradePurpose"));
    return g_api->reqTraderPosiAllQry(&seqNo, &req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderQryStorage(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    unsigned int seqNo = 0;
    CKSD_ReqTraderQryStorage req = {0};
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    return g_api->reqTraderQryStorage(&seqNo, &req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqOrderAllQry(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    unsigned int seqNo = 0;
    CKSD_ReqOrderAllQry req = {0};
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    copyToCharArray(req.ContractId, sizeof(req.ContractId), getObjectStringField(env, reqObj, "contractId"));
    string contractType = getObjectStringField(env, reqObj, "contractType");
    req.ContractType = contractType.empty() ? 0 : contractType[0];
    return g_api->reqOrderAllQry(&seqNo, &req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderInsertOrders(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    unsigned int seqNo = 0;
    CKSD_ReqTraderInsertOrders req = {0};
    copyToCharArray(req.LocalOrderNo, sizeof(req.LocalOrderNo), getObjectStringField(env, reqObj, "localOrderNo"));
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    copyToCharArray(req.MemberID, sizeof(req.MemberID), getObjectStringField(env, reqObj, "memberID"));
    copyToCharArray(req.ClientID, sizeof(req.ClientID), getObjectStringField(env, reqObj, "clientID"));
    copyToCharArray(req.ContractID, sizeof(req.ContractID), getObjectStringField(env, reqObj, "contractID"));
    string bsFlag = getObjectStringField(env, reqObj, "bsFlag");
    string eoFlag = getObjectStringField(env, reqObj, "eoFlag");
    string shFlag = getObjectStringField(env, reqObj, "shFlag");
    string orderType = getObjectStringField(env, reqObj, "orderType");
    string orderAttr = getObjectStringField(env, reqObj, "orderAttr");
    req.BsFlag = bsFlag.empty() ? 0 : bsFlag[0];
    req.EoFlag = eoFlag.empty() ? 0 : eoFlag[0];
    req.ShFlag = shFlag.empty() ? 0 : shFlag[0];
    req.StopPrice = getObjectDoubleField(env, reqObj, "stopPrice");
    req.Price = getObjectDoubleField(env, reqObj, "price");
    req.Qty = static_cast<unsigned int>(getObjectLongField(env, reqObj, "qty"));
    req.OrderType = orderType.empty() ? 0 : orderType[0];
    req.OrderAttr = orderAttr.empty() ? 0 : orderAttr[0];
    copyToCharArray(req.OrderTime, sizeof(req.OrderTime), getObjectStringField(env, reqObj, "orderTime"));
    copyToCharArray(req.ActArbiContractID, sizeof(req.ActArbiContractID), getObjectStringField(env, reqObj, "actArbiContractID"));
    copyToCharArray(req.TradePurpose, sizeof(req.TradePurpose), getObjectStringField(env, reqObj, "tradePurpose"));
    return g_api->reqTraderInsertOrders(&seqNo, &req);
}

JNIEXPORT jint JNICALL Java_com_dimple_trade_KsdTradeApi_reqTraderQuitOrder(JNIEnv* env, jobject, jobject reqObj) {
    if (!g_api) {
        return -1;
    }
    unsigned int seqNo = 0;
    CKSD_ReqTraderQuitOrder req = {0};
    copyToCharArray(req.TraderNo, sizeof(req.TraderNo), getObjectStringField(env, reqObj, "traderNo"));
    copyToCharArray(req.MemberID, sizeof(req.MemberID), getObjectStringField(env, reqObj, "memberID"));
    copyToCharArray(req.ContractID, sizeof(req.ContractID), getObjectStringField(env, reqObj, "contractID"));
    copyToCharArray(req.CancelTraderNo, sizeof(req.CancelTraderNo), getObjectStringField(env, reqObj, "cancelTraderNo"));
    copyToCharArray(req.LocalOrderNo, sizeof(req.LocalOrderNo), getObjectStringField(env, reqObj, "localOrderNo"));
    copyToCharArray(req.SysOrderNo, sizeof(req.SysOrderNo), getObjectStringField(env, reqObj, "sysOrderNo"));
    return g_api->reqTraderQuitOrder(&seqNo, &req);
}

}

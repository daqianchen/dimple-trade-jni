#pragma once

#include <jni.h>
#include <condition_variable>
#include <cstring>
#include <mutex>
#include <queue>
#include <thread>

#include "KSDTradeApi.h"

using namespace KingstardimpleTradeApi;

enum TaskType {
    TASK_EXIT = 0,
    TASK_FRONT_CONNECTED = 1,
    TASK_FRONT_DISCONNECTED = 2,
    TASK_KICK_OFF = 3,
    TASK_RSP_LOGIN = 4,
    TASK_RSP_LOGOUT = 5,
    TASK_RSP_QRY_POSI = 6,
    TASK_RSP_QRY_MONEY = 7,
    TASK_RSP_ORDER_ALL = 8,
    TASK_RSP_INSERT_ORDER = 9,
    TASK_RTN_INSERT_ORDER = 10,
    TASK_RSP_QUIT_ORDER = 11,
    TASK_NTY_TRADER_MATCH = 12
};

struct Task {
    int type;
    void* data;
    void* error;
    unsigned int seqNo;
    bool isLast;

    void clear() {
        if (data) {
            free(data);
            data = nullptr;
        }
        if (error) {
            free(error);
            error = nullptr;
        }
    }
};

template<typename T>
class ConcurrentQueue {
public:
    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(value);
        lock.unlock();
        condition_.notify_one();
    }

    T waitAndPop() {
        std::unique_lock<std::mutex> lock(mutex_);
        while (queue_.empty()) {
            condition_.wait(lock);
        }
        T value = queue_.front();
        queue_.pop();
        return value;
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable condition_;
};

class JniTradeApi : public CKSDTradeSpi {
public:
    JniTradeApi(JavaVM* jvm, jobject javaObj);
    ~JniTradeApi();

    void createApi();
    void init();
    void release();
    void join();
    int registerServer(char* ip, int port);
    int subscribePrivateFlow();
    int subscribePublicFlow();
    int reqTraderLogin(CKSD_ReqTradeLoginField* req);
    int reqTraderEncLogin(CKSD_ReqEncTradeLoginField* req);
    int reqTraderLogout(CKSD_ReqTradeLogoutField* req);
    int reqTraderQryPosi(unsigned int* seqNo, CKSD_ReqTraderQryPosi* req);
    int reqTraderQryMoney(unsigned int* seqNo, CKSD_ReqTraderQryMoney* req);
    int reqOrderAllQry(unsigned int* seqNo, CKSD_ReqOrderAllQry* req);
    int reqTraderInsertOrders(unsigned int* seqNo, CKSD_ReqTraderInsertOrders* req);
    int reqTraderQuitOrder(unsigned int* seqNo, CKSD_ReqTraderQuitOrder* req);

    void startThread();
    void stopThread();
    void processTask();

    virtual void OnFrontConnected() override;
    virtual void OnFrontDisconnected() override;
    virtual void OnKickOff() override;
    virtual void OnRspTraderLogin(const CKSD_RspInfoField* rspInfo, const CKSD_RspTradeLoginField* data, bool isLast) override;
    virtual void OnRspTraderLogout(const CKSD_RspInfoField* rspInfo, const CKSD_RspTradeLogoutField* data, bool isLast) override;
    virtual void OnRspTraderQryPosi(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderQryPosi* data, bool isLast) override;
    virtual void OnRspTraderQryMoney(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderQryMoney* data, bool isLast) override;
    virtual void OnRspOrderAllQry(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspOrderAllQry* data, bool isLast) override;
    virtual void OnRspTraderInsertOrders(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderInsertOrders* data, bool isLast) override;
    virtual void OnRtnTraderInsertOrders(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RtnTraderInsertOrders* data, bool isLast) override;
    virtual void OnRspTraderQuitOrder(unsigned int seqNo, const CKSD_RspInfoField* rspInfo, const CKSD_RspTraderQuitOrder* data, bool isLast) override;
    virtual void OnNtyTraderMatch(unsigned int seqNo, const CKSD_NtyTraderMatch* data, bool isLast) override;

private:
    CKSDTradeApi* api_;
    JavaVM* jvm_;
    jobject javaObj_;
    std::thread* worker_;
    volatile bool active_;
    ConcurrentQueue<Task> queue_;
};

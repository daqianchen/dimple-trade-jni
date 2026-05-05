# DimpleTradeApi

`DimpleTradeApi` 是基于 `t_dapi` 的 JNI 交易封装工程，结构与 `DimpleQuoteApi` 保持一致，目标产物是一个可被其他 Java 项目直接引用的 jar。

## 当前能力

- 连接、初始化、释放
- 明文登录、密文登录、登出
- 订阅公有流、私有流
- 查询交易员持仓
- 查询交易员资金/信用额度
- 查询委托汇总
- 下单
- 撤单
- 交易回报、成交回报、连接状态回调

## 工程结构

- `src/main/java/com/dimple/trade`: Java API、结构体、动态库加载器
- `src/main/cpp`: Windows JNI 源码与 CMake 配置
- `src/main/cpp-linux`: Linux JNI 源码与 CMake 配置
- `src/main/lib`: 构建 JNI 时依赖的 Dimple 原生库
- `src/main/resources`: 打进 jar 的原生依赖库

## 打包步骤

### 1. 构建 JNI 动态库

Windows:

```powershell
cd src\main\cpp
cmake -B build -S . -A x64
cmake --build build --config Release
```

构建成功后，CMake 会自动把 `dimple_trade_jni.dll` 复制到 `src/main/resources/win-x64/`，避免 Windows jar 漏掉 JNI 桥接库。

Linux:

```bash
cd src/main/cpp-linux
cmake -B build -S .
cmake --build build --config Release
cp build/libdimple_trade_jni.so ../resources/linux-x64/
```

### 2. 打包 jar

```powershell
mvn clean package
```

产物位于 `target/DimpleTradeApi-1.0.0.jar`。

如果当前机器没有 Maven，也可以使用项目内脚本完成 Windows JNI 构建、资源检查和 jar 打包：

```powershell
.\scripts\build-windows-package.ps1
```

## 运行说明

默认会从 jar 中自动释放并加载以下依赖：

- Windows: `cryptopp.dll`, `KSDTradeApi.dll`, `dimple_trade_jni.dll`
- Linux: `libcryptopp64.so`, `libKSDTradeApi64.so`, `libdimple_trade_jni.so`

如果你希望从外部目录加载已经编好的 JNI 库，可以设置系统属性：

```java
System.setProperty("dimple.trade.native.dir", "D:/native-libs");
```

## 使用示例

```java
KsdTradeApi api = new KsdTradeApi() {
    @Override
    public void onFrontConnected() {
        KsdReqTradeLogin login = new KsdReqTradeLogin();
        login.traderNo = "demo001";
        login.password = "123456";
        reqTraderLogin(login);
    }

    @Override
    public void onRspTraderLogin(KsdRspTradeLogin data, KsdRspInfo error, boolean isLast) {
        System.out.println("login result = " + (error == null ? "OK" : error.errorID));
    }
};

api.createKSDTradeApi();
api.registerServer("127.0.0.1", 9001);
api.subscribePrivateFlow();
api.subscribePublicFlow();
api.init();
```

## 说明

这个版本优先把交易核心链路做成可以打包、可扩展的骨架。`t_dapi` 头文件里的高级查询、期权、ETF、定价等接口量非常大，当前 JNI 先覆盖了量化交易里最常见的一批交易接口；如果你需要，我可以继续在这个工程里按同一模式把剩余接口继续补全。

工程内我们新增和维护的源码、注释、说明文档统一按 UTF-8 保存，避免中文乱码。第三方 SDK 头文件如果原始发布时不是 UTF-8，建议在 IDE 中按对应原始编码查看，避免误判为工程编码问题。

package com.dimple.trade;

import com.dimple.trade.library.LibraryLoader;
import com.dimple.trade.struct.KsdNtyTraderMatch;
import com.dimple.trade.struct.KsdReqEncTradeLogin;
import com.dimple.trade.struct.KsdReqOrderAllQry;
import com.dimple.trade.struct.KsdReqTradeLogin;
import com.dimple.trade.struct.KsdReqTraderInsertOrders;
import com.dimple.trade.struct.KsdReqTraderQryMoney;
import com.dimple.trade.struct.KsdReqTraderQryStorage;
import com.dimple.trade.struct.KsdReqTraderQryPosi;
import com.dimple.trade.struct.KsdReqTraderPosiAllQry;
import com.dimple.trade.struct.KsdReqTraderQuitOrder;
import com.dimple.trade.struct.KsdRspInfo;
import com.dimple.trade.struct.KsdRspOrderAllQry;
import com.dimple.trade.struct.KsdRspTradeLogin;
import com.dimple.trade.struct.KsdRspTradeLogout;
import com.dimple.trade.struct.KsdRspTraderInsertOrders;
import com.dimple.trade.struct.KsdRspTraderQryMoney;
import com.dimple.trade.struct.KsdRspTraderQryPosi;
import com.dimple.trade.struct.KsdRspTraderQryStorage;
import com.dimple.trade.struct.KsdRspTraderPosiAllQry;
import com.dimple.trade.struct.KsdRspTraderQuitOrder;
import com.dimple.trade.struct.KsdRtnTraderInsertOrders;

/**
 * Dimple 交易 API 的 Java 抽象封装。
 * 业务系统继承该类后，可以直接发起交易请求并覆写回调方法处理异步应答。
 */
public abstract class KsdTradeApi {

    static {
        // 类加载时先装载 JNI 依赖库，避免首次调用 native 方法时再失败。
        LibraryLoader.load();
    }

    /** 创建底层 CKSDTradeApi 实例并注册 JNI SPI。 */
    public native void createKSDTradeApi();

    /** 注册交易前置地址。 */
    public native int registerServer(String ip, int port);

    /** 订阅私有流，通常用于订单、成交、资金等私有数据。 */
    public native int subscribePrivateFlow();

    /** 订阅公有流。 */
    public native int subscribePublicFlow();

    /** 初始化 API 并发起连接。 */
    public native void init();

    /** 阻塞等待底层线程退出。 */
    public native void join();

    /** 释放底层 API 资源。 */
    public native void release();

    /** 安全退出 JNI 层，并清理线程与 native 对象。 */
    public native void exit();

    /** 明文登录。 */
    public native int reqTraderLogin(KsdReqTradeLogin req);

    /** 密文登录，password 应传入已经加密后的内容。 */
    public native int reqTraderEncLogin(KsdReqEncTradeLogin req);

    /** 登出。 */
    public native int reqTraderLogout(String traderNo);

    /** 查询交易员持仓。 */
    public native int reqTraderQryPosi(KsdReqTraderQryPosi req);

    /** 查询交易员资金/信用额度。 */
    public native int reqTraderQryMoney(KsdReqTraderQryMoney req);

    /** 查询交易员持仓汇总。 */
    public native int reqTraderPosiAllQry(KsdReqTraderPosiAllQry req);

    /** 查询交易员库存。 */
    public native int reqTraderQryStorage(KsdReqTraderQryStorage req);

    /** 查询委托汇总。 */
    public native int reqOrderAllQry(KsdReqOrderAllQry req);

    /** 交易员下单。 */
    public native int reqTraderInsertOrders(KsdReqTraderInsertOrders req);

    /** 交易员撤单。 */
    public native int reqTraderQuitOrder(KsdReqTraderQuitOrder req);

    /** 前置连接成功回调。 */
    public void onFrontConnected() {
    }

    /** 前置连接断开回调。 */
    public void onFrontDisconnected() {
    }

    /** 账户被踢下线回调。 */
    public void onKickOff() {
    }

    /** 登录应答回调。 */
    public void onRspTraderLogin(KsdRspTradeLogin data, KsdRspInfo error, boolean isLast) {
    }

    /** 登出应答回调。 */
    public void onRspTraderLogout(KsdRspTradeLogout data, KsdRspInfo error, boolean isLast) {
    }

    /** 持仓查询应答回调。 */
    public void onRspTraderQryPosi(int seqNo, KsdRspTraderQryPosi data, KsdRspInfo error, boolean isLast) {
    }

    /** 资金查询应答回调。 */
    public void onRspTraderQryMoney(int seqNo, KsdRspTraderQryMoney data, KsdRspInfo error, boolean isLast) {
    }

    /** 持仓汇总查询应答回调。 */
    public void onRspTraderPosiAllQry(int seqNo, KsdRspTraderPosiAllQry data, KsdRspInfo error, boolean isLast) {
    }

    /** 库存查询应答回调。 */
    public void onRspTraderQryStorage(int seqNo, KsdRspTraderQryStorage data, KsdRspInfo error, boolean isLast) {
    }

    /** 委托汇总查询应答回调。 */
    public void onRspOrderAllQry(int seqNo, KsdRspOrderAllQry data, KsdRspInfo error, boolean isLast) {
    }

    /** 下单请求应答回调。 */
    public void onRspTraderInsertOrders(int seqNo, KsdRspTraderInsertOrders data, KsdRspInfo error, boolean isLast) {
    }

    /** 委托回报回调。 */
    public void onRtnTraderInsertOrders(int seqNo, KsdRtnTraderInsertOrders data, KsdRspInfo error, boolean isLast) {
    }

    /** 撤单应答回调。 */
    public void onRspTraderQuitOrder(int seqNo, KsdRspTraderQuitOrder data, KsdRspInfo error, boolean isLast) {
    }

    /** 成交通知回调。 */
    public void onNtyTraderMatch(int seqNo, KsdNtyTraderMatch data, boolean isLast) {
    }
}

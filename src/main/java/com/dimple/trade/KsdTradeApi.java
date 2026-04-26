package com.dimple.trade;

import com.dimple.trade.library.LibraryLoader;
import com.dimple.trade.struct.KsdNtyTraderMatch;
import com.dimple.trade.struct.KsdReqEncTradeLogin;
import com.dimple.trade.struct.KsdReqOrderAllQry;
import com.dimple.trade.struct.KsdReqTradeLogin;
import com.dimple.trade.struct.KsdReqTraderInsertOrders;
import com.dimple.trade.struct.KsdReqTraderQryMoney;
import com.dimple.trade.struct.KsdReqTraderQryPosi;
import com.dimple.trade.struct.KsdReqTraderQuitOrder;
import com.dimple.trade.struct.KsdRspInfo;
import com.dimple.trade.struct.KsdRspOrderAllQry;
import com.dimple.trade.struct.KsdRspTradeLogin;
import com.dimple.trade.struct.KsdRspTradeLogout;
import com.dimple.trade.struct.KsdRspTraderInsertOrders;
import com.dimple.trade.struct.KsdRspTraderQryMoney;
import com.dimple.trade.struct.KsdRspTraderQryPosi;
import com.dimple.trade.struct.KsdRspTraderQuitOrder;
import com.dimple.trade.struct.KsdRtnTraderInsertOrders;

public abstract class KsdTradeApi {

    static {
        LibraryLoader.load();
    }

    public native void createKSDTradeApi();

    public native int registerServer(String ip, int port);

    public native int subscribePrivateFlow();

    public native int subscribePublicFlow();

    public native void init();

    public native void join();

    public native void release();

    public native void exit();

    public native int reqTraderLogin(KsdReqTradeLogin req);

    public native int reqTraderEncLogin(KsdReqEncTradeLogin req);

    public native int reqTraderLogout(String traderNo);

    public native int reqTraderQryPosi(KsdReqTraderQryPosi req);

    public native int reqTraderQryMoney(KsdReqTraderQryMoney req);

    public native int reqOrderAllQry(KsdReqOrderAllQry req);

    public native int reqTraderInsertOrders(KsdReqTraderInsertOrders req);

    public native int reqTraderQuitOrder(KsdReqTraderQuitOrder req);

    public void onFrontConnected() {
    }

    public void onFrontDisconnected() {
    }

    public void onKickOff() {
    }

    public void onRspTraderLogin(KsdRspTradeLogin data, KsdRspInfo error, boolean isLast) {
    }

    public void onRspTraderLogout(KsdRspTradeLogout data, KsdRspInfo error, boolean isLast) {
    }

    public void onRspTraderQryPosi(int seqNo, KsdRspTraderQryPosi data, KsdRspInfo error, boolean isLast) {
    }

    public void onRspTraderQryMoney(int seqNo, KsdRspTraderQryMoney data, KsdRspInfo error, boolean isLast) {
    }

    public void onRspOrderAllQry(int seqNo, KsdRspOrderAllQry data, KsdRspInfo error, boolean isLast) {
    }

    public void onRspTraderInsertOrders(int seqNo, KsdRspTraderInsertOrders data, KsdRspInfo error, boolean isLast) {
    }

    public void onRtnTraderInsertOrders(int seqNo, KsdRtnTraderInsertOrders data, KsdRspInfo error, boolean isLast) {
    }

    public void onRspTraderQuitOrder(int seqNo, KsdRspTraderQuitOrder data, KsdRspInfo error, boolean isLast) {
    }

    public void onNtyTraderMatch(int seqNo, KsdNtyTraderMatch data, boolean isLast) {
    }
}

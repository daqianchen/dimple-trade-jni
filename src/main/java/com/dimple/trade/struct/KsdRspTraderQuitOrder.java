package com.dimple.trade.struct;

/** 撤单应答。 */
public class KsdRspTraderQuitOrder {
    public String traderNo;
    public String memberID;
    public String clientID;
    public long orderBatchNo;
    public String contractID;
    public String cancelTraderNo;
    public String localOrderNo;
    public String sysOrderNo;
    public String exchCode;
    public String actionTime;
    public long orderCancelQty;
}

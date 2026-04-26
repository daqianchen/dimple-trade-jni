package com.dimple.trade.struct;

/** 下单请求。 */
public class KsdReqTraderInsertOrders {
    public String localOrderNo;
    public String traderNo;
    public String memberID;
    public String clientID;
    public String contractID;
    public String bsFlag;
    public String eoFlag;
    public String shFlag;
    public double stopPrice;
    public double price;
    public long qty;
    public String orderType;
    public String orderAttr;
    public String orderTime;
    public String actArbiContractID;
    public String tradePurpose;
}

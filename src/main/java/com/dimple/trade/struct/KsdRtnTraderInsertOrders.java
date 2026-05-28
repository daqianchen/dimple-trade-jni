package com.dimple.trade.struct;

import lombok.Data;

/** 委托回报。 */
@Data
public class KsdRtnTraderInsertOrders {
    public String sysOrderNo;
    public String localOrderNo;
    public String traderNo;
    public String memberID;
    public String clientID;
    public String contractID;
    public String exchCode;
    public String bsFlag;
    public String eoFlag;
    public String shFlag;
    public double price;
    public long qty;
    public String orderType;
    public String orderAttr;
    public String orderTime;
    public long orderBatchNo;
    public String tradeType;
    public String tradingDay;
    public String status;
    public String actArbiContractID;
    public long remainAmt;
    public String type;
    public String tradePurpose;
}

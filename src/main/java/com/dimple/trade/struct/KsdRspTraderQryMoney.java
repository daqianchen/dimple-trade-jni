package com.dimple.trade.struct;

import lombok.Data;

/** 资金/信用额度查询应答。 */
@Data
public class KsdRspTraderQryMoney {
    public String currency;
    public String exchCode;
    public String memberID;
    public String traderNo;
    public double creditTot;
    public double creditUsed;
    public double creditFrozen;
    public double creditRemain;
    public double floatProfitLoss;
    public double offsetProfitLoss;
}

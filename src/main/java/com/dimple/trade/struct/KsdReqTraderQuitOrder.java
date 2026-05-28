package com.dimple.trade.struct;

import lombok.Data;

/** 撤单请求。 */
@Data
public class KsdReqTraderQuitOrder {
    public String traderNo;
    public String memberID;
    public String contractID;
    public String cancelTraderNo;
    public String localOrderNo;
    public String sysOrderNo;
}

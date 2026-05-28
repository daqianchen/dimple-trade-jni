package com.dimple.trade.struct;

import lombok.Data;

/** 登录应答。 */
@Data
public class KsdRspTradeLogin {
    public String memberID;
    public String traderNo;
    public String loginTime;
    public String tradingDay;
    public String latestOrderNo;
    public String latestQuoteOrderNo;
    public String latestQuoteOrderBatchNo;
    public int isPwdExpirePrompt;
    public int expireDays;
}

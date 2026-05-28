package com.dimple.trade.struct;

import lombok.Data;

/** 资金/信用额度查询请求。 */
@Data
public class KsdReqTraderQryMoney {
    public String exchCode;
    public String memberID;
    public String traderNo;
    public String currency;
}

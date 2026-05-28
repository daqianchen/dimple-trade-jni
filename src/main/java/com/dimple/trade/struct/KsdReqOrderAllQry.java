package com.dimple.trade.struct;

import lombok.Data;

/** 委托汇总查询请求。 */
@Data
public class KsdReqOrderAllQry {
    public String traderNo;
    public String contractId;
    public String contractType;
}

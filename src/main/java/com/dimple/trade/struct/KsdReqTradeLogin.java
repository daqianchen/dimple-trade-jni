package com.dimple.trade.struct;

import lombok.Data;

/** 明文登录请求。 */
@Data
public class KsdReqTradeLogin {
    public String traderNo;
    public String password;
    public int ifWithoutPwd;
    public String umId;
    public String umPwd;
    public int ifQuantify;
}

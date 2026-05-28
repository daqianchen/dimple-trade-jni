package com.dimple.trade.struct;

import lombok.Data;

/** 密文登录请求。 */
@Data
public class KsdReqEncTradeLogin {
    public String traderNo;
    public String password;
}

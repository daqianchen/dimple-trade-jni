package com.dimple.trade.struct;

import lombok.Data;

/** 通用错误应答信息。 */
@Data
public class KsdRspInfo {
    public int errorID;
    public String errorMsg;
    public String timeStamp;
}

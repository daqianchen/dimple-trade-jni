#ifndef KSD_FTDCSTRUCT_H
#define KSD_FTDCSTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KSDUserApiDataType.h"
#include <vector>
using namespace std;

///响应信息
struct CKSD_RspInfoField
{

	TKSD_ErrorIDType	ErrCode; /* 错误代码 */
	TKSD_ErrorMsgType	RspMsg;/*错误信息*/
	TKSD_TimestampType 	TimeStamp; /*时间戳*/
};

///用户登录请求
struct CKSD_ReqTradeLoginField
{
	///
	TKSD_TraderIDType	TraderNo; /*用户代码*/
	///
	TKSD_PasswordType	Pwd; /*密码*/
	///
	TKSD_ByteType		IfWithoutPwd; /*是否免密登录*/	
	///
	TKSD_UMIDType		UmID;/*员工号*/	
	///
	TKSD_PasswordType	UmPwd; /*员工号密码*/
	///
	TKSD_ByteType		IfQuantify; /*是否量化*/
};

///用户登录应答
struct CKSD_RspTradeLoginField
{
	TKSD_MemberIDType 	MemberID; /*会员号*/
	TKSD_TraderIDType	TraderNo; /*用户代码*/
	TKSD_TimeType		Time; /*交易核心日期*/
	TKSD_DateType		Date; /*交易核心时间*/
	TKSD_LatestOrderNo	LatestOrderNo; /*最近成功提交的报单编号*/
	TKSD_LatestOrderNo	LatestQuoteOrderNo; /*最近成功提交的报价报单编号*/
	TKSD_LatestOrderNo	LatestQuoteOrderBatchNo; /*最近成功提交的报价报单批次号*/
	TKSD_CByteType   	IsPwdExpirePrompt;    // 密码是否到期提示
	TKSD_VolumeType		ExpireDays;  /*距离过期天数*/
};

///用户登出请求
struct CKSD_ReqTradeLogoutField
{	
	TKSD_TraderIDType	TraderNo;///用户代码
};

///用户登出应答
struct CKSD_RspTradeLogoutField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
};

///用户资金查询
struct CKSD_ReqTradingAccountField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
};

///用户资金应答
struct CKSD_RspTradingAccountField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_MoneyType		Available;	///可用资金
	TKSD_MoneyType		FrozenMargin;	///委托冻结资金
	TKSD_MoneyType		OccupyMargin;	///占用资金
	TKSD_MoneyType		CloseProfit;	///平仓盈亏
};

///用户资金变化通知
struct CKSD_RtnTradingAccountField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_MoneyType		Available;	///可用资金
	TKSD_MoneyType		FrozenMargin;	///委托冻结资金
	TKSD_MoneyType		OccupyMargin;	///占用资金
	TKSD_MoneyType		CloseProfit;	///平仓盈亏
};

//库存查询请求
struct CKSD_ReqStorageField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_VarietyIDType  VarietyID;	///交割品种代码
	TKSD_ContractIDType	ContractID;	///合约代码
};

///库存查询应答
struct CKSD_RspStorageField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_VarietyIDType  VarietyID;	///交割品种代码            	
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_WeightType     TotalStorage;  	///库存总量       	
	TKSD_WeightType		AvailableStorage;	///可用库存
	TKSD_WeightType		FrozenStorage;	///现货冻结库存
};

///库存变化通知
struct CKSD_RtnStorageField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_VarietyIDType  VarietyID; 	///交割品种代码           	
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_WeightType     TotalStorage;     	///库存总量   	
	TKSD_WeightType		AvailableStorage;	///可用库存
	TKSD_WeightType		FrozenStorage;	///现货冻结库存
};

///用户持仓查询
struct CKSD_ReqInvestorPositionField
{	
	TKSD_TraderIDType	TraderNo;///用户代码
	TKSD_ContractIDType	ContractID;	///合约代码
};

///用户持仓应答
struct CKSD_RspInvestorPositionField
{

	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_ByteType		BsFlag;	///买卖标志
	TKSD_VolumeType		LastQty;	///上日持仓量
	TKSD_VolumeType		Qty;	///今日持仓量
	TKSD_VolumeType		OffsetLastQty;	///可平昨
	TKSD_VolumeType		OffsetTodayQty;	///可平今
	TKSD_PriceType		Amt;	///持仓额
	TKSD_PriceType		AvePrice;	///持仓均价
	TKSD_PriceType		LastPrice;	///最新价
	TKSD_PriceType		FloatProfitLoss;	///持仓盈亏
};

///用户持仓变化通知
struct CKSD_RtnInvestorPositionField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_ByteType		BsFlag;	///买卖标志
	TKSD_VolumeType		LastQty;	///上日持仓量
	TKSD_VolumeType		Qty;	///今日持仓量
	TKSD_VolumeType		OffsetLastQty;	///可平昨
	TKSD_VolumeType		OffsetTodayQty;	///可平今
	TKSD_PriceType		Amt;	///持仓额
	TKSD_PriceType		Margin;	///保证金
	TKSD_PriceType		AvePrice;	///持仓均价
	TKSD_PriceType		LastPrice;	///最新价
	TKSD_PriceType		FloatProfitLoss;	///持仓盈亏
};

///市场状态应答
/*struct CKSD_RspMarketStatus
{
	///市场状态
	TKSD_MktStatusType   MktStatus;           
	///状态触发时间
	TKSD_TimeType	MktChgTime;
};
*/

///市场状态变化通知
struct CKSD_RtnMarketStatus
{
	TKSD_MktStatusType  MktStatus; 	///市场状态          
	TKSD_TimeType		MktChgTime;	///状态触发时间
};

///合约查询应答
struct CKSD_RspInstrumentField
{

	TKSD_ContractIDType		ContractID; 	///合约代码       
	TKSD_ContractNameType	ContractName;	///合约名称
	TKSD_VarietyIDType   	VarietyID;  	///交割品种代码
	TKSD_VolumeMultipleType	Unit;	///合约数量乘数
	TKSD_MeasureUnit   		MeasureUnit;  	//计价单位       
	TKSD_PriceType			Tick;	///最小变动价位
	TKSD_VolumeType			MaxHand;	///市价单最大下单量
	TKSD_VolumeType			MinHand;	///市价单最小下单量
	TKSD_VolumeType			MaxMarketOrderVolume;	///限价单最大下单量
	TKSD_VolumeType			MinMarketOrderVolume;	///限价单最小下单量
	TKSD_PriceType			RiseLimit;	///涨停板
	TKSD_PriceType			FallLimit;	///跌停板
	TKSD_PriceType			LastClearPrice;	///上日结算价
};

///下单请求
struct CKSD_ReqOrderField
{
	TKSD_LocalOrderNo 	LocalOrderNo;	///本地委托号	
	TKSD_TraderIDType	TraderNo;///用户代码	
	TKSD_ContractIDType	ContractID;///合约代码	
	TKSD_ByteType		BsFlag;///买卖标志	
	TKSD_ByteType		EoFlag;///开平标志
	TKSD_PriceType		Price;	///价格	
	TKSD_VolumeType		Qty;///数量
	TKSD_ByteType			OrderType;	///定单类型
};

///下单应答
struct CKSD_RspOrderField
{	
	TKSD_LocalOrderNo 	LocalOrderNo;///本地委托号
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_ByteType		BsFlag;	///买卖标志	
	TKSD_ByteType		EoFlag;///开平标志
	TKSD_PriceType		Price;	///价格	
	TKSD_VolumeType		Qty;///数量
	TKSD_ByteType		OrderType;	///定单类型
};

///下单回报
struct CKSD_RtnOrderField
{
	TKSD_SysOrderNo 	SysOrderNo;	///系统委托号
	TKSD_LocalOrderNo 	LocalOrderNo;	///本地委托号
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_ByteType		BsFlag;	///买卖标志
	TKSD_ByteType		EoFlag;	///开平标志
	TKSD_PriceType		Price;	///价格
	TKSD_VolumeType		Qty;	///数量
	TKSD_ByteType		OrderType;	///定单类型
	TKSD_TimeType		OrderTime;	///委托时间
	TKSD_Status			Status;	///状态
	TKSD_VolumeType		RemainAmt;	///剩余数量
};

///撤单请求
struct CKSD_ReqOrderCancelField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_SysOrderNo 	SysOrderNo;	///系统委托号
};

///撤单应答
struct CKSD_RspOrderCancelField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_SysOrderNo 	SysOrderNo;	///系统委托号
};

///撤单响应
struct CKSD_RtnOrderCancelField
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_SysOrderNo 	SysOrderNo;	///系统委托号
	TKSD_LocalOrderNo 	LocalOrderNo;	///本地委托号
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_TimeType		ActionTime;	///操作时间
	TKSD_VolumeType		OrderCancelQty;	///撤单数量
	TKSD_ByteType		OrderType;	///定单类型
};

///成交回报通知
struct CKSD_RtnTradeField
{
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_MatchNo		MatchNo;	///成交号
	TKSD_TimeType		MatchTime;	///成交时间
	TKSD_DateType		MatchDate;	///成交日期
	TKSD_PriceType		Price;	///成交价格
	TKSD_VolumeType		Qty;	///成交数量
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_ByteType		BsFlag;	///买卖标志
	TKSD_ByteType		EoFlag;	///开平标志
	TKSD_LocalOrderNo 	LocalOrderNo;	///本地委托号
};

///深度行情
struct CKSD_DepthMarketDataField
{
	TKSD_DateType		TradingDay;	///交易日
	TKSD_ContractIDType	ContractID;	///合约代码
	TKSD_PriceType		LastPrice;	///最新价
	TKSD_PriceType		HighPrice;	///最高价
	TKSD_PriceType		LowPrice;	///最低价
	TKSD_VolumeType		MatchTotQty;	///成交量
	TKSD_WeightType		MatchWeight;	///成交重量
	TKSD_MoneyType		Turnover;	///成交额
	TKSD_VolumeType		OpenInterest;	///持仓量
	TKSD_PriceType		OpenPrice;	///开盘价
	TKSD_PriceType		ClosePrice;	///收盘价
	TKSD_PriceType		ClearPrice;	///今结算价
	TKSD_PriceType		LastClearPrice;	///上日结算价
	TKSD_PriceType		LastClose;	///上日收盘价
	TKSD_PriceType		RiseLimit;	///涨停板
	TKSD_PriceType		FallLimit;	///跌停板
	TKSD_PriceType		UpDown;	///涨跌
	TKSD_PriceType		UpDownRate;	///涨跌幅度
	TKSD_PriceType		AveragePrice;	///当日均价
	TKSD_PriceType		BidPrice1;	///申买价一
	TKSD_VolumeType		BidVolume1;	///申买量一
	TKSD_PriceType		AskPrice1;	///申卖价一
	TKSD_VolumeType		AskVolume1;	///申卖量一
	TKSD_PriceType		BidPrice2;	///申买价二
	TKSD_VolumeType		BidVolume2;	///申买量二
	TKSD_PriceType		AskPrice2;	///申卖价二
	TKSD_VolumeType		AskVolume2;	///申卖量二
	TKSD_PriceType		BidPrice3;	///申买价三
	TKSD_VolumeType		BidVolume3;	///申买量三
	TKSD_PriceType		AskPrice3;	///申卖价三
	TKSD_VolumeType		AskVolume3;	///申卖量三
	TKSD_PriceType		BidPrice4;	///申买价四
	TKSD_VolumeType		BidVolume4;	///申买量四
	TKSD_PriceType		AskPrice4;	///申卖价四
	TKSD_VolumeType		AskVolume4;	///申卖量四
	TKSD_PriceType		BidPrice5;	///申买价五
	TKSD_VolumeType		BidVolume5;	///申买量五
	TKSD_PriceType		AskPrice5;	///申卖价五
	TKSD_VolumeType		AskVolume5;	///申卖量五
    
};


struct CKSD_ReqTraderPwdUpd
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_MemberIDType   MemberID;	///会员号	
    TKSD_PasswordType   OldPwd;  	///旧密码    
   	TKSD_PasswordType   NewPwd;    	///新密码           
};

struct  CKSD_RspTraderPwdUpd
{
	TKSD_TraderIDType	TraderNo;	///用户代码
	TKSD_MemberIDType  	MemberID;	///会员号	
    TKSD_PasswordType  	OldPwd;   	///旧密码   
   	TKSD_PasswordType  	NewPwd;   	///新密码            
};
////////////


//市场状态应答
struct CKSD_RspMarketStatus
{	
	TKSD_MktStatusType   MktStatus;  ///市场状态         
	TKSD_TimeType		 MktChgTime;	///状态触发时间
};


//查询期货品种请求
struct  CKSD_ReqQryFtrVariety
{
	TKSD_VarietyIDType  VarietyID;   	///品种代码         
};
//查询期货品种应答
struct  CKSD_RspQryFtrVariety
{	
	TKSD_VarietyIDType  VarietyID;		///品种代码
	TKSD_Currency   	Currency;  		///币种   
	TKSD_VarietyName  	VarietyName;  	///品种名称       
	TKSD_VarietyEName 	VarietyEName;    ///品种英文名称            
};
//查询期货合约请求
struct  CKSD_ReqQryFtrContract
{
	TKSD_ContractIDType   ContractID;  	///合约编码                  
};
//查询期货合约应答
struct  CKSD_RspQryFtrContract
{
	TKSD_ExchCode			ExchCode; 				///交易所代码
	TKSD_ContractIDType		ContractID; 			///合约编码	
	TKSD_Currency			Currency; 				///币种 
	TKSD_ContractNameType   ContractName;  			///合约名称	
	TKSD_VarietyIDType		VarietyId; 				///品种代码		
	TKSD_UVolumeType		Unit;					///每手乘数
	TKSD_MeasureUnit		MeasureUnit;			///计价单位	  
	TKSD_PriceType			Tick;   				///最小价位   
	TKSD_UVolumeType        MaxHand;  				///限价单最大可下单手数
	TKSD_UVolumeType        MinHand;				///限价单最小可下单手数		
	TKSD_UVolumeType        MaxMarketOrderVolume;	///市价单最大下单量	
	TKSD_UVolumeType        MinMarketOrderVolume;	///市价单最小下单量
	TKSD_PriceType          RefPrice;				///挂牌基准价
	TKSD_CByteType          Status;  				///合约状态	 	
	TKSD_DateType			EndDeliveryDate;		///终止交割日期		
	TKSD_PriceType          RiseLimit;				///涨停板 
	TKSD_PriceType          FallLimit;    			///跌停板	       
	TKSD_AttrType           TradeType;				/*市场*/
	TKSD_ByteType           QuoteMode;				//报价模式 0-自动 1-手动
	TKSD_ContractCodeType	ContractCode;			//合约业务代码
};
//查询客户请求
struct CKSD_ReqTraderQryClient
{
	TKSD_TraderIDType	TraderNo; 	///用户代码      
};
//查询客户应答
struct  CKSD_RspTraderQryClient
{
	TKSD_MemberIDType   MemberID;  	///会员号
	TKSD_ClientIDType  	ClientID;  	///客户号          	
	TKSD_ExchCode   	ExchCode;	///交易所代码
	TKSD_CByteType     	Status;  	///状态
	TKSD_AttrType   	Attr;		///交易编码属性		
	TKSD_AbbrType		Abbr;   	///客户简称
	TKSD_AttrType		IfQuote;    //是否金交所报价商席位
};

//查询交易员持仓结构：
struct  CKSD_ReqTraderQryPosi
{	
	TKSD_TraderIDType	TraderNo;  ///用户代码     
};

//查询交易员持仓应答
struct  CKSD_RspTraderQryPosi
{
	TKSD_MemberIDType   	MemberID;  	///会员号          
	TKSD_ClientIDType  		ClientID; 	///客户号
	TKSD_TraderIDType  		TraderNo; 	///交易员号hxs	
	TKSD_ContractIDType  	ContractID;	///合约号
	TKSD_CByteType          ShFlag;  	///投保标志hxs
	TKSD_UVolumeType        LastBuyQty;	///上日买持仓量	 
	TKSD_UVolumeType        LastSellQty;	///上日卖持仓量	
	TKSD_UVolumeType        TodayBuyQty;	///今日新买持仓量
	TKSD_UVolumeType        TodaySellQty;	///今日新卖持仓量	
	TKSD_UVolumeType        BuyQty; 	///买持仓量
	TKSD_UVolumeType        SellQty;	///卖持仓量	
	TKSD_PriceType          BuyAmt; 	///买持仓额	
	TKSD_PriceType          SellAmt; 	///卖持仓额
	TKSD_UVolumeType        BuyOpenQty;	///当日买开仓量	
	TKSD_UVolumeType        SellOpenQty; 	///当日卖开仓量	
	TKSD_UVolumeType        BuyOffsetQty; 	///当日买平仓量		
	TKSD_UVolumeType        SellOffsetQty; 	///当日卖平仓量
	TKSD_UVolumeType        BuyOffsetTodayFrozenQty;	///当日买平仓冻结
	TKSD_UVolumeType        SellOffsetTodayFrozenQty;	///当日卖平仓冻结
	TKSD_UVolumeType        BuyOffsetLastFrozenQty;	///当日买平昨仓冻结
	TKSD_UVolumeType        SellOffsetLastFrozenQty;	///当日卖平昨仓冻结
	TKSD_ActArbiContractIDType  ActArbiContractID;	 ///套利合约号(dimple) 
	TKSD_TradePurposeType   TradePurpose;   	///交易目的	     
};


//查询客户信用额度请求
struct  CKSD_ReqTraderQryMoney
{
	TKSD_ExchCode			ExchCode;   ///交易所代码
	TKSD_MemberIDType   	MemberID;  	///会员号
	TKSD_TraderIDType		TraderNo; 	///用户代码   
	TKSD_Currency			Currency;   ///币种

};

//查询客户信用额度应答
struct  CKSD_RspTraderQryMoney
{
	TKSD_Currency			Currency;            /*币种*/
	TKSD_ExchCode			ExchCode;			 /*交易所代码*/
	TKSD_MemberIDType   	MemberID;  			 /*会员号*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_PriceType          CreditTot;           /*信用额度*/
	TKSD_PriceType          CreditUsed;          /*已用信用额度*/
	TKSD_PriceType          CreditFrozen;        /*冻结信用额度*/
	TKSD_PriceType          CreditRemain;        /*剩余信用额度*/
	TKSD_PriceType          FloatProfitLoss;     /*累计持仓盈亏*/
	TKSD_PriceType          OffsetProfitLoss;    /*累计平仓盈亏*/
};
//查询交易员敞口请求
struct  CKSD_ReqTraderExposureQry
{
	TKSD_TraderIDType	TraderNo;    	///用户代码   
};

//查询交易员敞口应答
struct  CKSD_RspTraderExposureQry
{
	TKSD_MemberIDType   	MemberID;  			 /*会员号*/
	TKSD_TraderIDType		TraderNo;            /*交易员*/
	TKSD_VarietyIDType		VarietyID;           /*品种代码*/
	TKSD_CByteType          TradeType;           /*市场*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_PriceType          UsedExposure;        /*已用敞口*/
	TKSD_PriceType			DayExposure;         /*日中敞口额度*/
	TKSD_PriceType          FrozenExposure;      /*已冻结敞口*/
};

//查询自营交易员资金请求：
struct  CKSD_ReqTraderMoneyQry
{
	TKSD_TraderIDType	TraderNo;  	///用户代码    
	TKSD_MemberIDType		MemberID ;           //会员号
};
//查询自营交易员资金应答
struct  CKSD_RspTraderMoneyQry
{
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_TraderIDType		TraderNo;            /*交易员*/
	TKSD_PriceType          FrozenFund;          /*委托冻结资金*/
	TKSD_PriceType          OccupyFund;          /*占用资金*/
	TKSD_PriceType          ProfitFund;          /*平仓盈亏*/
};


//查询交易员持仓汇总请求：
struct  CKSD_ReqTraderPosiAllQry
{
	TKSD_MemberIDType			MemberID ;           /*会员号*/
	TKSD_TraderIDType			TraderNo;            /*交易员*/
	TKSD_ContractIDType			ContractId;          /*合约号*/
	TKSD_CByteType				ContractType;        /*合约类型(dimple)*/
    TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
    TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	
};
//交易员持仓汇总应答
struct CKSD_RspTraderPosiAllQry
{
	TKSD_MemberIDType		MemberID ;				/*会员号*/
	TKSD_ClientIDType		ClientID ;				/*客户号*/
	TKSD_TraderIDType		TraderNo ;				/*交易员号*/
	TKSD_ActArbiContractIDType  ActArbiContractId ; /*套利合约号*/
	TKSD_ContractIDType		ContractID ;			/*合约号*/
	TKSD_CByteType          BsFlag ;				/*买卖标志*/
	TKSD_CByteType          ShFlag ;				/*投保标志*/
	TKSD_UVolumeType        LastQty ;				/*上日持仓量*/
	TKSD_UVolumeType        Qty ;					/*持仓量*/
	TKSD_UVolumeType        OffsetQty ;				/*可平量 成交量*/
	TKSD_UVolumeType        OffsetLastQty ;			/*可平昨 未成交数量*/
	TKSD_UVolumeType        OffsetTodayQty ;		/*可平今 撤单数量*/
	TKSD_PriceType          Exposure ;				/*敞口*/
	TKSD_PriceType          Amt ;					/*持仓额*/
	TKSD_PriceType          Margin ;				/*保证金*/
	TKSD_PriceType          AvePrice ;				/*持仓均价*/
	TKSD_PriceType          LastPrice ;				/*最新价*/
	TKSD_PriceType          ProfitFund;				/*平仓盈亏*/
	TKSD_PriceType          FloatProfitLoss;		/*持仓盈亏*/
	TKSD_PriceType			ProfitLossTodayFloating;/*当日浮动盈亏*/
	TKSD_PriceType			ProfitLossTotal;		/*累计浮动盈亏*/
	TKSD_TradePurposeType   TradePurpose;			/*交易目的*/ 
};

//查询交易员持仓明细请求：
struct  CKSD_ReqTraderPosiDtlQry
{
	TKSD_TraderIDType			TraderNo;            /*交易员*/
	TKSD_MemberIDType			MemberID ;           /*会员号*/
	TKSD_ContractIDType			ContractId;          /*合约号*/
	TKSD_CByteType				ContractType;        /*合约类型(dimple)*/
    TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
    TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	
};
//查询交易员持仓明细应答
struct CKSD_RspTraderPosiDtlQry
{
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_ClientIDType		ClientID ;           /*客户号*/
	TKSD_TraderIDType		TraderNo ;           /*交易员号*/
	TKSD_ActArbiContractIDType  ActArbiContractId ;  /*套利合约号*/
	TKSD_ContractIDType		ContractID ;         /*合约号*/
	TKSD_CByteType          BsFlag ;             /*买卖标志*/
	TKSD_CByteType          ShFlag ;             /*投保标志*/
	TKSD_UVolumeType        Qty ;                /*持仓量*/
	TKSD_DateType			MatchDate ;          /*成交日期*/
	TKSD_MatchNo			MatchNo ;            /*成交号*/
	TKSD_MatchNo			MatchBatchNo ;       /*成交批次号*/
	TKSD_PriceType          Price ;              /*成交价 成交均价*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_PriceType          ProfitLossTodayFloating;/*当日浮动盈亏*/
	TKSD_PriceType          ProfitLossTotal;     /*累计盈亏*/
};

//成交明细查询请求
struct  CKSD_ReqMatchDtlQry
{
	TKSD_TraderIDType		TraderNo;            /*交易员*/
	TKSD_ContractIDType		ContractId;          /*合约号*/
	TKSD_CByteType          ContractType;        /*合约类型(dimple)*/
    
};
//成交明细查询应答
struct CKSD_RspMatchDtlQry
{
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_ClientIDType		ClientID ;           /*客户号*/
	TKSD_TraderIDType		TraderNo ;           /*交易员号*/
	TKSD_ActArbiContractIDType  ActArbiContractId ;  /*套利合约号*/
	TKSD_ContractIDType		ContractID ;         /*合约号*/
	TKSD_CByteType          BsFlag ;             /*买卖标志*/
	TKSD_CByteType          ShFlag ;             /*投保标志*/
	TKSD_UVolumeType        Qty ;                /*持仓量*/
	TKSD_UVolumeType        OffsetQty ;          /*可平量 成交量*/
	TKSD_DateType			MatchDate ;          /*成交日期*/
	TKSD_MatchNo			MatchNo ;            /*成交号*/
	TKSD_MatchNo			StrMatchNo ;         /*字符串成交号*/
	TKSD_MatchNo			MatchBatchNo ;       /*成交批次号*/
	TKSD_PriceType          Price ;              /*成交价 成交均价*/
	TKSD_CByteType          EoFlag;              /*开平标志*/
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地委托号*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
};

//委托汇总查询请求
struct  CKSD_ReqOrderAllQry
{
	TKSD_TraderIDType		TraderNo;            /*交易员*/
	TKSD_ContractIDType		ContractId;          /*合约号*/
	TKSD_CByteType          ContractType;        /*合约类型(dimple)*/
    
};
//委托汇总查询应答
struct CKSD_RspOrderAllQry
{
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_ClientIDType		ClientID ;           /*客户号*/
	TKSD_TraderIDType		TraderNo ;           /*交易员号*/
	TKSD_ActArbiContractIDType  ActArbiContractId ;  /*套利合约号*/
	TKSD_ContractIDType		ContractID ;         /*合约号*/
	TKSD_CByteType          BsFlag ;             /*买卖标志*/
	TKSD_CByteType          ShFlag ;             /*投保标志*/
	TKSD_UVolumeType        Qty ;                /*持仓量*/
	TKSD_UVolumeType        OffsetQty ;          /*可平量 成交量*/
	TKSD_UVolumeType        OffsetLastQty ;      /*可平昨 未成交数量*/
	TKSD_UVolumeType        OffsetTodayQty ;     /*可平今 撤单数量*/
	TKSD_PriceType          AvePrice ;           /*持仓均价*/
	TKSD_PriceType          Price ;              /*成交价 成交均价*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
};

//委托明细查询请求
struct  CKSD_ReqOrderDtlQry
{
	TKSD_TraderIDType		TraderNo;            /*交易员*/
	TKSD_ContractIDType		ContractId;          /*合约号*/
	TKSD_CByteType          ContractType;        /*合约类型(dimple)*/
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号*/    
};
//委托明细查询应答
struct CKSD_RspOrderDtlQry
{
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_ClientIDType		ClientID ;           /*客户号*/
	TKSD_TraderIDType		TraderNo ;           /*交易员号*/
	TKSD_ActArbiContractIDType  ActArbiContractId ;  /*套利合约号*/
	TKSD_ContractIDType		ContractID ;         /*合约号*/
	TKSD_CByteType          BsFlag ;             /*买卖标志*/
	TKSD_CByteType          ShFlag ;             /*投保标志*/
	TKSD_UVolumeType        Qty ;                /*持仓量*/
	TKSD_UVolumeType        OffsetQty ;          /*可平量 成交量*/
	TKSD_UVolumeType        OffsetLastQty ;      /*可平昨 未成交数量*/
	TKSD_UVolumeType        OffsetTodayQty ;     /*可平今 撤单数量*/
	TKSD_PriceType          AvePrice ;           /*持仓均价*/
	TKSD_DateType			MatchDate ;          /*成交日期*/
	TKSD_MatchNo			MatchBatchNo ;       /*成交批次号*/
	TKSD_PriceType          Price ;              /*成交价 成交均价*/
	TKSD_CByteType          EoFlag;              /*开平标志*/
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地委托号*/
	TKSD_StatusType			Status;              /*状态*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
};

//查询约请求
struct  CKSD_ReqContract
{
	TKSD_ContractIDType  ContractID;          /*合约号*/    
};
//查询套利合约应答
struct CKSD_RspFldFtrArbiContract
{
	TKSD_ActArbiContractIDType   arbi_contract_id;   /*套利合约号*/
	TKSD_ContractIDType		leg1;                /*腿1合约号*/
	TKSD_ContractIDType		leg2;                /*腿2合约号*/
	TKSD_ContractIDType		leg3;                /*腿3合约号*/
	TKSD_PriceType			leg1_qty;          /*腿1数量*/
	TKSD_PriceType          leg2_qty;            /*腿2数量*/
	TKSD_PriceType          leg3_qty;            /*腿3数量*/
	TKSD_UVolumeType        max_hand;            /*最大下单手数*/
	TKSD_UVolumeType        min_hand;            /*最小下单手数*/
	TKSD_PriceType          tick;               /*最小变动价位*/
	TKSD_ContractNameType	buy_perf_contract_id;/*买组合合约号*/
	TKSD_PriceType          buy_ftr_ratio;       /*买组合合约的期货保证金和比例*/
	TKSD_ContractNameType	sell_perf_contract_id;/*卖组合合约号*/
	TKSD_PriceType			sell_ftr_ratio;      /*卖组合合约的期货保证金和比例*/
	TKSD_DateType			logout_date;         /*摘牌日期*/
	TKSD_CByteType          status;              /*合约状态*/
};

//查询客户库存请求
struct  CKSD_ReqClientQryStorage
{
	TKSD_TraderIDType  TraderNo ;           /*交易员号*/  
};
//查询客户库存应答
struct CKSD_RspClientQryStorage
{
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_ClientIDType		ClientID ;           /*客户号*/
	TKSD_TraderIDType		TraderNo ;           /*交易员号*/
	TKSD_VarietyIDType		VarietyID;           /*交割品种代码*/
	TKSD_PriceType          TotalStorage;        /*库存总量*/
	TKSD_PriceType          AvailableStorage;    /*可用库存*/
	TKSD_PriceType          FrozenStorage;       /*现货冻结库存*/
	TKSD_PriceType          PendStorage;         /*待提库存*/
	TKSD_PriceType          ImpawnStorage;       /*质押库存*/
	TKSD_PriceType          LawFrozen;           /*法律冻结库存*/
	TKSD_PriceType          SetoffFrozen;        /*充抵冻结库存*/
	TKSD_PriceType          TransferFrozen;      /*过户业务冻结库存*/
};

//查询交易员库存请求
struct  CKSD_ReqTraderQryStorage
{
	TKSD_TraderIDType  TraderNo ;           /*交易员号*/  
};
//查询交易员库存应答
struct CKSD_RspTraderQryStorage
{
	TKSD_TraderIDType		TraderNo ;           /*交易员号*/
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ContractIDType		ContractID;			 /*合约代码*/
	TKSD_VarietyIDType		VarietyID;           /*交割品种代码*/
	TKSD_VarietyName		VarietyName;         /*交割品种名称*/
	TKSD_PriceType          TotalStorage;        /*库存总量*/
	TKSD_PriceType          AvailableStorage;    /*可用库存*/
	TKSD_PriceType          FrozenStorage;       /*现货冻结库存*/
	TKSD_PriceType          PendStorage;         /*待提库存*/
	TKSD_PriceType          ImpawnStorage;       /*质押库存*/
	TKSD_PriceType          LawFrozen;           /*法律冻结库存*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_PriceType          SetoffFrozen;        /*充抵冻结库存*/
	TKSD_PriceType          TransferFrozen;      /*过户业务冻结库存*/
};


//成交统计信息查询请求
struct  CKSD_ReqQryTraderMatchStat
{
	TKSD_TraderIDType  TraderNo;            /*委托席位号*/
};
//成交统计信息查询应答
struct CKSD_RspTraderMatchStatQry
{
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_ClientIDType		ClientID ;           /*客户号*/
	TKSD_TraderIDType		TraderNo;            /*交易员*/
	TKSD_ContractIDType		ContractId;          /*合约号*/
	TKSD_CByteType           ShFlag;              /*投保标志*/
	TKSD_UVolumeType        BuyMatchQty;         /*买成交量*/
	TKSD_PriceType          BuyAvePrice;         /*买均价*/
	TKSD_UVolumeType        SellMatchQty;        /*卖成交量*/
	TKSD_PriceType          SellAvePrice;        /*卖均价*/ 
};

//交易所资金查询请求
struct  CKSD_ReqQryExchMoney
{
	TKSD_ExchCode      ExchCode;            /*交易所代码*/
	TKSD_TraderIDType  TraderNo;            /*委托席位号*/
	TKSD_MemberIDType		MemberID ;           /*会员号*/
};
//交易所资金查询应答
struct CKSD_RspQryExchMoney
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_TraderIDType  TraderNo;            /*委托席位号*/
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_PriceType          PreBalance;          /*上日可用资金及额度*/
	TKSD_PriceType          LastMargin;          /*上日交易保证金*/
	TKSD_PriceType          MoneyIn;             /*当日入金*/
	TKSD_PriceType          MoneyOut;            /*当日出金*/
	TKSD_PriceType          FrozenMargin;              /*当日冻结保证金*/
	TKSD_PriceType          OccupiedMargin;             /*当日占用保证金*/
	TKSD_PriceType          Balance;        /*可用资金及额度*/
	TKSD_PriceType          AllBalance;        /*总资金及额度*/
};

//市场状态查询应答   
struct CKSD_RspQryMktStatus
{
	TKSD_StatusType   MktStatus;           /*市场状态*/
	TKSD_ExchCode     ExchCode;            /*交易所代码*/
	TKSD_TimeType     MktChgTime;          /*状态触发时间*/
};

//交易所市场状态通知
struct CKSD_NtyQryMktStatus
{
	TKSD_StatusType   MktStatus;           /*市场状态*/
	TKSD_ExchCode	  ExchCode;            /*交易所代码*/
	TKSD_TimeType	  MktChgTime;          /*状态触发时间*/
};

//交易员取消定单请求
struct CKSD_ReqTraderCancelOrder
{
	TKSD_TraderIDType 		TraderNo;	/*会员号*/
	TKSD_MemberIDType 		MemberID;		/*会员号*/
	TKSD_UVolumeType 		OrderBatchNo;	/*委托批次号*/
	TKSD_ContractIDType 	ContractID;			//合约号
	TKSD_TraderIDType 		CancelTraderNo;		//席位号
	TKSD_LocalOrderNo 		LocalOrderNo;  //本地定单号
	TKSD_CByteType 			OrderSrc;	//定单来源
	TKSD_SysOrderNo 		SysOrderNo;  //系统定单号
}; 
//交易员取消定单应答
struct CKSD_RspTraderCancelOrder
{
	TKSD_TraderIDType 		TraderNo;	/*会员号*/
	TKSD_MemberIDType 		MemberID;		/*会员号*/
	TKSD_UVolumeType 		OrderBatchNo;	/*委托批次号*/
	TKSD_ContractIDType 	ContractID;			//合约号
	TKSD_TraderIDType 		CancelTraderNo;		//席位号
	TKSD_LocalOrderNo 		LocalOrderNo;  //本地定单号
	TKSD_CByteType 			OrderSrc;	//定单来源
	TKSD_SysOrderNo 		SysOrderNo;  //系统定单号
		
};
//交易员撤单请求
struct CKSD_ReqTraderQuitOrder
{
	TKSD_TraderIDType 		TraderNo;			/*交易员*/
	TKSD_MemberIDType 		MemberID;			/*会员号*/
	TKSD_ContractIDType 	ContractID;			/*合约号*/
	TKSD_TraderIDType 		CancelTraderNo;		/*席位号*/
	TKSD_LocalOrderNo 		LocalOrderNo;		/*本地定单号*/
	TKSD_SysOrderNo 		SysOrderNo;			/*系统定单号*/
}; 
//交易员撤单应答
struct CKSD_RspTraderQuitOrder
{
	TKSD_TraderIDType 		TraderNo;		/*交易员*/
	TKSD_MemberIDType 		MemberID;		/*会员号*/
	TKSD_ClientIDType		ClientID ;      /*客户号*/
	TKSD_UVolumeType 		OrderBatchNo;	/*委托批次号*/
	TKSD_ContractIDType 	ContractID;		/*合约号*/
	TKSD_TraderIDType 		CancelTraderNo;	/*席位号*/
	TKSD_LocalOrderNo 		LocalOrderNo;   /*本地定单号*/
	TKSD_SysOrderNo 		SysOrderNo;		/*系统定单号*/
	TKSD_ExchCode			ExchCode;       /*交易所代码*/
	TKSD_TimeType			ActionTime;     /*操作时间*/
	TKSD_UVolumeType 		OrderCancelQty; /*撤单数量*/
};

//资金通知
struct CKSD_NtyTraderNoCap
{
	TKSD_Currency			Currency;            /*币种*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_PriceType          CreditTot;           /*信用额度*/
	TKSD_PriceType          CreditUsed;          /*已用信用额度*/
	TKSD_PriceType          CreditFrozen;        /*冻结信用额度*/
	TKSD_PriceType          CreditRemain;        /*剩余信用额度*/
	TKSD_PriceType          FloatProfitLoss;     /*累计持仓盈亏*/
	TKSD_PriceType          OffsetProfitLoss;    /*累计平仓盈亏*/ 
};
//持仓通知
struct CKSD_NtyTraderPosi
{
	TKSD_MemberIDType		  MemberID;            /*会员号*/
	TKSD_ClientIDType		  ClientID;            /*客户号*/
	TKSD_TraderIDType		  TraderNo;            /*交易员号hxs*/
	TKSD_ContractIDType	      ContractID;          /*合约号*/
	TKSD_CByteType            ShFlag;              /*投保标志*/
	TKSD_UVolumeType          LastBuyQty;          /*上日买持仓量*/
	TKSD_UVolumeType          LastSellQty;         /*上日卖持仓量*/
	TKSD_UVolumeType          TodayBuyQty;         /*今日新买持仓量*/
	TKSD_UVolumeType          TodaySellQty;        /*今日新卖持仓量*/
	TKSD_UVolumeType          BuyQty;              /*买持仓量*/
	TKSD_UVolumeType          SellQty;             /*卖持仓量*/
	TKSD_PriceType            BuyAmt;              /*买持仓额*/
	TKSD_PriceType            SellAmt;             /*卖持仓额*/
	TKSD_UVolumeType          BuyOpenQty;          /*当日买开仓量*/
	TKSD_UVolumeType          SellOpenQty;         /*当日卖开仓量*/
	TKSD_UVolumeType          BuyOffsetQty;        /*当日买平仓量*/
	TKSD_UVolumeType          SellOffsetQty;       /*当日卖平仓量*/
	TKSD_UVolumeType          BuyOffsetTodayFrozenQty;/*当日买平仓冻结*/
	TKSD_UVolumeType          SellOffsetTodayFrozenQty;/*当日卖平仓冻结*/
	TKSD_UVolumeType          BuyOffsetLastFrozenQty;/*当日买平昨仓冻结*/
	TKSD_UVolumeType          SellOffsetLastFrozenQty;/*当日卖平昨仓冻结*/
	TKSD_TradePurposeType	  TradePurpose;        /*交易目的*/ 
};
//期权持仓通知
struct CKSD_NtyOptMixPosi
{
	TKSD_MemberIDType		  MemberID;            /*会员号*/
	TKSD_ClientIDType		  ClientID;            /*客户号*/
	TKSD_TraderIDType		  TraderNo;            /*交易员号hxs*/
	TKSD_ContractIDType	      ContractID;          /*合约号*/
	TKSD_CByteType            ShFlag;              /*投保标志*/
	TKSD_DateType			  TradeDate;           /*交易日期*/
	TKSD_UVolumeType          LastBuyQty;          /*上日买持仓量*/
	TKSD_UVolumeType          LastSellQty;         /*上日卖持仓量*/
	TKSD_UVolumeType          TodayBuyQty;         /*今日新买持仓量*/
	TKSD_UVolumeType          TodaySellQty;        /*今日新卖持仓量*/
	TKSD_UVolumeType          BuyQty;              /*买持仓量*/
	TKSD_UVolumeType          SellQty;             /*卖持仓量*/
	TKSD_PriceType            BuyAmt;              /*买持仓额*/
	TKSD_PriceType            SellAmt;             /*卖持仓额*/
	TKSD_UVolumeType          BuyOpenQty;          /*当日买开仓量*/
	TKSD_UVolumeType          SellOpenQty;         /*当日卖开仓量*/
	TKSD_UVolumeType          BuyOffsetQty;        /*当日买平仓量*/
	TKSD_UVolumeType          SellOffsetQty;       /*当日卖平仓量*/
	TKSD_UVolumeType          BuyOffsetTodayFrozenQty;/*当日买平仓冻结*/
	TKSD_UVolumeType          SellOffsetTodayFrozenQty;/*当日卖平仓冻结*/
	TKSD_UVolumeType          BuyOffsetLastFrozenQty;/*当日买平昨仓冻结*/
	TKSD_UVolumeType          SellOffsetLastFrozenQty;/*当日卖平昨仓冻结*/
	TKSD_UVolumeType          ExecTodayFrozenQty;  /*当日执行今仓冻结*/
	TKSD_UVolumeType          ExecLastFrozenQty;   /*当日执行昨仓冻结*/
	TKSD_UVolumeType          SelfCloseTodayFrozenQty;/*当日自对冲今仓冻结*/
	TKSD_UVolumeType          SelfCloseLastFrozenQty;/*当日自对冲昨仓冻结*/
	TKSD_TradePurposeType	  TradePurpose;        /*交易目的*/
};
//交易员定单请求
struct  CKSD_ReqTraderInsertOrders
{
	TKSD_LocalOrderNo			LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_PriceType				StopPrice;           /*止损(盈)价*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/ 
};
//交易员定单应答
struct  CKSD_RspTraderInsertOrders
{
	TKSD_LocalOrderNo			LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType			    EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_PriceType				StopPrice;           /*止损(盈)价*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/ 
};
//交易员定单回报
struct CKSD_RtnTraderInsertOrders
{
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号int转为20位字符*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_TraderIDType		TraderNo;            /*委托席位号*/
	TKSD_MemberIDType		MemberID;            /*会员编号*/
	TKSD_ClientIDType		ClientID;            /*客户编号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_CByteType          BsFlag;              /*买卖标志*/
	TKSD_CByteType          EoFlag;              /*开平标志*/
	TKSD_CByteType          ShFlag;              /*投保标志*/
	TKSD_PriceType          Price;               /*价格*/
	TKSD_UVolumeType        Qty;                 /*数量*/
	TKSD_CByteType          OrderType;           /*定单类型*/
	TKSD_CByteType          OrderAttr;           /*定单属性*/
	TKSD_TimeType			OrderTime;           /*委托时间*/
	TKSD_UVolumeType        OrderBatchNo;        /*委托批次号*/
	TKSD_CByteType          TradeType;           /*交易类型*/
	TKSD_DateType			TradingDay;          /*交易日*/
	TKSD_StatusType			Status;              /*状态*/
	TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
	TKSD_UVolumeType		 RemainAmt;           /*剩余数量(dimple)*/
	TKSD_CByteType           Type;                /*类型(dimple)*/
	TKSD_TradePurposeType	 TradePurpose;        /*交易目的*/
};
//交易员交割中立仓定单请求
struct  CKSD_ReqTraderInsertDeliveryOrders
{
	TKSD_LocalOrderNo		 LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_TraderIDType	     TraderNo;            /*委托席位号*/
	TKSD_MemberIDType		 MemberID;            /*会员编号*/
	TKSD_ClientIDType		 ClientID;            /*客户编号*/
	TKSD_ContractIDType		 ContractID;          /*合约号*/
	TKSD_CByteType           BsFlag;              /*买卖标志*/
	TKSD_CByteType           ShFlag;              /*投保标志*/
	TKSD_UVolumeType         Qty;                 /*数量*/
	TKSD_TimeType			 OrderTime;           /*委托时间*/
	TKSD_TradePurposeType    TradePurpose;        /*交易目的*/ 
	TKSD_CByteType			 MidFlag;			  /*是否中立仓*/
};
//交易员交割中立仓撤单应答
struct CKSD_RspTraderQuitDeliveryOrder
{
	TKSD_MemberIDType		 MemberID;            /*会员号*/
	TKSD_ExchCode			 ExchCode;            /*交易所代码*/
	TKSD_SysOrderNo			 SysOrderNo;          /*系统委托号*/
	TKSD_LocalOrderNo		 LocalOrderNo;        /*本地定单号*/
	TKSD_ContractIDType		 ContractID;          /*合约号*/
	TKSD_TraderIDType		 TraderNo;            /*委托席位号*/
	TKSD_TraderIDType		 CancelTraderNo;      /*撤单席位号*/
	TKSD_CByteType           OrderSrc;            /*定单来源*/
	TKSD_UVolumeType         OrderCancelQty;      /*撤单数量*/
	TKSD_ClientIDType		 ClientID;            /*客户代码*/
	TKSD_CByteType           TradeType;           /*交易类型*/
	TKSD_TimeType			 ActionTime;		  /*操作时间*/
	TKSD_CByteType			 MidFlag;			  /*是否中立仓*/
};
//交易员交割中立仓撤单请求
struct  CKSD_ReqTraderQuitDeliveryOrder
{
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地定单号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_TraderIDType		TraderNo;            /*委托席位号*/
	TKSD_TraderIDType		CancelTraderNo;      /*撤单席位号*/
	TKSD_CByteType           OrderType;          /*定单类型*/
	TKSD_CByteType           MidFlag;            /*是否中立仓*/
};
//交易员
struct  CKSD_ReqTrader
{
	TKSD_TraderIDType  TraderNo ;           /*交易员号*/  
	TKSD_MemberIDType  MemberID;            /*会员号*/
};
//交割中立仓成交应答
struct CKSD_RspTraderQryDeliveryMatch
{
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MatchNo			MatchNo;             /*成交号*/
	TKSD_TimeType			MatchTime;           /*成交时间*/
	TKSD_UVolumeType        Qty;                 /*成交数量*/
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号*/
	TKSD_TraderIDType		TraderNo;            /*席位号*/
	TKSD_CByteType          BsFlag;              /*买卖标志*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_CByteType          MidFlag;             /*是否中立仓*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
};

struct CKSD_RspQryTraderPurpose
{
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的编号*/
	TKSD_TradePurposeNameType  TradePurposeName; /*交易目的名称*/
	TKSD_CByteType           IsDefault;          /*是否默认*/
};

struct CKSD_RtnTraderInsertDeliveryOrders
{
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号int转为20位字符*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_TraderIDType		TraderNo;            /*委托席位号*/
	TKSD_MemberIDType		MemberID;            /*会员编号*/
	TKSD_ClientIDType		ClientID;            /*客户编号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_CByteType          BsFlag;              /*买卖标志*/
	TKSD_CByteType          EoFlag;              /*开平标志*/
	TKSD_CByteType          ShFlag;              /*投保标志*/
	TKSD_PriceType          Price;               /*价格*/
	TKSD_UVolumeType        Qty;                 /*数量*/
	TKSD_CByteType          OrderType;           /*定单类型*/
	TKSD_CByteType          OrderAttr;           /*定单属性*/
	TKSD_TimeType			OrderTime;           /*委托时间*/
	TKSD_UVolumeType        OrderBatchNo;        /*委托批次号*/
	TKSD_CByteType          TradeType;           /*交易类型*/
	TKSD_DateType			TradingDay;          /*交易日*/
	TKSD_StatusType			Status;              /*状态*/
	TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
	TKSD_UVolumeType        RemainAmt;           /*剩余数量(dimple)*/
	TKSD_CByteType          Type;                /*类型(dimple)*/
	TKSD_TradePurposeType	TradePurpose;        /*交易目的*/
	TKSD_CByteType          MidFlag;             /*是否中立仓*/
};
//查询交割中立仓委托应答结构：
struct CKSD_RspTraderQryDeliveryOrder
{
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号int转为20位字符*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_TraderIDType		TraderNo;            /*委托席位号*/
	TKSD_MemberIDType		MemberID;            /*会员编号*/
	TKSD_ClientIDType		ClientID;            /*客户编号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_CByteType          BsFlag;              /*买卖标志*/
	TKSD_CByteType          EoFlag;              /*开平标志*/
	TKSD_CByteType          ShFlag;              /*投保标志*/
	TKSD_PriceType          Price;               /*价格*/
	TKSD_UVolumeType        Qty;                 /*数量*/
	TKSD_CByteType          OrderType;           /*定单类型*/
	TKSD_CByteType          OrderAttr;           /*定单属性*/
	TKSD_TimeType			OrderTime;           /*委托时间*/
	TKSD_UVolumeType        OrderBatchNo;        /*委托批次号*/
	TKSD_CByteType          TradeType;           /*交易类型*/
	TKSD_DateType			TradingDay;          /*交易日*/
	TKSD_StatusType			Status;              /*状态*/
	TKSD_CByteType          Type;                /*类型(dimple)*/
	TKSD_TradePurposeType	TradePurpose;        /*交易目的*/
	TKSD_UVolumeType		MinQty;				 /*成交数量*/
	TKSD_CByteType          MidFlag;			 /*是否中立仓*/

};
//查询委托参数应答的结构：
struct CKSD_RspQryOrderPara
{
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_TraderIDType		TraderNo ;           /*交易员号*/
	TKSD_UVolumeType        MinHand;             /*最小下单量*/
	TKSD_UVolumeType        MaxHand;             /*最大下单量*/
	TKSD_PriceType          PriceDiff;           /*价差*/
	TKSD_DByteType			TraderControl;       /*控制到交易员*/
	
};
//查询系统参数应答的结构
struct CKSD_RspQrySystemPara
{
	TKSD_TraderIDType	TraderNo;            /*交易员号*/
	TKSD_DByteType		IfChk;               /*订单是否复核*/
	TKSD_DByteType		IfCreditCtl;         /*是否事前信用额度控制*/
	TKSD_DByteType		IfVaexpCtl;          /*是否事前敞口控制*/
	TKSD_DByteType		IfRuleCtl;           /*是否合规控制*/
	TKSD_DByteType		IfMarketCtl;         /*是否支持市价单*/
};
//递延补偿费率
struct CKSD_DeferFeeRateByFund
{
	TKSD_ContractIDType		 ContractId;          /*合约号*/
	TKSD_CByteType           PayFlag;             /*支付方向*/
	TKSD_PriceType           DeferFee;            /*递延费率*/
	TKSD_UVolumeType         DeliveryQty;         /*交货量*/
	TKSD_UVolumeType         ReceiveQty;          /*收货量*/
};
//交易员成交通知结构
struct CKSD_NtyTraderMatch
{
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_ExchCode				ExchCode;            /*交易所代码*/
	TKSD_MatchNo				MatchNo;             /*成交号*/
	TKSD_DateType				MatchDate;           /*成交日期*/
	TKSD_TimeType				MatchTime;           /*成交时间*/
	TKSD_PriceType				Price;               /*成交价格*/
	TKSD_UVolumeType			Qty;                 /*成交数量*/
	TKSD_SysOrderNo				SysOrderNo;          /*系统委托号*/
	TKSD_TraderIDType			TraderNo;            /*席位号*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_MemberIDType			MemberID;            /*会员号*/
	TKSD_ClientIDType			ClientID;            /*客户号*/
	TKSD_LocalOrderNo			LocalID;             /*报单本地编码*/
	TKSD_UVolumeType			OrderBatchNo;        /*委托批次号*/
	TKSD_CByteType				TradingRole;         /*交易角色*/
	TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
	TKSD_CByteType				MidFlag;             /*是否中立仓*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	TKSD_CByteType				MatchType;           /*类型(dimple)*/
};

/* 深度行情域 */
struct CKSD_RtyMBLQuot
{
	TKSD_ActArbiContractIDType	 ContractID;                    /*合约号*/
	TKSD_PriceType				 LastPrice;					    /*最新价*/
	TKSD_UVolumeType		 	 LastMatchQty;				    /*最新成交量*/
	TKSD_PriceType				 OpenPrice;						/*开盘价*/
	TKSD_PriceType               Bid1;                          /*买价1*/
	TKSD_UVolumeType               BidLot1;                       /*买量1*/
	TKSD_PriceType               Bid2;                          /*买价2*/
	TKSD_UVolumeType               BidLot2;                       /*买量2*/
	TKSD_PriceType               Bid3;                          /*买价3*/
	TKSD_UVolumeType               BidLot3;                       /*买量3*/
	TKSD_PriceType               Bid4;                          /*买价4*/
	TKSD_UVolumeType               BidLot4;                       /*买量4*/
	TKSD_PriceType               Bid5;                          /*买价5*/
	TKSD_UVolumeType               BidLot5;                       /*买量5*/
	TKSD_PriceType               Bid6;                          /*买价6*/
	TKSD_UVolumeType               BidLot6;                       /*买量6*/
	TKSD_PriceType               Bid7;                          /*买价7*/
	TKSD_UVolumeType               BidLot7;                       /*买量7*/
	TKSD_PriceType               Bid8;                          /*买价8*/
	TKSD_UVolumeType               BidLot8;                       /*买量8*/
	TKSD_PriceType               Bid9;                          /*买价9*/
	TKSD_UVolumeType               BidLot9;                       /*买量9*/
	TKSD_PriceType               Bid10;                          /*买价10*/
	TKSD_UVolumeType               BidLot10;                       /*买量10*/
	TKSD_PriceType               Ask1;                          /*卖价1*/
	TKSD_UVolumeType               AskLot1;                       /*卖量1*/
	TKSD_PriceType               Ask2;                          /*卖价2*/
	TKSD_UVolumeType               AskLot2;                       /*卖量2*/
	TKSD_PriceType               Ask3;                          /*卖价3*/
	TKSD_UVolumeType               AskLot3;                       /*卖量3*/
	TKSD_PriceType               Ask4;                          /*卖价4*/
	TKSD_UVolumeType               AskLot4;                       /*卖量4*/
	TKSD_PriceType               Ask5;                          /*卖价5*/
	TKSD_UVolumeType               AskLot5;                       /*卖量5*/
	TKSD_PriceType               Ask6;                          /*卖价6*/
	TKSD_UVolumeType               AskLot6;                       /*卖量6*/
	TKSD_PriceType               Ask7;                          /*卖价7*/
	TKSD_UVolumeType               AskLot7;                       /*卖量7*/
	TKSD_PriceType               Ask8;                          /*卖价8*/
	TKSD_UVolumeType               AskLot8;                       /*卖量8*/
	TKSD_PriceType               Ask9;                          /*卖价9*/
	TKSD_UVolumeType               AskLot9;                       /*卖量9*/
	TKSD_PriceType               Ask10;                          /*卖价10*/
	TKSD_UVolumeType               AskLot10;                       /*卖量10*/
};

/* 直接市场最优行情域 */
struct CKSD_RtyBestQuot
{
	TKSD_DateType		TradeDate;           /*交易日期*/
	TKSD_ActArbiContractIDType	ContractID;  /*合约号*/
	TKSD_UVolumeType	TID;                 /*事务编号*/
	TKSD_ContractNameType	ContractName;    /*合约名称*/
	TKSD_PriceType		LastPrice;           /*最新价*/
	TKSD_PriceType		HighPrice;           /*最高价*/
	TKSD_PriceType		LowPrice;            /*最低价*/
	TKSD_UVolumeType	LastMatchQty;        /*最新成交量 已废弃*/
	TKSD_UVolumeType	MatchTotQty;         /*成交量*/
	TKSD_PriceType		MatchWeight;         /*成交重量*/
	TKSD_PriceType		Turnover;            /*成交额*/
	TKSD_UVolumeType	InitOpenInterest;    /*初始持仓量*/
	TKSD_UVolumeType	OpenInterest;        /*持仓量*/
	TKSD_VolumeType		InterestChg;         /*持仓量变化*/
	TKSD_PriceType		ClearPrice;          /*今结算价*/
	TKSD_PriceType		LifeLow;             /*历史最低价*/
	TKSD_PriceType		LifeHigh;            /*历史最高价*/
	TKSD_PriceType		RiseLimit;           /*涨停板*/
	TKSD_PriceType		FallLimit;           /*跌停板*/
	TKSD_PriceType		LastClearPrice;      /*上日结算价*/
	TKSD_PriceType		LastClose;           /*上日收盘价*/
	TKSD_PriceType		BidPrice;            /*最高买*/
	TKSD_UVolumeType	BidQty;              /*申买量*/	
	TKSD_UVolumeType	BidImplyQty;         /*申买推导量*/
	TKSD_PriceType		AskPrice;            /*最低卖*/
	TKSD_UVolumeType	AskQty;              /*申卖量*/
	TKSD_UVolumeType	AskImplyQty;         /*申卖推导量*/
	TKSD_PriceType		AvgPrice;			 /*当日均价*/
	TKSD_TimeType		GenTime;             /*生成时间*/
	TKSD_PriceType		OpenPrice;           /*开盘价*/
	TKSD_PriceType		ClosePrice;          /*收盘价*/
	TKSD_UVolumeType	SeqNum;              /*行情序号*/
	TKSD_PriceType		PreDelta;            /*昨虚实度*/
	TKSD_PriceType		CurrDelta;           /*今虚实度*/    
};

//查询会员持仓结构：
struct  CKSD_ReqMemberQryPosi
{	
	TKSD_TraderIDType	TraderNo;  ///用户代码     
};
//查询会员持仓应答
struct  CKSD_RspMemberQryPosi
{
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_ClientIDType		ClientID ;           /*客户号*/
	TKSD_ContractIDType		ContractID ;         /*合约号*/
	TKSD_CByteType          BsFlag ;             /*买卖标志*/
	TKSD_CByteType          ShFlag ;             /*投保标志*/
	TKSD_UVolumeType        LastQty ;            /*上日持仓量*/
	TKSD_UVolumeType        Qty ;                /*持仓量*/
	TKSD_UVolumeType        OffsetQty ;          /*可平量 成交量*/
	TKSD_UVolumeType        OffsetLastQty ;      /*可平昨 未成交数量*/
	TKSD_UVolumeType        OffsetTodayQty ;     /*可平今 撤单数量*/
	TKSD_PriceType          Exposure ;           /*敞口*/
	TKSD_PriceType          Amt ;                /*持仓额*/
	TKSD_PriceType          AvePrice ;           /*持仓均价*/
	TKSD_PriceType          LastPrice ;          /*最新价*/
	TKSD_PriceType          FloatProfitLoss;     /*持仓盈亏*/   
};

//查询交易员交易编码关系请求
struct  CKSD_ReqClientMemberTrader
{	
	TKSD_TraderIDType	TraderNo;  ///用户代码     
};
//查询交易员交易编码关系应答
struct  CKSD_RspClientMemberTrader
{
	TKSD_TraderIDType		TraderNo ;           /*交易员号*/
	TKSD_ClientIDType		ClientID ;           /*客户号*/
	TKSD_MemberIDType		MemberID ;           /*会员号*/
	TKSD_ExchCode			ExchCode; 			 /*交易所代码*/
	TKSD_DByteType          IsDefault;          /*是否默认*/
	TKSD_AttrType			IfQuote;			/*是否金交所报价商席位*/
    
};
// ETF定单信息域
struct CKSD_ETFOrder
{
	TKSD_SysOrderNo		SysOrderNo;          /*系统委托号int转为20位字符*/
	TKSD_LocalOrderNo   LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_SysOrderNo		SelfLocalNo;         /*Fund编号*/
	TKSD_TraderIDType   TraderNo;            /*委托席位号*/
	TKSD_MemberIDType   MemberID;            /*会员编号*/
	TKSD_ClientIDType   ClientID;            /*投资人黄金账号*/
	TKSD_ETFCode		ETFCode;             /*基金代码*/
	TKSD_BondAccountNo  BondAccountNo;       /*投资人证券账号*/
	TKSD_DepositUnit	DepositUnit;         /*托管单元*/
	TKSD_AttrType   TradeType;				 /*交易类型*/
	TKSD_TradePurposeType   TradePurpose;    /*交易目的*/
	TKSD_UVolumeType          PercentQty;    /*份额*/
	TKSD_PriceType          TotalQty;        /*总重量*/
	TKSD_ContractIDType  ContractID1;        /*合约代码1*/
	TKSD_PriceType          Qty1;            /*重量1*/
	TKSD_ContractIDType  ContractID2;        /*合约代码2*/
	TKSD_PriceType          Qty2;            /*重量2*/
	TKSD_ContractIDType  ContractID3;        /*合约代码3*/
	TKSD_PriceType          Qty3;            /*重量3*/
	TKSD_ContractIDType  ContractID4;        /*合约代码4*/
	TKSD_PriceType          Qty4;            /*重量4*/
	TKSD_ContractIDType  ContractID5;        /*合约代码5*/
	TKSD_PriceType          Qty5;            /*重量5*/
	TKSD_DateType   TradeDate;				 /*交易日期*/
	TKSD_TimeType  TradeTime;                /*交易时间*/
	TKSD_AttrType   Status;					 /*状态*/
	TKSD_DateType   ConfirmDate;			 /*确认日期*/
	TKSD_Status   SystemStatus;				 /*系统状态*/
};

//ETF申赎清单请求域 
struct CKSD_ReqETFList
{
	TKSD_ETFCode   ETFCode;             /*ETF基金代码*/
};

//ETF申赎清单域
struct CKSD_RspETFList
{
	TKSD_ETFCode   ETFCode;							/*ETF基金代码*/
	TKSD_DateType   TradeDate;						/*交易日期*/
	TKSD_MemberIDType   MemberID;					/*会员号*/
	TKSD_ContractIDType  ContractId1;				/*合约代码1*/
	TKSD_PriceType          CalcAmt1;				/*T日预估现金差额1*/
	TKSD_PriceType          Amt1;					/*T-1日现金差额1*/
	TKSD_ContractIDType  ContractId2;				/*合约代码2*/
	TKSD_PriceType          CalcAmt2;				/*T日预估现金差额2*/
	TKSD_PriceType          Amt2;					/*T-1日现金差额2*/
	TKSD_ContractIDType  ContractId3;				/*合约代码3*/
	TKSD_PriceType          CalcAmt3;				/*T日预估现金差额3*/
	TKSD_PriceType          Amt3;					/*T-1日现金差额3*/
	TKSD_ContractIDType  ContractId4;				/*合约代码4*/
	TKSD_PriceType          CalcAmt4;				/*T日预估现金差额4*/
	TKSD_PriceType          Amt4;					/*T-1日现金差额4*/
	TKSD_ContractIDType  ContractId5;				/*合约代码5*/
	TKSD_PriceType          CalcAmt5;				/*T日预估现金差额5*/
	TKSD_PriceType          Amt5;					/*T-1日现金差额5*/
	TKSD_UVolumeType          MinQty;			    /*最小申购赎回重量*/
	TKSD_UVolumeType          MaxApplyQty;		    /*当日申购上限*/
	TKSD_UVolumeType          MaxRansomQty;		    /*当日赎回上限*/
	TKSD_CByteType           IfAr;					/*当日是否允许申购/赎回标志*/
	TKSD_PriceType          ETFUnit;				/*每份黄金ETF基金对应的黄金重量*/
};

//业务参数请求数据域
struct CKSD_ReqPara
{
	TKSD_VarietyEName  Code;                /*系统参数代码*/
};

//业务参数应答数据域
struct CKSD_RspPara
{
	TKSD_VarietyEName  Code;                /*系统参数代码*/
	TKSD_NameType  ParaName;            /*中文名称*/
	TKSD_NameType  EName;               /*英文名称*/
	TKSD_PriceType ParaValue;           /*参数值*/
	TKSD_VarietyEName  ParaString;          /*参数字符串*/
	TKSD_NoteType Note;                /*备注*/
};


//递延交收行情域
struct CKSD_DeferOrder
{
	TKSD_ContractIDType		  ContractID;          /*合约代码(dimple)*/
	TKSD_UVolumeType          BuyAmt;              /*买量(dimple)*/
	TKSD_UVolumeType          SellAmt;             /*卖量(dimple)*/
	TKSD_UVolumeType          MiddleBuyAmt;        /*中立仓买量(dimple)*/
	TKSD_UVolumeType          MiddleSellAmt;       /*中立仓卖量(dimple)*/
};

//保证金查询域
struct CKSD_TradeMarginRateQry
{
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_CByteType          ShFlag;              /*投保标志*/
	TKSD_PriceType          LastClearPrice;      /*昨结算价*/
	TKSD_CByteType          MarginType;          /*保证金类型*/
	TKSD_PriceType          BuyRate;             /*买率*/
	TKSD_PriceType          SellRate;            /*卖率*/
	TKSD_PriceType          BuyFix;              /*买固定值*/
	TKSD_PriceType          SellFix;             /*卖固定值*/
	TKSD_PriceType          LastBuyRate;         /*昨买率*/
	TKSD_PriceType          LastSellRate;        /*昨卖率*/
	TKSD_PriceType          LastBuyFix;          /*昨买固定值*/
	TKSD_PriceType          LastSellFix;         /*昨卖固定值*/
};

// 交易手续费查询域
struct CKSD_TradeFtrFee
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_VarietyIDType		VarietyID;           /*品种代码*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_AttrType			Attr;                /*交易编码属性*/
	TKSD_AttrType			AppType;             /*定价成交申报类型*/
	TKSD_DByteType			FeeType;             /*费用类型*/
	TKSD_PriceType          OpenFee;             /*开仓结算手续费*/
	TKSD_PriceType          OffsetFee;           /*平仓结算手续费*/
	TKSD_PriceType          TOpenFee;            /*开仓交易手续费*/
	TKSD_PriceType          TOffsetFee;          /*平仓交易手续费*/
	TKSD_PriceType          ShortOpenFee;        /*短线开仓手续费*/
	TKSD_PriceType          ShortOffsetFee;      /*短线平仓手续费*/
};

// 交割手续费查询域
struct CKSD_TradeDeliveryFee
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_VarietyIDType		VarietyID;           /*品种代码*/
	TKSD_DByteType			FeeType;             /*费用类型*/
	TKSD_PriceType          DeliveryFee;         /*交割手续费*/
};

// 报价商报单请求域
struct CKSD_MakerQuote
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_VolumeType			ContractNo;			 /*合约编号*/		
	TKSD_MarketNoType		MarketNo;			 /*市场编号*/
	TKSD_UVolumeType		QuoteBatchNo;        /*报价委托组号*/
	TKSD_LocalOrderNo		LocalOrderNo;		 /*本地报单编号*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
	TKSD_UVolumeType        Qty;                 /*数量*/
	TKSD_PriceType          Price;               /*价格*/
	TKSD_CByteType          OrderType;           /*指令类型*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_ByteType			OrderSrc;			 /*定单来源*/
};

// 报价商报单回报域
struct CKSD_RtnMakerQuote
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_VolumeType			ContractNo;			 /*合约编号*/
	TKSD_MarketNoType		MarketNo;			 /*市场编号*/
	TKSD_UVolumeType		QuoteBatchNo;        /*报价委托组号*/
	TKSD_LocalOrderNo		LocalOrderNo;		 /*本地报单编号*/
	TKSD_SysOrderNo			QuoteOrderNo;        /*系统报单编号*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
	TKSD_UVolumeType        Qty;                 /*数量*/
	TKSD_UVolumeType        RemainQty;           /*剩余数量*/
	TKSD_PriceType          Price;               /*价格*/
	TKSD_CByteType          OrderType;           /*指令类型*/
	TKSD_DateType			OrderDate;           /*申请日期*/
	TKSD_TimeType			OrderTime;           /*申请时间*/
	TKSD_StatusType			Status;              /*定单状态*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_ByteType			OrderSrc;			 /*定单来源*/
};

// 报价商撤单请求域
struct CKSD_MakerCancelQuote
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_MarketNoType		MarketNo;			 /*市场编号*/
	TKSD_LocalOrderNo		QuoteLocalOrderNo;	 /*本地报单编号*/
	TKSD_SysOrderNo			QuoteOrderNo;		 /*系统报单编号*/
};
// 报价商撤单回报域
struct CKSD_RtnMakerCancelQuote
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_MarketNoType		MarketNo;			 /*市场编号*/
	TKSD_LocalOrderNo		QuoteLocalOrderNo;   /*本地报单编号*/
	TKSD_SysOrderNo			QuoteOrderNo;        /*系统报单编号*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
	TKSD_UVolumeType        Qty;                 /*数量*/
	TKSD_UVolumeType        RemainQty;           /*剩余数量*/
	TKSD_PriceType          Price;               /*价格*/
	TKSD_CByteType          OrderType;           /*指令类型*/
	TKSD_DateType			OrderDate;           /*申请日期*/
	TKSD_TimeType			OrderTime;           /*申请时间*/
	TKSD_TimeType			CancleTime;          /*撤销时间*/
	TKSD_TraderIDType		CancelTraderNo;      /*撤销交易员号*/
	TKSD_StatusType			Status;              /*定单状态*/
};

// 报价成交通知
struct CKSD_NtyQuoteMatch
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_VolumeType			ContractNo;			 /*合约编号*/
	TKSD_MarketNoType		MarketNo;			 /*市场编号*/
	TKSD_LocalOrderNo		QuoteLocalOrderNo;   /*本地报单编号*/
	TKSD_SysOrderNo			QuoteOrderNo;        /*系统报单编号*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
	TKSD_UVolumeType        Qty;                 /*成交数量*/
	TKSD_WeightType			Weight;				 /*成交重量*/
	TKSD_PriceType          Price;               /*成交价格*/
	TKSD_DateType			MatchDate;           /*成交日期*/
	TKSD_TimeType			MatchTime;           /*成交时间*/
	TKSD_MatchNo			MatchNo;			 /*成交编号*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_ByteType           OrderSrc;            /*定单来源*/
	TKSD_UVolumeType        RemainQty;           /*剩余数量*/
	TKSD_ClientIDType        LongPosi;            /*客户多头持仓*/
	TKSD_ClientIDType        ShortPosi;           /*客户空头持仓*/
};

// 报价商报价行情通知
struct CKSD_NtyQuoteQuot
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MarketNoType		MarketNo;			 /*市场编号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_VolumeType			ContractNo;			 /*合约编号*/
	TKSD_PriceType          AskPrice;            /*卖价*/
	TKSD_UVolumeType        AskQty;              /*卖量*/
	TKSD_PriceType          BidPrice;            /*买价*/
	TKSD_UVolumeType        BidQty;              /*买量*/
	TKSD_DateType			TradeDate;           /*行情日期*/
	TKSD_TimeType			GenTime;			 /*行情时间*/
	TKSD_DateType			NaturalDate;		 /*自然日期*/
	TKSD_UVolumeType		SeqNum;				 /*行情序号*/
};

// 报价市场成交行情通知
struct CKSD_NtyQuoteMatchQuot
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MarketNoType		MarketNo;			 /*市场编号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_VolumeType			ContractNo;			 /*合约编号*/
	TKSD_PriceType			OpenPrice;           /*开盘价*/
	TKSD_PriceType			HighPrice;           /*最高价*/
	TKSD_PriceType			LowPrice;            /*最低价*/
	TKSD_PriceType			LastPrice;           /*最新价*/
	TKSD_UVolumeType		MatchTotQty;         /*成交量*/
	TKSD_PriceType			MatchWeight;         /*成交重量*/
	TKSD_UVolumeType		OpenInterest;        /*持仓量*/
	TKSD_PriceType			Updown;				 /*涨跌*/
	TKSD_PriceType			UpdownRate;          /*涨跌幅度*/
	TKSD_PriceType			Turnover;            /*成交额*/
	TKSD_PriceType			AvgPrice;			 /*均价*/
	TKSD_DateType			TradeDate;           /*行情日期*/
	TKSD_TimeType			GenTime;			 /*行情时间*/
	TKSD_DateType			NaturalDate;		 /*自然日期*/
	TKSD_UVolumeType		SeqNum;              /*行情序号*/
};


// 报价市场日终(初始)行情通知
struct CKSD_NtyQuoteClearQuot
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_MarketNoType		MarketNo;			 /*市场编号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_VolumeType			ContractNo;			 /*合约编号*/
	TKSD_PriceType			LastClearPrice;      /*上日结算价*/
	TKSD_PriceType			LastClose;           /*上日收盘价*/
	TKSD_PriceType			OpenPrice;           /*开盘价*/
	TKSD_PriceType			HighPrice;           /*最高价*/
	TKSD_PriceType			LowPrice;            /*最低价*/
	TKSD_PriceType			LastPrice;           /*最新价*/
	TKSD_PriceType			ClosePrice;          /*收盘价*/
	TKSD_PriceType			ClearPrice;          /*结算价*/
	TKSD_UVolumeType		MatchTotQty;         /*成交量*/
	TKSD_PriceType			MatchWeight;         /*成交重量*/
	TKSD_UVolumeType		OpenInterest;        /*持仓量*/
	TKSD_PriceType			RiseLimit;           /*涨停板*/
	TKSD_PriceType			FallLimit;           /*跌停板*/	
	TKSD_PriceType			Updown;				 /*涨跌*/
	TKSD_PriceType			UpdownRate;          /*涨跌幅度*/
	TKSD_PriceType			Turnover;            /*成交额*/
	TKSD_PriceType			AvgPrice;			 /*均价*/
	TKSD_DateType			TradeDate;           /*行情日期*/
	TKSD_TimeType			GenTime;			 /*行情时间*/
	TKSD_DateType			NaturalDate;		 /*自然日期*/
};

// 单腿策略定单请求域 
struct CKSD_ReqInsertPreOrder
{
	TKSD_ExchCode				ExchCode;            /*交易所代码*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_CByteType				RefPriceType;        /*参考价类型*/
	TKSD_PriceType				StopPrice;           /*止损(盈)价*/
	TKSD_CByteType				Trigger;             /*触发条件*/
	TKSD_PriceType				TrailingStop;        /*移动止损值*/
	TKSD_CByteType				TrigMethod;          /*触发方式*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	TKSD_CByteType				IfRetain;            /*是否结算后保留*/
};

// 单腿策略定单应答域 
struct CKSD_RspPreOrder
{
	TKSD_LocalOrderNo			LocalPreOrderNo;	 /*预备单号*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_ExchCode				ExchCode;            /*交易所代码*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_CByteType				RefPriceType;        /*参考价类型*/
	TKSD_PriceType				StopPrice;           /*止损(盈)价*/
	TKSD_CByteType				Trigger;             /*触发条件*/
	TKSD_PriceType				TrailingStop;        /*移动止损值*/
	TKSD_CByteType				TrigMethod;          /*触发方式*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_UVolumeType            RemainQty;           /*剩余数量*/
	TKSD_DateType				TradingDay;          /*交易日*/
	TKSD_Status					Status;              /*定单状态*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	TKSD_CByteType				IfRetain;            /*是否结算后保留*/
};
//取消策略定单请求域
struct CKSD_ReqCancelPreOrder
{
	TKSD_LocalOrderNo			LocalPreOrderNo;	 /*预备单号*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_DateType				TradingDay;          /*交易日*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
};
//取消策略定单应答域
struct CKSD_RspCancelPreOrder
{
	TKSD_LocalOrderNo			LocalPreOrderNo;	 /*预备单号*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_DateType				TradingDay;          /*交易日*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_Status					Status;              /*定单状态*/
	TKSD_DateType				CancelDate;          /*撤消日期*/
	TKSD_TimeType				CancelTime;          /*撤消时间*/
};
// 修改单腿策略定单请求域 
struct CKSD_ReqUpdPreOrder
{
	TKSD_LocalOrderNo			LocalPreOrderNo;	 /*预备单号*/
	TKSD_DateType				TradingDay;          /*交易日*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_CByteType				RefPriceType;        /*参考价类型*/
	TKSD_PriceType				StopPrice;           /*止损(盈)价*/
	TKSD_CByteType				Trigger;             /*触发条件*/
	TKSD_PriceType				TrailingStop;        /*移动止损值*/
	TKSD_CByteType				TrigMethod;          /*触发方式*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	TKSD_CByteType				IfRetain;            /*是否结算后保留*/
};

//查询策略定单请求域
struct CKSD_ReqQryPreOrder
{
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_DateType				TradingDay;          /*交易日*/
};

//查询策略定单应答域
struct CKSD_RspQryPreOrder
{
	TKSD_LocalOrderNo			LocalOrderNo;		 /*本地委托号(dimple)*/
	TKSD_SysOrderNo				SysOrderNo;			 /*系统委托号*/
	TKSD_LocalOrderNo			LocalPreOrderNo;	 /*预备单号*/
	TKSD_UVolumeType            OrderBatchNo;        /*委托批次号*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_ActArbiContractIDType	ArbiContractID;		 /*套利合约号*/
	TKSD_ExchCode				ExchCode;            /*交易所代码*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_CByteType				RefPriceType;        /*参考价类型*/
	TKSD_PriceType				RefPrice;            /*参考价*/
	TKSD_PriceType				StopPrice;           /*止损(盈)价*/
	TKSD_CByteType				Trigger;             /*触发条件*/
	TKSD_PriceType				TrailingStop;        /*移动止损值*/
	TKSD_CByteType				TrigMethod;          /*触发方式*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_UVolumeType            RemainQty;           /*剩余数量*/
	TKSD_DateType				TradingDay;          /*交易日*/
	TKSD_Status					Status;              /*定单状态*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	TKSD_DateType				ExecDate;			 /*触发日期*/
	TKSD_TimeType				ExecTime;			 /*触发时间*/
	TKSD_DateType				CancelDate;          /*撤消日期*/
	TKSD_TimeType				CancelTime;          /*撤消时间*/
	TKSD_TraderIDType			CancelTraderNo;      /*撤消员代码*/
	TKSD_CByteType				IfRetain;            /*是否结算后保留*/
	TKSD_CByteType				DblOrderType;        /*两腿策略类型*/
};

//两腿策略定单请求域
struct CKSD_ReqDoublePreOrder
{
	TKSD_LocalOrderNo			LocalOrderNo;		 /*本地委托号(dimple)*/
	TKSD_SysOrderNo				SysOrderNo;			 /*系统委托号*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_ActArbiContractIDType	ArbiContractID;		 /*套利合约号*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_CByteType				TrigMethod;          /*触发方式*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	TKSD_CByteType				IfRetain;            /*是否结算后保留*/
	TKSD_CByteType				DblOrderType;        /*两腿策略类型*/
};
typedef vector<CKSD_ReqDoublePreOrder> CKSD_ReqDoublePreOrderVec;
// 两腿策略定单应答域 
struct CKSD_RspDoublePreOrder
{
	TKSD_LocalOrderNo			LocalPreOrderNo;	 /*预备单号*/
	TKSD_LocalOrderNo			LocalOrderNo;		 /*本地委托号(dimple)*/
	TKSD_SysOrderNo				SysOrderNo;			 /*系统委托号*/
	TKSD_UVolumeType            OrderBatchNo;        /*委托批次号*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_ActArbiContractIDType	ArbiContractID;		 /*套利合约号*/
	TKSD_ExchCode				ExchCode;            /*交易所代码*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_UVolumeType            RemainQty;           /*剩余数量*/
	TKSD_DateType				TradingDay;          /*交易日*/
	TKSD_Status					Status;              /*定单状态*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	TKSD_CByteType				IfRetain;            /*是否结算后保留*/
	TKSD_CByteType				DblOrderType;        /*两腿策略类型*/
};
typedef vector<CKSD_RspDoublePreOrder> CKSD_RspDoublePreOrderVec;
//手动触发策略单请求域
struct CKSD_ReqTrigPreOrder
{
	TKSD_LocalOrderNo			LocalPreOrderNo;	 /*预备单号*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_DateType				TradingDay;          /*交易日*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
};
//手动触发策略单应答域
struct CKSD_RspTrigPreOrder
{
	TKSD_LocalOrderNo			LocalPreOrderNo;	 /*预备单号*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_DateType				TradingDay;          /*交易日*/
	TKSD_Status					Status;              /*定单状态*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_DateType				ExecDate;			 /*触发日期*/
	TKSD_TimeType				ExecTime;			 /*触发时间*/
};
//报价平盘请求域
struct CKSD_ReqOffsetOrder
{
	TKSD_ByteType				OpType;				 /*操作类型*/
	TKSD_MemberIDType			MemberID;			 /*会员号*/
	TKSD_ClientIDType			ClientID;			 /*客户号*/
	TKSD_TraderIDType			TraderNo;			 /*交易员号*/
	TKSD_ContractIDType			PairsCurrency;		 /*货币对*/
	TKSD_OffsetIDType			OffsetID;			 /*平盘方*/
	TKSD_ByteType				OffsetType;			 /*平盘类型*/
	TKSD_ByteType				OffsetMode;			 /*平盘模式*/
	TKSD_ByteType				OffsetStrategy;		 /*平盘策略*/
	TKSD_ByteType				BsFlag;				 /*平盘方向*/
	TKSD_MoneyType				Qty1;				 /*平盘重量(克):美元平盘不填*/
	TKSD_MoneyType				TranAmt;			 /*平盘重量(盎司)或平盘金额*/
	TKSD_DateType				TradeDate;			 /*交易日期*/
};
//报价平盘应答域
struct CKSD_RspOffsetOrder
{
	TKSD_ByteType				OpType;				 /*操作类型*/
	TKSD_MemberIDType			MemberID;			 /*会员号*/
	TKSD_ClientIDType			ClientID;			 /*客户号*/
	TKSD_TraderIDType			TraderNo;			 /*交易员号*/
	TKSD_ContractIDType			PairsCurrency;		 /*货币对*/
	TKSD_OffsetIDType			OffsetID;			 /*平盘方*/
	TKSD_ByteType				OffsetType;			 /*平盘类型*/
	TKSD_ByteType				OffsetMode;			 /*平盘模式*/
	TKSD_ByteType				OffsetStrategy;		 /*平盘策略*/
	TKSD_ByteType				BsFlag;				 /*平盘方向*/
	TKSD_MoneyType				Qty1;				 /*平盘重量(克):美元平盘不填*/
	TKSD_MoneyType				TranAmt;			 /*平盘重量(盎司)或平盘金额*/
	TKSD_DateType				TradeDate;			 /*交易日期*/
	TKSD_TimeType				TradeTime;			 /*交易时间*/
	TKSD_Currency				TranCcy;			 /*交易货币*/
	TKSD_Currency				FisrtCcy;			 /*第一货币*/
	TKSD_Currency				CrdCcy;				 /*第二货币*/
	TKSD_SysOrderNo				LocalNo;			 /*本地流水号*/
	TKSD_SysOrderNo				OrderNo;			 /*系统报单号*/
	TKSD_ByteType				TradeStatus;		 /*交易状态*/
	TKSD_ExgRtQtnNoType			ExgRtQtnNo;			 /*牌价号*/
	TKSD_Currency				BaseFeeCcy;			 /*基准货币币种*/
	TKSD_MoneyType				BrgnExgRt;			 /*成交汇率*/
	TKSD_MoneyType				MatchAmt;			 /*成交金额:重量或美元*/
	TKSD_MoneyType				Amt1;				 /*金额1*/
	TKSD_MoneyType				Amt2;				 /*金额2*/
	TKSD_DateType				DeliveryDate;		 /*交割日期*/
	TKSD_ErrorMsgType			Remark;              /*备注*/
};
//报价贵金属实时头寸查询域
struct CKSD_ReqQuotePosiQry
{
	TKSD_MemberIDType			MemberID;			 /*会员号*/
	TKSD_TraderIDType			TraderNo;			 /*交易员号*/
	TKSD_ContractIDType			ContractID;			 /*货币对*/
};
//报价贵金属头寸查询应答域
struct CKSD_RspQuoteMetalPosi
{
	TKSD_MemberIDType			MemberID;			 /*会员号*/
	TKSD_ContractIDType			PairsCurrency;		 /*货币对*/
	TKSD_ContractIDType			ContractID;			 /*合约*/
	TKSD_UVolumeType			BuyPosi;             /*买持仓量(手)*/
	TKSD_UVolumeType			SellPosi;            /*卖持仓量(手)*/
	TKSD_VolumeType				NetPosi;             /*轧差头寸(手)*/
	TKSD_WeightType				BuyQty;				 /*买持仓重量(克)*/
	TKSD_WeightType				SellQty;             /*卖持仓重量(克)*/
	TKSD_WeightType				NetQty;              /*轧差头寸(克)*/
	TKSD_WeightType				OffsetBuyQty;        /*买平盘重量(克)*/
	TKSD_WeightType				OffsetSellQty;       /*卖平盘重量(克)*/
	TKSD_WeightType				NetOffsetQty;        /*平盘轧差头寸(克)*/
	TKSD_WeightType				NOffsetQty;          /*待平盘重量(克)*/
};
//报价美元头寸查询应答域
struct CKSD_RspQuoteUSDPosi
{
	TKSD_Currency				Currency;			 /*币种*/
	TKSD_MoneyType				MetalOffsetMoneyOut;   /*贵金属平盘买入支出金额(美元)*/
	TKSD_MoneyType				MetalOffsetMoneyIn;  /*贵金属平盘卖出收到金额(美元)*/
	TKSD_MoneyType				MetalNetOffsetAmt;   /*贵金属平盘轧差金额(美元)*/
	TKSD_MoneyType				USDOffsetBuyAmt;     /*美元平盘买入收到金额(美元)*/
	TKSD_MoneyType				USDOffsetSellAmt;    /*美元平盘卖出支出金额(美元)*/
	TKSD_MoneyType				USDNetOffsetAmt;     /*美元平盘轧差金额(美元)*/
	TKSD_MoneyType				USDNOffsetAmt;       /*美元待平盘金额(美元)*/
};
//报价市场信息域
struct CKSD_QuoteMarketInfo
{
	TKSD_MarketNoType			MarketID;            /*市场代码*/
	TKSD_Status					marketTradeState;    /*市场交易状态*/
};
//报价合约状态信息域
struct CKSD_QuoteContractInfo
{
	TKSD_ContractIDType			ContractID;          /*合约代码*/
	TKSD_ByteType				InstState;           /*合约交易状态*/
	TKSD_ByteType				InstOpenFlag;		 /*合约活跃标志*/
};

//报价行情查询请求域
struct CKSD_QuoteQuotQry
{
	TKSD_MemberIDType   MemberID;            /*会员号*/
	TKSD_ExchCode		ExchCode;            /*交易所代码*/
	TKSD_TraderIDType	TraderNo;            /*席位号*/
	TKSD_MarketNoType   MarketNo;            /*市场编号*/
	TKSD_ContractNoType ContractNO;          /*合约编号*/
	TKSD_ContractIDType ContractId;          /*合约代码*/
};
//报价行情应答域
struct CKSD_QuoteQuotRsp
{
	TKSD_ExchCode		ExchCode;            /*交易所代码*/
	TKSD_MemberIDType   MemberID;            /*会员号*/
	TKSD_ClientIDType	ClientID;            /*客户号*/
	TKSD_TraderIDType	TraderNo;            /*交易员号*/
	TKSD_MarketNoType   MarketNo;            /*市场编号*/
	TKSD_ContractNoType ContractNo;          /*合约编号*/
	TKSD_ContractIDType ContractID;          /*合约代码*/
	TKSD_PriceType      AskPrice;            /*卖价*/
	TKSD_UVolumeType    AskQty;              /*卖量*/
	TKSD_PriceType      BidPrice;            /*买价*/
	TKSD_UVolumeType    BidQty;              /*买量*/
	TKSD_DateType		TradeDate;           /*行情日期*/
	TKSD_TimeType		GenTime;             /*行情时间*/
	TKSD_DateType		NaturalDate;         /*自然日期*/
	TKSD_SeqNoType		SeqNo;               /*流水号*/
};

//报价合约信息查询域
struct CKSD_QuoteContractInfoReq
{
	TKSD_ContractIDType   ContractID;          /*合约代码*/
};
//报价商报价委托查询请求
struct  CKSD_ReqQuoteOrderQry
{
	TKSD_TraderIDType		TraderNo;            /*交易员*/
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ContractIDType		ContractId;          /*合约号*/
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号*/
};

//报价商报价委托查询应答域
struct  CKSD_RspQuoteOrderQry
{
	TKSD_TraderIDType		TraderNo;            /*交易员*/
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ClientIDType		ClientID;			 /*客户号*/
	TKSD_ContractIDType		ContractId;          /*合约号*/
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号*/ 
	TKSD_ByteType			OrderStatus;		 /*定单状态*/
	TKSD_LocalOrderNo		LocalOrderNo;		 /*本地委托号*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_ByteType			BsFlag;              /*买卖标志*/
	TKSD_PriceType			Price;               /*价格*/	
	TKSD_TimeType			OrderTime;           /*委托时间*/
	TKSD_UVolumeType        MatchQty;            /*成交量*/
	TKSD_TimeType			CancelTime;          /*撤单时间*/
	TKSD_TraderIDType		CancelTraderNo;      /*撤单席位号*/
	TKSD_UVolumeType		OrderBatchNo;        /*委托批次号*/
	TKSD_UVolumeType        QtyTotOrginal;       /*原始总申报数量（以手为单位）*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_ByteType			OrderSrc;            /*定单来源*/
	TKSD_PriceType          LastMatchPrice;      /*最新成交价格*/
};
//设置应急模式域 
struct CKSD_QuoteSetEmergencyMode
{
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_ByteType           Mode;                /*模式:0一般模式;1应急模式*/
};

///用户密文登录请求
struct CKSD_ReqEncTradeLoginField
{
	///
	TKSD_TraderIDType		TraderNo; /*用户代码*/
	///
	TKSD_EncPasswordType	Pwd; /*SHA256密文密码*/
};

//期权询价请求域
struct CKSD_ReqOptInquireOrder
{
	TKSD_ExchCode		ExchCode;            /*交易所代码*/
	TKSD_MemberIDType   MemberID;            /*会员号*/
	TKSD_ClientIDType   ClientID;            /*客户号*/
	TKSD_TraderIDType   TraderNo;            /*交易员号*/
	TKSD_ContractIDType ContractID;          /*合约代码*/
	TKSD_SysOrderNo		DemandLocalID;       /*本地询价编号*/
};

//期权询价应答域
struct CKSD_RspOptInquireOrder
{
	TKSD_ExchCode		ExchCode;            /*交易所代码*/
	TKSD_MemberIDType   MemberID;            /*会员号*/
	TKSD_ClientIDType   ClientID;            /*客户号*/
	TKSD_TraderIDType   TraderNo;            /*交易员号*/
	TKSD_ContractIDType ContractID;          /*合约代码*/
	TKSD_SysOrderNo		DemandLocalID;       /*本地询价编号*/
	TKSD_SysOrderNo		DemandID;            /*询价编号*/
	TKSD_DateType		DemandDay;           /*询价日期*/
	TKSD_TimeType		DemandTime;          /*询价时间*/
	TKSD_ByteType       Status;              /*状态*/
};

//期权询价通知域
struct CKSD_RtnOptInquireOrder
{
	TKSD_ExchCode		ExchCode;            /*交易所代码*/
	TKSD_MemberIDType   MemberID;            /*会员号*/
	TKSD_ClientIDType   ClientID;            /*客户号*/
	TKSD_TraderIDType   TraderNo;            /*交易员号*/
	TKSD_ContractIDType ContractID;          /*合约代码*/
	TKSD_SysOrderNo		DemandLocalID;       /*本地询价编号*/
	TKSD_SysOrderNo		DemandID;            /*询价编号*/
	TKSD_DateType		DemandDay;           /*询价日期*/
	TKSD_TimeType		DemandTime;          /*询价时间*/
	TKSD_ByteType         Status;              /*状态*/
};

//做市商期权报单请求域
struct CKSD_ReqOptQuetoOrder
{
	TKSD_LocalOrderNo			LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_ExchCode				ExchCode;            /*交易所代码*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType			    EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_PriceType				StopPrice;           /*止损(盈)价*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_CByteType				OrderSort;           /*定单类别*/	
	TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/ 
	TKSD_SysOrderNo             QuoteDemandID;       /*询价编号*/
};
typedef vector<CKSD_ReqOptQuetoOrder> CKSD_ReqOptQuetoOrderVec;

//做市商期权报单应答域
struct CKSD_RspOptQuetoOrder
{
	TKSD_SysOrderNo			SysOrderNo;          /*系统委托号*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地委托号*/
	TKSD_TraderIDType		TraderNo;            /*委托席位号*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_CByteType          BsFlag;              /*买卖标志*/
	TKSD_CByteType          EoFlag;              /*开平标志*/
	TKSD_CByteType          ShFlag;              /*投保标志*/
	TKSD_PriceType          Price;               /*价格*/
	TKSD_UVolumeType        Qty;                 /*数量*/
	TKSD_CByteType          OrderType;           /*定单类型*/
	TKSD_CByteType          OrderAttr;           /*定单属性*/
	TKSD_TimeType			OrderTime;           /*委托时间*/
	TKSD_UVolumeType        OrderBatchNo;        /*委托批次号*/
	TKSD_CByteType          TradeType;           /*交易类型*/
	TKSD_DateType			TradingDay;          /*交易日*/
	TKSD_StatusType			Status;              /*状态*/
	TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
	TKSD_UVolumeType		 RemainAmt;           /*剩余数量(dimple)*/
	TKSD_CByteType           Type;                /*类型(dimple)*/
	TKSD_TradePurposeType	 TradePurpose;        /*交易目的*/
	TKSD_SysOrderNo          QuoteDemandID;       /*询价编号*/
	TKSD_SysOrderNo          SysQuoteNo;          /*系统报价编号*/
	TKSD_CByteType           IfOptMktMk;          /*是否期权做市商下单*/
};

//做市商期权撤单请求域
struct CKSD_ReqOptQuetoOrderCancel
{
	TKSD_ExchCode			ExchCode;       /*交易所代码*/
    TKSD_TraderIDType 		TraderNo;			/*交易员*/
	TKSD_MemberIDType 		MemberID;			/*会员号*/
	TKSD_ContractIDType 	ContractID;			/*合约号*/
	TKSD_TraderIDType 		CancelTraderNo;		/*席位号*/
	TKSD_LocalOrderNo 		LocalOrderNo;		/*本地定单号*/
	TKSD_SysOrderNo 		SysOrderNo;			/*系统定单号*/
    TKSD_SysOrderNo         SysQuoteNo;          /*系统报价编号*/
};

//做市商期权撤单应答域
struct CKSD_RspOptQuetoOrderCancel
{
	TKSD_TraderIDType 		TraderNo;		/*交易员*/
	TKSD_MemberIDType 		MemberID;		/*会员号*/
	TKSD_ClientIDType		ClientID ;      /*客户号*/
	TKSD_UVolumeType 		OrderBatchNo;	/*委托批次号*/
	TKSD_ContractIDType 	ContractID;		/*合约号*/
	TKSD_TraderIDType 		CancelTraderNo;	/*席位号*/
	TKSD_LocalOrderNo 		LocalOrderNo;   /*本地定单号*/
	TKSD_SysOrderNo 		SysOrderNo;		/*系统定单号*/
	TKSD_ExchCode			ExchCode;       /*交易所代码*/
	TKSD_TimeType			ActionTime;     /*操作时间*/
	TKSD_UVolumeType 		OrderCancelQty; /*撤单数量*/
    TKSD_SysOrderNo         SysQuoteNo;          /*系统报价编号*/
};


//期权行权请求域
struct CKSD_ReqOptExecField
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_TraderIDType		TraderNo;			 /*交易员*/	
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ClientIDType		ClientID;			 /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_SysOrderNo			ExecLocalNo;		 /*本地执行编号*/
	TKSD_CByteType			BsFlag;              /*买卖标志*/
	TKSD_CByteType			EoFlag;              /*开平标志*/
	TKSD_CByteType			ShFlag;              /*投保标志*/
	TKSD_UVolumeType		Qty;                 /*数量*/
	TKSD_CByteType			ExecType;			 /*行权类型*/
	TKSD_CByteType			IsSelfClose;		 /*是否执行后期货自对冲*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
};

//期权行权信息域
struct CKSD_OptExecField
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_TraderIDType		TraderNo;			 /*交易员*/	
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ClientIDType		ClientID;			 /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_SysOrderNo			ExecLocalNo;		 /*本地执行编号*/
	TKSD_SysOrderNo			ExecSysNo;			 /*系统执行编号*/
	TKSD_CByteType			BsFlag;              /*买卖标志*/
	TKSD_CByteType			EoFlag;              /*开平标志*/
	TKSD_CByteType			ShFlag;              /*投保标志*/
	TKSD_UVolumeType		Qty;                 /*数量*/
	TKSD_CByteType			ExecType;			 /*行权类型*/
	TKSD_CByteType			IsSelfClose;		 /*是否执行后期货自对冲*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_CByteType			Status;				 /*状态*/
	TKSD_DateType			ActionDay;			 /*申请日期*/	
	TKSD_TimeType			ApplyTime;			 /*申请时间*/
	TKSD_TraderIDType		CancelTraderNo;		 /*撤销交易员*/
	TKSD_TimeType			CancelTime;			 /*撤销时间*/
};

//期权行权撤销请求域
struct CKSD_ReqOptCancelExecField
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_TraderIDType		TraderNo;			 /*交易员*/	
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ClientIDType		ClientID;			 /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_SysOrderNo			ExecLocalNo;		 /*本地执行编号*/
	TKSD_SysOrderNo			ExecSysNo;			 /*系统执行编号*/
	TKSD_TraderIDType		CancelTraderNo;		 /*撤销交易员*/
};

//期权自对冲请求域
struct CKSD_ReqOptSelfCloseField
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_TraderIDType		TraderNo;			 /*交易员*/	
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ClientIDType		ClientID;			 /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_SysOrderNo			SelfCloseLocalNo;	 /*本地自对冲编号*/
	TKSD_UVolumeType		Qty;                 /*数量*/
	TKSD_CByteType			SelfCloseType;		 /*自对冲类型*/
};

//期权自对冲信息域
struct CKSD_OptSelfCloseField
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_TraderIDType		TraderNo;			 /*交易员*/	
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ClientIDType		ClientID;			 /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_SysOrderNo			SelfCloseLocalNo;	 /*本地自对冲编号*/
	TKSD_SysOrderNo			SelfCloseSysNo;		 /*系统自对冲编号*/
	TKSD_UVolumeType		Qty;                 /*数量*/
	TKSD_CByteType			SelfCloseType;		 /*自对冲类型*/
	TKSD_CByteType			Status;				 /*状态*/
	TKSD_DateType			ActionDay;			 /*申请日期*/	
	TKSD_TimeType			ApplyTime;			 /*申请时间*/
	TKSD_TraderIDType		CancelTraderNo;		 /*撤销交易员*/
	TKSD_TimeType			CancelTime;			 /*撤销时间*/
};

//期权自对冲撤单请求域
struct CKSD_ReqOptCancelSelfCloseField
{
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_TraderIDType		TraderNo;			 /*交易员*/	
	TKSD_MemberIDType		MemberID;			 /*会员号*/
	TKSD_ClientIDType		ClientID;			 /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约号*/
	TKSD_SysOrderNo			SelfCloseLocalNo;	 /*本地自对冲编号*/
	TKSD_SysOrderNo			SelfCloseSysNo;		 /*系统自对冲编号*/
	TKSD_TraderIDType		CancelTraderNo;		 /*撤销交易员*/
};


// 定价参考价信息域
struct CKSD_RefPriceField
{
	TKSD_DateType			TradeDate;           /*交易日期*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_PriceType          RefPrice;            /*报入价格*/
	TKSD_StatusType			SourceType;          /*报入来源*/
	TKSD_SysOrderNo			LocalOrderNo;        /*本地报单号*/
	TKSD_SysOrderNo			OrderNo;             /*系统报单号*/
	TKSD_TimeType			ApplyTime;           /*报入时间*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_CByteType          Status;              /*状态*/
};

// 定价场次状态域 
struct CKSD_PriceSessionStautsField
{
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_RoundIDType		RoundID;             /*轮次编号*/
	TKSD_CByteType          Status;              /*合约交易状态*/
	TKSD_CByteType          RoundPhase;          /*轮次阶段*/
};

// 定价报单域
struct CKSD_PriceOrderField
{
	TKSD_DateType			TradeDate;           /*交易日期*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_CByteType		    EntryType;           /*报单类型*/
	TKSD_CByteType          EntryPhase;          /*申报阶段*/
	TKSD_CByteType          CancelType;          /*撤单类型*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
	TKSD_PriceType          Price;               /*价格*/
	TKSD_UVolumeType        Qty;                 /*申报手数*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_RoundIDType		RoundID;             /*轮次编号*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地报单号*/
	TKSD_SysOrderNo			OrderNo;             /*系统报单号*/
	TKSD_TimeType			ApplyTime;           /*报入时间*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
	TKSD_CByteType          Status;              /*状态*/
	TKSD_PriceType          FrozenCash;          /*冻结保证金*/
};

// 定价申报状态域
struct CKSD_PriceOrderStatusField
{
	TKSD_DateType			ApplyDate;           /*申报日期*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_RoundIDType		RoundID;             /*轮次编号*/
	TKSD_CByteType          EntryType;           /*报单类型*/
	TKSD_CByteType          CancelType;          /*撤单类型*/
	TKSD_CByteType          EntryPhase;          /*申报阶段*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
	TKSD_UVolumeType        Qty;                 /*申报手数*/
	TKSD_PriceType          Price;               /*申报价格*/
	TKSD_PriceType          FrozenCash;          /*冻结保证金*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地报单号*/
	TKSD_SysOrderNo			OrderNo;             /*系统报单号*/
	TKSD_TimeType			ApplyTime;           /*申报时间*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
};

// 定价申报查询域 
struct CKSD_QryPriceOrderStatusField
{
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_LocalOrderNo		LocalOrderNo;        /*本地报单号*/
	TKSD_SysOrderNo			OrderNo;             /*系统报单号*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_DateType			TradeDate;           /*交易日期*/
	TKSD_RoundIDType		RoundID;             /*轮次编号*/
};

// 定价申报量域
struct CKSD_PriceApplyQtyField
{
	TKSD_DateType			ApplyDate;           /*申报日期*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_TradePurposeType   TradePurpose;        /*交易目的*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_RoundIDType		RoundID;             /*轮次编号*/
	TKSD_UVolumeType        BidLot1;             /*本轮市场申报买量*/
	TKSD_UVolumeType        AskLot1;             /*本轮市场申报卖量*/
	TKSD_UVolumeType        BidLot2;             /*本轮补充申报买量*/
	TKSD_UVolumeType        AskLot2;             /*本轮补充申报卖量*/
	TKSD_UVolumeType        BidLot3;             /*上轮市场申报买量*/
	TKSD_UVolumeType        AskLot3;             /*上轮市场申报卖量*/
	TKSD_UVolumeType        BidLot4;             /*上轮补充申报买量*/
	TKSD_UVolumeType        AskLot4;             /*上轮补充申报卖量*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
};

// 定价成交信息查询域 
struct CKSD_QryPriceMatchField
{
	TKSD_MatchNo			MatchNo;             /*成交编号*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
	TKSD_CByteType          MatchMode;           /*成交模式*/
};

// 定价成交信息域 
struct CKSD_PriceMatchField
{
	TKSD_MatchNo			MatchNo;             /*成交编号*/
	TKSD_TraderIDType		TraderNo;            /*交易员号*/
	TKSD_TradePurposeType	TradePurpose;        /*交易目的*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
	TKSD_CByteType          MatchMode;           /*成交模式*/
	TKSD_UVolumeType        Qty;                 /*成交手数*/
	TKSD_PriceType          Price;               /*成交价格*/
	TKSD_PriceType          Margin;              /*保证金金额*/
	TKSD_TimeType			MatchTime;           /*成交时间*/
	TKSD_DateType			MatchDate;           /*成交日期*/
	TKSD_ExchCode			ExchCode;            /*交易所代码*/
};

// 定价通用查询域 
struct CKSD_QryBptInfoField
{
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_RoundIDType		RoundID;             /*轮次编号*/
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_DByteType			MarketID;            /*市场代码*/
};

// 定价场次信息域 
struct CKSD_PriceSessionField
{
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_SessionNameType	SessionName;         /*场次名称*/
	TKSD_TimeType			QuoteTime;           /*开始时间*/
	TKSD_TimeType			EndTime;             /*结束时间*/
	TKSD_DByteType			IsSettlePrice;       /*是否为结算价*/
	TKSD_UVolumeType		OpenContinueTime;    /*开盘持续时间*/
	TKSD_UVolumeType        RefPriceStartContinueTime;/*参考价报入开始持续时间*/
	TKSD_UVolumeType		RefPriceEndContinueTime;/*参考价报入结束持续时间*/
	TKSD_UVolumeType        MrStartContinueTime1;/*首轮市场申报开始持续时间*/
	TKSD_UVolumeType        MrEndContinueTime1;  /*首轮市场申报结束持续时间*/
	TKSD_UVolumeType        FrStartContinueTime1;/*首轮补充申报开始持续时间*/
	TKSD_UVolumeType        FrEndContinueTime1;  /*首轮补充申报结束持续时间*/
	TKSD_UVolumeType        MrStartContinueTime2;/*后续轮市场申报开始持续时间*/
	TKSD_UVolumeType        MrEndContinueTime2;  /*后续轮市场申报结束持续时间*/
	TKSD_UVolumeType        FrStartContinueTime2;/*后续轮补充申报开始持续时间*/
	TKSD_UVolumeType        FrEndContinueTime2;  /*后续轮补充申报结束持续时间*/
	TKSD_UVolumeType        InitPriceSeqNo;      /*初始价序号*/
	TKSD_PriceType			DefaultInitPrice;    /*默认初始价*/
	TKSD_PriceType          InitPrice;           /*初始价*/
	TKSD_UVolumeType        FixPriceSeqNo;       /*定盘价序号*/
	TKSD_PriceType          FixPrice;            /*定盘价*/
	TKSD_PriceType			Qty;                 /*成交重量*/
	TKSD_PriceType			Updown;              /*涨跌*/
	TKSD_UVolumeType        Round;               /*轮数*/
};

// 定价当日轮次行情域 
struct CKSD_PriceRoundQuoteField
{
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_RoundIDType		RoundID;             /*轮次编号*/
	TKSD_PriceType			Price;               /*价格*/
	TKSD_TimeType			QuoteTime;           /*行情时间*/
	TKSD_TimeType			MrBeginTime;         /*本轮市场申报开始时间*/
	TKSD_TimeType			MrEndTime;           /*本轮市场申报结束时间*/
	TKSD_TimeType			FrBeginTime;         /*本轮补充申报开始时间*/
	TKSD_TimeType			FrEndTime;           /*本轮补充申报结束时间*/
	TKSD_UVolumeType        BidLot1;             /*市场申报买量*/
	TKSD_UVolumeType        AskLot1;             /*市场申报卖量*/
	TKSD_UVolumeType        BidLot2;             /*补充申报买量*/
	TKSD_UVolumeType        AskLot2;             /*补充申报卖量*/
	TKSD_PriceType          DefaultRoundPrice;   /*默认价格*/
	TKSD_TraderIDType		UserID;              /*操作员代码*/
};

// 定价申报方向域 
struct CKSD_PriceFrDirectionField
{
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_RoundIDType		RoundID;             /*轮次编号*/
	TKSD_CByteType          BsFlag;              /*买卖方向*/
};

// 定价订单持续请求域 
struct CKSD_PriceOrderSuatField
{
	TKSD_MemberIDType		MemberID;            /*会员号*/
	TKSD_ClientIDType		ClientID;            /*客户号*/
	TKSD_ContractIDType		ContractID;          /*合约代码*/
	TKSD_SessionIDType		SessionID;           /*场次编号*/
	TKSD_DByteType			Type;                /*操作类型*/
};

// 定价服务器同步时间域 
struct CKSD_BptSyncTimeField
{
	TKSD_DateType			TradeDate;           /*交易日期*/
	TKSD_TimestampType		SystemTime;          /*系统时间*/
	TKSD_CByteType          MarketType;          /*市场类型*/
};

//定价场内行情域 
struct CKSD_OnExchQuotField
{
	TKSD_MemberIDType			MemberID;            /*会员号*/
	TKSD_ContractIDType			ContractID;          /*合约代码*/
	TKSD_PriceType				LastPrice;           /*价格*/
	TKSD_ActArbiContractIDType  ContractCode;        /*合约业务代码*/
};

// 定价合约信息域 
struct CKSD_PriceContractInfoField
{
	TKSD_ContractIDType			ContractID;          /*合约代码*/
	TKSD_ContractNameType		ContractName;        /*合约名称*/
	TKSD_DByteType				MarketID;            /*市场代码*/
	TKSD_CByteType				VarietyType;         /*品种类别*/
	TKSD_VarietyIDType			VarietyID;           /*交割品种代码*/
	TKSD_CByteType				PriceUnit;           /*报价方式:价格单位*/
	TKSD_PriceType				Tick;                /*最小价位*/
	TKSD_UVolumeType			MaxHand;             /*最大申报限量*/
	TKSD_UVolumeType			MinHand;             /*最小申报限量*/
	TKSD_CByteType				InstOpenFlag;        /*合约活跃标志 1-活跃，2-不活跃*/
	TKSD_DByteType				WeightUnit;          /*重量单位*/
	TKSD_UVolumeType			Unit;                /*交易单位数量*/
	TKSD_ActArbiContractIDType  ContractCode;        /*合约业务代码*/
};

// 保证金询价合约信息域 
struct CKSD_RfqContractInfoField
{
	TKSD_ContractIDType			ContractID;          /*合约代码*/
	TKSD_ActArbiContractIDType  ContractCode;        /*合约业务代码*/
	TKSD_ContractNameType		ContractName;        /*合约名称*/
	TKSD_DByteType				MarketID;            /*市场编号*/
	TKSD_CByteType				VarietyType;         /*品种类别*/
	TKSD_UVolumeType			Unit;                /*每手乘数*/
	TKSD_PriceType				Tick;                /*最小价位*/
	TKSD_UVolumeType			MaxHand;             /*限价单最大可下单手数*/
	TKSD_UVolumeType			MinHand;             /*限价单最小可下单手数*/
	TKSD_PriceType				UpperLimit;          /*涨停板率*/
	TKSD_PriceType				LowerLimit;          /*跌停板率*/
	TKSD_CByteType				InstOpenFlag;        /*合约活跃标志 1-活跃，2-不活跃*/
	TKSD_CByteType				InstState;           /*合约交易状态*/
	TKSD_PriceType				RefPrice;            /*参考价*/
};

// 保证金询价市场信息域 
struct CKSD_RfqMarketInfoField
{
	TKSD_DByteType				MarketNo;            /*市场编号*/
	TKSD_DByteType				MarketID;            /*市场代码*/
	TKSD_MarketNameType			MarketName;          /*市场全称*/
	TKSD_CByteType				MarketType;          /*市场类型*/
	TKSD_CByteType				marketOpenFlag;      /*市场活跃标志 1-是，0-否*/
	TKSD_MarketStateType		marketTradeState;    /*市场交易状态*/
};

//交易员量化交易定单域
struct  CKSD_TraderStrategyOrderField
{
	TKSD_LocalOrderNo			LocalOrderNo;        /*本地委托号(dimple)*/
	TKSD_TraderIDType			TraderNo;            /*委托席位号*/
	TKSD_MemberIDType			MemberID;            /*会员编号*/
	TKSD_ClientIDType			ClientID;            /*客户编号*/
	TKSD_ContractIDType			ContractID;          /*合约号*/
	TKSD_CByteType				BsFlag;              /*买卖标志*/
	TKSD_CByteType				EoFlag;              /*开平标志*/
	TKSD_CByteType				ShFlag;              /*投保标志*/
	TKSD_PriceType				StopPrice;           /*止损(盈)价*/
	TKSD_PriceType				Price;               /*价格*/
	TKSD_UVolumeType			Qty;                 /*数量*/
	TKSD_CByteType				OrderType;           /*定单类型*/
	TKSD_CByteType				OrderAttr;           /*定单属性*/
	TKSD_TimeType				OrderTime;           /*委托时间*/
	TKSD_ActArbiContractIDType  ActArbiContractID;   /*套利合约号(dimple)*/
	TKSD_TradePurposeType		TradePurpose;        /*交易目的*/
	TKSD_Strategy               StrategyID;          /*交易策略代码*/
};

//合约交易状态改变域
struct CKSD_InstrumentStatusField
{
	TKSD_ActArbiContractIDType  InstrumentID;        /*合约代码*/
	TKSD_ByteType           	InstrumentStatus;    /*合约交易状态*/
	TKSD_ExchCode  				ExchCode;            /*交易所代码*/
	TKSD_StatusNote  			Note;                /*备注*/
};

#endif

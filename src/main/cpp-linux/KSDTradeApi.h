#ifndef KSD_TRADE_API_H_
#define KSD_TRADE_API_H_

#include <stdio.h>

#ifdef KSDTRADEAPI_EXPORTS
#define KSDTRADEAPI_LIB __declspec(dllexport)
#else
#ifdef WIN32
#define KSDTRADEAPI_LIB __declspec(dllimport)
#else
#define KSDTRADEAPI_LIB
#endif
#endif

#include "KSDUserApiStruct.h"

namespace KingstardimpleTradeApi
{

class CKSDTradeSpi
{
public:
	//已连接
	virtual void OnFrontConnected(){};	
	//未连接
	virtual void OnFrontDisconnected(){};	
	//踢除用户
	virtual void OnKickOff(){};
	//登录应答
	virtual void OnRspTraderLogin(const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTradeLoginField *pRspUserLoginRsp,bool bIsLast){};
	//登出应答
	virtual void OnRspTraderLogout(const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTradeLogoutField *pRspUserLogoutRsp,bool bIsLast){};
	//更新密码应答
	virtual void OnRspTraderPwdUpd(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RspTraderPwdUpd *pfldTraderPwdUpd){};
	//查询期货品种应答
	virtual void OnRspQryFtrVariety(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQryFtrVariety *pfldQryFtrVarietyRsp,bool bIsLast){};
	//查询期货合约应答
	virtual void OnRspQryFtrContract(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQryFtrContract *pfldQryFtrContractRsp,bool bIsLast){};
	//查询客户应答
	virtual void OnRspTraderQryClient(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderQryClient *pfldTraderQryClientRsp,bool bIsLast){};
	//查询交易员持仓应答
	virtual void OnRspTraderQryPosi (unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderQryPosi *pfldTraderQryPosiRsp,bool bIsLast){};
	//查询客户信用额度应答
	virtual void OnRspTraderQryMoney (unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderQryMoney *pfldTraderQryMoneyRsp,bool bIsLast){};
	//查询交易员敞口应答
	virtual void OnRspTraderExposureQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderExposureQry *pfldTraderExposureQryRsp,bool bIsLast){};
	//查询自营交易员资金应答
	virtual void OnRspTraderMoneyQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderMoneyQry *pfldTraderMoneyQryRsp,bool bIsLast){};
	//交易员持仓汇总查询应答
	virtual void OnRspTraderPosiAllQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderPosiAllQry *pfldTraderPosiAllQryRsp,bool bIsLast){};
	//交易员持仓明细查询应答
    virtual	void OnRspTraderPosiDtlQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderPosiDtlQry *pfldTraderPosiDtlQryRsp,bool bIsLast){};
	//成交明细查询应答
	virtual void OnRspMatchDtlQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspMatchDtlQry *pfldMatchDtlQryRsp,bool bIsLast){};
	//委托汇总查询应答
	virtual void OnRspOrderAllQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspOrderAllQry *pfldOrderAllQryRsp,bool bIsLast){};
	//委托明细查询应答
	virtual void OnRspOrderDtlQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspOrderDtlQry *pfldOrderDtlQryRsp,bool bIsLast){};
	//查询套利合约应答
	virtual void OnRspFldFtrArbiContract(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspFldFtrArbiContract *pfldFldFtrArbiContractRsp,bool bIsLast){};
	//查询客户库存应答
	virtual void OnRspClientQryStorage(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspClientQryStorage *pfldClientQryStorageRsp,bool bIsLast){};
	//查询交易员库存应答
	virtual void OnRspTraderQryStorage(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderQryStorage *pfldTraderQryStorageRsp,bool bIsLast){};
	//成交统计信息查询应答
	virtual void OnRspTraderMatchStatQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderMatchStatQry *pfldTraderMatchStatQryRsp,bool bIsLast){};
	//交易所资金查询应答
	virtual void OnRspQryExchMoney(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQryExchMoney *pfldQryExchMoneyRsp,bool bIsLast){};
	//市场状态查询应答
	virtual void OnRspQryMktStatus(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQryMktStatus *pfldQryMktStatusRsp,bool bIsLast){};
	//中金所市场状态通知
	virtual void OnNtyMktStatus (unsigned int seqno ,const CKSD_NtyQryMktStatus *pfldQryMktStatusNty,bool bIsLast){};
	//资金持仓通知
	virtual void OnNtyMemberCapPosi(unsigned int seqno,const CKSD_NtyTraderNoCap *pfldTraderNoCapNty,const CKSD_NtyTraderPosi *pfldTraderPosiNty,const CKSD_NtyOptMixPosi * pfldOptMixPosiNty,bool bIsLast){};
	//交易员撤单应答
	virtual void OnRspTraderQuitOrder(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderQuitOrder *pfldTraderQuitOrderRsp, bool bIsLast){};
	//交易员定单应答（未复核定单应答）
	virtual void OnRspTraderInsertOrders(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderInsertOrders  *pfldTraderInsertOrdersRsp,bool bIsLast){};
	//交易员定单回报(未复核和已复核订单回报)
	virtual void OnRtnTraderInsertOrders(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RtnTraderInsertOrders  *pfldTraderInsertOrdersRtn,bool bIsLast){};
	//交易员交割中立仓撤单回报
	virtual void RspTraderQuitDeliveryOrder(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderQuitDeliveryOrder  *pfldTraderQuitDeliveryOrderRsp,bool bIsLast){};
	//交易员交割申报中立仓单回报
	virtual void OnRtnTraderInsertDeliveryOrders(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RtnTraderInsertDeliveryOrders  *pfldTraderInsertDeliveryOrdersRtn,bool bIsLast){};
	//查询交割中立仓成交应答
	virtual void OnRspTraderQryDeliveryMatch(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderQryDeliveryMatch   *pfldTraderQryDeliveryMatchRsp,bool bIsLast){};
	//查询交易员交易目的应答
	virtual void OnRspQryTraderPurpose(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQryTraderPurpose   *pfldQryTraderPurposeRsp,bool bIsLast){};
	//查询交割中立仓委托应答
	virtual void OnRspTraderQryDeliveryOrder(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspTraderQryDeliveryOrder  *pfldTraderQryDeliveryOrderRsp,bool bIsLast){};
	//查询委托参数应答
	virtual void OnRspQryOrderParar(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQryOrderPara  *pfldQryOrderParaRsp,bool bIsLast){};
	//查询系统参数应答
	virtual void OnRspQrySystemPara(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQrySystemPara  *pfldQrySystemParaRsp,bool bIsLast){};
	//查询递延补偿费率应答
	virtual void OnRspQryDeferFeeRate(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_DeferFeeRateByFund  *pfldDeferFeeRateByFundRsp,bool bIsLast){};
	//递延补偿费率通知
	virtual void OnNtyDeferFeeRateByFund(unsigned int seqno,const CKSD_DeferFeeRateByFund  *pfldDeferFeeRateByFundNty,bool bIsLast){};
	//交易员成交通知
	virtual void OnNtyTraderMatch(unsigned int seqno,const CKSD_NtyTraderMatch  *pfldTraderMatchNty,bool bIsLast){};
	//交易员交割中立仓成交通知
	virtual void OnNtyTraderDeliveryMatch(unsigned int seqno,const CKSD_NtyTraderMatch  *pfldTraderMatchNty,bool bIsLast){};
	//查询会员持仓应答
	virtual void OnRspMemberPosiQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspMemberQryPosi  *pfldMemberQryPosiRsp,bool bIsLast){};
	//查询交易员交易编码关系应答
	virtual void OnRspClientMemberTrader(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspClientMemberTrader  *pfldClientMemberTraderRsp,bool bIsLast){};
	//交易员认申赎下单应答
	virtual void OnRspTraderETFOrders(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_ETFOrder  *pfldETFOrderRsp,bool bIsLast){};
	//查询交易员认申赎信息应答
	virtual void OnRspQryTraderETFOrders(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_ETFOrder  *pfldETFOrderRsp,bool bIsLast){};
	//查询ETF申赎清单应答
	virtual void OnRspQryETFList(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspETFList  *pfldETFListRsp,bool bIsLast){};
	//查询业务参数应答
	virtual void OnRspQryPara(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspPara *pfldPara,bool bIsLast){};
	//递延交收行情
	virtual void OnNtyRptDeferQuot(unsigned int seqno,const CKSD_DeferOrder *pfldDeferOrder,bool bIsLast){};
	//保证金查询应答
	virtual void OnRspTradeMarginRateQry(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg,const CKSD_TradeMarginRateQry *pfldTradeMarginRate,bool bIsLast){};
	//交易手续费查询应答
	virtual void OnRspTradeFtrFeeQry(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg,const CKSD_TradeFtrFee *pfldTradeFtrFee,bool bIsLast){};
	//交割手续费查询应答
	virtual void OnRspTradeDeliveryFeeQry(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg,const CKSD_TradeDeliveryFee *pfldTradeDeliveryFee,bool bIsLast){};
	//报价商报单回报
	virtual void OnRtnMakerQuote(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RtnMakerQuote *pfldMakerQuote,bool bIsLast){};
	//报价商撤单回报
	virtual void OnRtnMakerCancelQuote(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RtnMakerCancelQuote *pfldMakerCancelQuote,bool bIsLast){};
	//报价成交通知
	virtual void OnNtyQuoteMatch(unsigned int seqno, const CKSD_NtyQuoteMatch *pfldQuoteMatch,bool bIsLast){};
	//单腿策略定单应答
	virtual void OnRspTraderInsertPreOrder(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RspPreOrder *pfldRspPreOrder,bool bIsLast){};
	//取消策略定单应答
	virtual void OnRspTraderCancelPreOrder(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RspCancelPreOrder *pfldRspCancelPreOrder,bool bIsLast){};
	//修改策略定单应答
	virtual void OnRspTraderUpdPreOrder(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RspPreOrder *pfldRspPreOrder,bool bIsLast){};
	//查询策略定单应答
	virtual void OnRspTraderQryPreOrder(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RspQryPreOrder *pfldRspQryPreOrder,bool bIsLast){};
	//两腿策略定单应答
	virtual void OnRspTraderDoublePreOrder(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RspDoublePreOrderVec *pfldRspDoublePreOrder,bool bIsLast){};
	//手动触发策略定单应答
	virtual void OnRspTraderTrigPreOrder(unsigned int seqno, const CKSD_RspInfoField *pfldRspMsg, const CKSD_RspTrigPreOrder *pfldRspTrigPreOrder,bool bIsLast){};
	//报价平盘应答
	virtual void OnRspOffsetOrder(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspOffsetOrder *pfldRspQuoteOffset) {};
	//贵金属实时头寸查询应答
	virtual void OnRspMetalPosiQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQuoteMetalPosi *pfldQuoteMetalPosi,bool bIsLast){};
	//美元实时头寸查询应答
	virtual void OnRspUSDPosiQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQuoteUSDPosi *pfldQuoteUSDPosi,bool bIsLast){};
	//报价市场状态通知
	virtual void OnNtyQuoteMarketStatus(unsigned int seqno,const CKSD_QuoteMarketInfo *pfldQuoteMarketInfo){};
	//报价合约状态通知
	virtual void OnNtyQuoteInstStatus(unsigned int seqno,const CKSD_QuoteContractInfo *pfldQuoteContractInfo){};
	//报价合约状态查询应答
	virtual void OnRspQryQuoteContractStatus(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_QuoteContractInfo *pfldQuoteContractInfo,bool bIsLast){};
	//报价商报价委托查询应答
	virtual void OnRspQuoteOrderInfoQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspQuoteOrderQry *pfldQuoteOrder,bool bIsLast){};
	//报价商报价成交查询应答
	virtual void OnRspQuoteMatchInfoQry(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_NtyQuoteMatch *pfldQuoteMatch,bool bIsLast){};
	//报价源设置应急模式应答
	virtual void OnRspQuoteSetEmergencyMode(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_QuoteSetEmergencyMode *pfldQuoteSetEmergencyMode){};
	//报价持仓通知
	virtual void OnNtyQuotePosi(unsigned int seqno,const CKSD_RspQuoteMetalPosi *pfldQuoteMetalPosi){};
	//期权行权应答
	virtual void OnRspTraderOptExec(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_OptExecField *pfldOptExec,bool bIsLast){};
	//期权行权撤销应答
	virtual void OnRspTraderOptCancelExec(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_OptExecField *pfldOptExec,bool bIsLast){};
	//期权自对冲应答
	virtual void OnRspTraderOptSelfClose(unsigned int seqno,CKSD_RspInfoField *pfldRspMsg,const CKSD_OptSelfCloseField *pfldOptSelfClose,bool bIsLast){};
	//期权自对冲撤销应答
	virtual void OnRspTraderOptCancelSelfClose(unsigned int seqno,CKSD_RspInfoField *pfldRspMsg,const CKSD_OptSelfCloseField *pfldOptSelfClose,bool bIsLast){};
	//期权询价应答
	virtual void OnRspOptInquire(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspOptInquireOrder *pvfldRspOptInquireOrder,bool bIsLast){};
	//期权询价通知
	virtual void OnRtnOptInquire(unsigned int seqno,const CKSD_RtnOptInquireOrder *pvfldRtnOptInquire){};
	//做市商期权报单应答
	virtual void OnRspOptionQuote(unsigned int seqno,const CKSD_RspInfoField *pfldRspMsg,const CKSD_RspOptQuetoOrder *pvfldRspOptQueto,bool bIsLast){};
	//做市商期权撤单应答
	virtual void OnRspOptCancelQuote(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_RspOptQuetoOrderCancel* pvfldRspOptQuetoCancel, bool bIsLast) {};
	//定价场次状态改变广播
	virtual void OnNtyBptSessionStauts(unsigned int seqno, const CKSD_PriceSessionStautsField* pfldPriceSessionStauts) {};
	//定价参考价报入应答
	virtual void OnRspBptInsertRefPrice(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_RefPriceField* pfldRefPrice, bool bIsLast) {};
	//定价当日成交查询应答
	virtual void OnRspQryBptMatch(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_PriceMatchField* pvfldPriceMatch, bool bIsLast) {};
	//定价报单申请应答
	virtual void OnRspBptTraderInsertOrder(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_PriceOrderField* pfldPriceOrder, bool bIsLast) {};
	//定价系统撤单广播
	virtual void OnRtnBptSysCancelOrder(unsigned int seqno, const CKSD_PriceOrderStatusField* pfldPriceOrderStatus) {};
	//定价补充申报方向广播
	virtual void OnNtyBptFrDirection(unsigned int seqno, const CKSD_PriceFrDirectionField* pfldPriceFrDirection) {};
	//定价服务器时间同步通知
	virtual void OnNtyBptSyncTime(unsigned int seqno, const CKSD_BptSyncTimeField* pfldBptSyncTime) {};
	//定价场次查询应答
	virtual void OnRspQryBptSession(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_PriceSessionField* pvfldPriceSession, bool bIsLast) {};
	//定价初始价广播
	virtual void OnNtyBptInitPrice(unsigned int seqno, const CKSD_PriceSessionField* pfldPriceSession) {};
	//定价定盘价广播
	virtual void OnNtyBptFixPrice(unsigned int seqno, const CKSD_PriceSessionField* pfldPriceSession) {};
	//定价场次状态查询应答
	virtual void OnRspQryBptSessionStatus(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_PriceSessionStautsField* pvfldPriceSessionStauts, bool bIsLast) {};
	//定价初始价查询应答
	virtual void OnRspQryBptInitPrice(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_PriceSessionField* pvfldPriceSession, bool bIsLast) {};
	//定价定盘价查询应答
	virtual void OnRspQryBptFixPrice(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_PriceSessionField* pvfldPriceSession, bool bIsLast) {};
	//定价申报量查询应答
	virtual void OnRspQryBptApplyQty(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_PriceApplyQtyField* pvfldPriceApplyQty, bool bIsLast) {};
	//定价参考价查询应答
	virtual void OnRspQryBptRefPrice(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_RefPriceField* pvfldRefPrice, bool bIsLast) {};
	//定价委托申报状态查询
	virtual void OnRspQryBptOrder(unsigned int seqno, const CKSD_RspInfoField* pfldRspMsg, const CKSD_PriceOrderField* pvfldPriceOrder, bool bIsLast) {};
	//合约交易状态改变广播
	virtual void OnNtyContractStatus(unsigned int seqno, const CKSD_InstrumentStatusField* pfldInstrumentStatus){};
};

class KSDTRADEAPI_LIB CKSDTradeApi
{
public:
	//创建接口
	static CKSDTradeApi *CreateKSDTradeApi();
	//释放接口
	virtual void Release()=0;
public:
	//注册回调接口
	virtual void RegisterSpi(CKSDTradeSpi *pKSDTradeSpi)=0;
	//订阅私有流
	virtual int SubscribePrivateFlow(bool restartflag=false)=0;
	//订阅公共流
	virtual int SubscribePublicFlow(bool restartflag=false)=0;
	//注册前置地址
	virtual void RegisterServer(char *ip,int port)=0;
	//初始化
	virtual void Init(bool logflag=true)=0;
	//等待线程结束
	virtual void Join()=0;
	//修改密码请求
	virtual int ReqTraderPwdUpd(unsigned int *seqno, CKSD_ReqTraderPwdUpd *pTraderLogoutReq)=0;
	//登录请求
	virtual int ReqTraderLogin(CKSD_ReqTradeLoginField *pTradeLoginReq)=0;
	//登出请求
	virtual int ReqTraderLogout(CKSD_ReqTradeLogoutField *pTradeLogoutReq)=0;
	//查询期货品种请求
	virtual int ReqQryFtrVariety(unsigned int *seqno, CKSD_ReqQryFtrVariety *pQryFtrVarietyReq)=0;
	//查询期货合约
	virtual int ReqQryFtrContract(unsigned int *seqno, CKSD_ReqQryFtrContract *pQryFtrContractReq)=0;
	//查询客户请求
	virtual int ReqTraderQryClient(unsigned int *seqno,CKSD_ReqTraderQryClient *pTraderQryClientReq)=0;
	//查询套利合约请求
	virtual int ReqFldFtrArbiContract(unsigned int *seqno )=0;
	//查询交易员持仓请求
	virtual int ReqTraderQryPosi(unsigned int *seqno,CKSD_ReqTraderQryPosi *pTraderQryPosiReq)=0;
	//查询客户信用额度请求
	virtual int ReqTraderQryMoney(unsigned int *seqno,CKSD_ReqTraderQryMoney *pTraderQryMoneyReq)=0;
	//查询交易员敞口请求
	virtual int ReqTraderExposureQry(unsigned int *seqno, CKSD_ReqTraderExposureQry *pTraderExposureQryReq)=0;	
	//查询自营交易员资金请求
	virtual int ReqTraderMoneyQry(unsigned int *seqno,CKSD_ReqTraderMoneyQry *pTraderMoneyQryReq)=0;
	//交易员持仓汇总查询请求
	virtual int ReqTraderPosiAllQry(unsigned int *seqno,CKSD_ReqTraderPosiAllQry *pTraderPosiAllQryReq)=0;
	//交易员持仓明细查询请求
	virtual int ReqTraderPosiDtlQry(unsigned int *seqno,CKSD_ReqTraderPosiDtlQry *pTraderPosiDtlQryReq)=0;
	//成交明细查询请求
	virtual int ReqMatchDtlQry(unsigned int *seqno,CKSD_ReqMatchDtlQry *pMatchDtlQryReq)=0;
	//委托汇总查询请求
	virtual int ReqOrderAllQry(unsigned int *seqno,CKSD_ReqOrderAllQry *pOrderAllQryReq)=0;
	//委托明细查询请求
	virtual int ReqOrderDtlQry(unsigned int *seqno,CKSD_ReqOrderDtlQry *pOrderDtlQryReq)=0;
	//查询客户库存请求
	virtual int ReqClientQryStorage(unsigned int *seqno,CKSD_ReqClientQryStorage *pFldClientQryStoragetReq)=0;
	//查询交易员库存请求
	virtual int ReqTraderQryStorage(unsigned int *seqno,CKSD_ReqTraderQryStorage *pFldTraderQryStorageReq)=0;
	//成交统计信息查询请求
	virtual int ReqQryTraderMatchStat(unsigned int *seqno,CKSD_ReqTrader *pFldQryTraderMatchStatReq)=0;
	//交易所资金查询请求
	virtual int ReqQryExchMoney(unsigned int *seqno,CKSD_ReqQryExchMoney *pFldQryExchMoneyReq)=0;
	//查询市场状态请求
	virtual int ReqQryMarketStatus(unsigned int *seqno)=0;
	//交易员撤单请求
	virtual int ReqTraderQuitOrder(unsigned int *seqno,CKSD_ReqTraderQuitOrder * pfldTraderQuitOrderReq)=0;
	//交易员定单请求
	virtual int ReqTraderInsertOrders(unsigned int *seqno,CKSD_ReqTraderInsertOrders  *pFldTraderInsertOrdersReq)=0;
	//交易员交割中立仓定单请求
	virtual int ReqTraderInsertDeliveryOrders(unsigned int *seqno,CKSD_ReqTraderInsertDeliveryOrders *pFldTraderInsertDeliveryOrdersReq)=0;
	//交易员交割中立仓撤单请求
	virtual int ReqTraderQuitDeliveryOrder(unsigned int *seqno,CKSD_ReqTraderQuitDeliveryOrder  *pFldTraderQuitDeliveryOrderReq)=0;
	//查询交割中立仓委托请求
	virtual int ReqTraderQryDeliveryOrder(unsigned int *seqno,CKSD_ReqTrader *pFldTrader)=0;
	//查询交割中立仓成交请求
	virtual int ReqTraderQryDeliveryMatch(unsigned int *seqno,CKSD_ReqTrader *pFldTrader)=0;
	//查询委托参数请求
	virtual int ReqQryOrderPara(unsigned int *seqno,CKSD_ReqContract *pfldQryOrderParaReq)=0;
	//查询系统参数请求
	virtual int ReqQrySystemPara(unsigned int *seqno)=0;
	//查询递延补偿费率请求
	virtual int ReqQryDeferFeeRate(unsigned int *seqno)=0;
	//查询会员持仓请求
	virtual int ReqMemberPosiQry(unsigned int *seqno, CKSD_ReqMemberQryPosi *pfldMemberQryPosiReq)=0;
	//查询交易员交易编码关系请求
	virtual int ReqClientMemberTrader(unsigned int *seqno, CKSD_ReqClientMemberTrader *pfldClientMemberTraderReq)=0;
	//查询交易员交易目的请求
	virtual int ReqQryTraderPurpose(unsigned int *seqno,CKSD_ReqTrader *pFldTrader)=0;
	//交易员认申赎下单请求
	virtual int ReqTraderETFOrders(unsigned int *seqno, CKSD_ETFOrder *pfldETFOrderReq)=0;
	//交易员认申赎信息查询请求
	virtual int ReqQryTraderETFOrders(unsigned int *seqno, CKSD_ETFOrder *pfldETFOrderReq)=0;
	//查询ETF申赎清单请求
	virtual int ReqQryETFList(unsigned int *seqno, CKSD_ReqETFList *pfldETFList)=0;
	//查询业务参数请求
	virtual int ReqQryPara(unsigned int *seqno, CKSD_ReqPara *pfldPara)=0;
	//保证金查询请求
	virtual int ReqTradeMarginRateQry(unsigned int *seqno,CKSD_TradeMarginRateQry *pfldTradeMarginRate)=0;
	//交易手续费查询请求
	virtual int ReqTradeFtrFeeQry(unsigned int *seqno,CKSD_TradeFtrFee *pfldTradeFtrFee)=0;
	//交割手续费查询请求
	virtual int ReqTradeDeliveryFeeQry(unsigned int *seqno,CKSD_TradeDeliveryFee *pfldTradeDeliveryFee)=0;
	//报价商报单请求
	virtual int ReqMakerQuote(unsigned int *seqno,CKSD_MakerQuote *pfldMakerQuote)=0;
	//报价商撤单请求
	virtual int ReqMakerCancelQuote(unsigned int *seqno,CKSD_MakerCancelQuote *pfldMakerCancelQuote)=0;
	//单腿策略定单请求
	virtual int ReqTraderInsertPreOrder(unsigned int *seqno,CKSD_ReqInsertPreOrder *pfldReqInsertPreOrder)=0;
	//取消策略定单请求
	virtual int ReqTraderCancelPreOrder(unsigned int *seqno,CKSD_ReqCancelPreOrder *pfldReqCancelPrerOrder)=0;
	//修改策略定单请求
	virtual int ReqTraderUpdPreOrder(unsigned int *seqno,CKSD_ReqUpdPreOrder *pfldReqUpdPreOrder)=0;
	//查询策略定单请求
	virtual int ReqTraderQryPreOrder(unsigned int *seqno,CKSD_ReqQryPreOrder *pfldReqQryPreOrder)=0;
	//两腿策略定单请求
	virtual int ReqTraderDoublePreOrder(unsigned int *seqno,CKSD_ReqDoublePreOrderVec *pfldReqDoublePreOrder)=0;
	//手动触发策略单请求
	virtual int ReqTraderTrigPreOrder(unsigned int *seqno,CKSD_ReqTrigPreOrder *pfldReqTrigPreOrder)=0;
	//报价平盘请求
	virtual int ReqOffsetOrder(unsigned int *seqno,CKSD_ReqOffsetOrder *pfldReqOffsetOrder)=0;
	//贵金属实时头寸查询请求
	virtual int ReqMetalPosiQry(unsigned int *seqno,CKSD_ReqQuotePosiQry *pfldReqQuotePosiQry)=0;
	//美元实时头寸查询请求
	virtual int ReqUSDPosiQry(unsigned int *seqno,CKSD_ReqQuotePosiQry *pfldReqQuotePosiQry)=0;
	//报价合约状态查询请求
	virtual int ReqQryQuoteContractStatus(unsigned int *seqno,CKSD_QuoteContractInfoReq *pfldQuoteContractInfoReq)=0;
	//报价商报价委托查询请求
	virtual int ReqQuoteOrderInfoQry(unsigned int *seqno, CKSD_ReqQuoteOrderQry *pfldQuoteOrderQryReq)=0;
	//报价商报价成交查询请求
	virtual int ReqQuoteMatchInfoQry(unsigned int *seqno,CKSD_ReqQuoteOrderQry *pfldQuoteMatchQryReq)=0;
	//报价源设置应急模式请求
	virtual int ReqQuoteSetEmergencyMode(unsigned int *seqno,CKSD_QuoteSetEmergencyMode *pfldQuoteSetEmergencyMode)=0;
	//密文登录请求
	virtual int ReqTraderEncLogin(CKSD_ReqEncTradeLoginField *pEncTradeLoginReq)=0;
	//期权行权请求
	virtual int ReqTraderOptExec(unsigned int *seqno,CKSD_ReqOptExecField *pfldReqOptExec)=0;
	//期权行权撤销请求
	virtual int ReqTraderOptCancelExec(unsigned int *seqno,CKSD_ReqOptCancelExecField *pfldReqOptCancelExec)=0;
	//期权自对冲请求
	virtual int ReqTraderOptSelfClose(unsigned int *seqno,CKSD_ReqOptSelfCloseField *pfldReqOptSelfClose)=0;
	//期权自对冲撤销请求
	virtual int ReqTraderOptCancelSelfClose(unsigned int *seqno,CKSD_ReqOptCancelSelfCloseField *pfldReqOptCancelSelfClose)=0;
	//期权询价请求
	virtual int ReqOptInquire(unsigned int *seqno,CKSD_ReqOptInquireOrder *pfldReqOptInquireOrder)=0;
	//做市商期权报单请求
	virtual int ReqOptionQuote(unsigned int *seqno,CKSD_ReqOptQuetoOrderVec *pfldReqOptQuetoOrder)=0;
	//做市商期权撤单请求
	virtual int ReqOptCancelQuote(unsigned int *seqno,CKSD_ReqOptQuetoOrderCancel *pfldReqOptQuetoOrderCancel)=0;
	//定价参考价报入请求
	virtual int ReqBptInsertRefPrice(unsigned int* seqno, CKSD_RefPriceField* pfldRefPrice)=0;
	//定价当日成交查询请求
	virtual int ReqQryBptMatch(unsigned int* seqno, CKSD_QryPriceMatchField* pfldQryPriceMatch) = 0;
	//定价报单申请请求
	virtual int ReqBptTraderInsertOrder(unsigned int* seqno, CKSD_PriceOrderField* pfldPriceOrder) = 0;
	//定价场次查询请求
	virtual int ReqQryBptSession(unsigned int* seqno, CKSD_QryBptInfoField* pfldQryBptInfo) = 0;
	//定价场次状态查询请求
	virtual int ReqQryBptSessionStatus(unsigned int* seqno, CKSD_QryBptInfoField* pfldQryBptInfo) = 0;
	//定价初始价查询请求
	virtual int ReqQryBptInitPrice(unsigned int* seqno, CKSD_QryBptInfoField* pfldQryBptInfo) = 0;
	//定价定盘价查询请求
	virtual int ReqQryBptFixPrice(unsigned int* seqno, CKSD_QryBptInfoField* pfldQryBptInfo) = 0;
	//定价申报量查询请求
	virtual int ReqQryBptApplyQty(unsigned int* seqno, CKSD_QryPriceOrderStatusField* pfldQryPriceOrderStatus) = 0;
	//定价参考价查询请求
	virtual int ReqQryBptRefPrice(unsigned int* seqno, CKSD_QryPriceOrderStatusField* pfldQryPriceOrderStatus) = 0;
	//定价委托申报状态查询请求
	virtual int ReqQryBptOrder(unsigned int* seqno, CKSD_QryPriceOrderStatusField* pfldQryPriceOrderStatus) = 0;
	//交易员量化交易定单请求
	virtual int ReqTraderInsertStrategyOrders(unsigned int* seqno, CKSD_TraderStrategyOrderField* pfldTraderStrategyOrder) = 0;


protected:
	~CKSDTradeApi();
private:
};




}


#endif
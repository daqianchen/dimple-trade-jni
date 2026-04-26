#ifndef KSD_Quot_API_H
#define KSD_Quot_API_H

#include <stdio.h>

#ifdef  KSDQUOTAPI_EXPORTS
#define KSDQuotAPI_LIB __declspec(dllexport)
#else
#ifdef	WIN32
#define KSDQuotAPI_LIB __declspec(dllimport)
#else
#define KSDQuotAPI_LIB 
#endif
#endif
#include "KSDUserApiStruct.h"

namespace KingstardimplequotAPI
{
	class CKSDQuotSpi 
	{
	public:
		//已连接
		virtual void OnFrontConnected(){};
		//未连接
		virtual void OnFrontDisconnected(){};
		//踢除用户
		virtual void OnKickOff(){};
		//登录应答
		virtual void OnRspUserLogin(const CKSD_RspInfoField *pRspMsg,const CKSD_RspTradeLoginField *pRspUserLogin,bool bIsLast){};
		//登出应答
		virtual void OnRspUserLogout(const CKSD_RspInfoField *pRspMsg,const CKSD_RspTradeLogoutField *pRspUserLogout,bool bIsLast){};
		//行情服务的深度行情通知
		virtual void OnMarketDataMblQuot(unsigned int seqno,const CKSD_RtyBestQuot *pRtyBestQuot, const CKSD_RtyMBLQuot *pRtyMBLQuot ,bool bIsLast){};
		//报价商报价行情通知
		virtual void OnNtyMakerQuoteQuot(unsigned int seqno,const CKSD_NtyQuoteQuot *pNtyQuoteQuot){};
		//报价市场成交行情通知
		virtual void OnNtyQuoteMatchQuot(unsigned int seqno,const CKSD_NtyQuoteMatchQuot *pNtyQuoteMatchQuot){};
		//报价市场初始行情通知
		virtual void OnNtyQuoteInitialQuot(unsigned int seqno,const CKSD_NtyQuoteClearQuot *pNtyQuoteInitialQuot){};	
		//报价市场日终行情通知
		virtual void OnNtyQuoteClearQuot(unsigned int seqno,const CKSD_NtyQuoteClearQuot *pNtyQuoteClearQuot){};
		//当日轮次行情广播
		virtual void OnNtyBptRoundQuot(unsigned int seqno, const CKSD_PriceRoundQuoteField* pNtyPriceRoundQuote) {};
	};
	
	class KSDQuotAPI_LIB CKSDQuotApi
	{
	public: 
		//创建接口
		static CKSDQuotApi *CreateCKSDQuotApi();
		//释放接口
		virtual void Release()=0;
	public:
		//注册回调接口
		virtual void RegisterSpi(CKSDQuotSpi *pKSDQuotSpi)=0;
		//订阅私有流
		virtual int SubscribePrivateFlow(bool restartflag=false)=0;
		//订阅公共流
		virtual int SubscribePublicFlow(bool restartflag=false)=0;
		//注册前置地址
		virtual int RegisterServer(char *ip,int port)=0;
		//初始化
		virtual void Init(bool logflag=true)=0;
		//等待线程结束
		virtual void Join()=0;
		//登录请求
		virtual int ReqUserLogin(CKSD_ReqTradeLoginField *pUserLoginReq)=0;  
		//登出请求
		virtual int ReqUserLogout(CKSD_ReqTradeLogoutField *pUserLogoutReq)=0;
		//密文登录请求
		virtual int ReqUserEncLogin(CKSD_ReqEncTradeLoginField *pEncTradeLoginReq)=0;	
	protected:
		~CKSDQuotApi();
	private:
	};
}
#endif

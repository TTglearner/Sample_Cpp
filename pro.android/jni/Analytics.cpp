#include "Analytics.h"
#include <jni.h>
#include <android/log.h>
#include "PluginJniHelper.h"
using namespace anysdk::framework;

#define  LOG_TAG    "Analytics"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__);
extern "C"{
void Java_com_anysdk_sample_wrapper_nativeStartSession(JNIEnv*  env, jobject thiz)
{
	Analytics::getInstance()->startSession();
}

void Java_com_anysdk_sample_wrapper_nativeStopSession(JNIEnv*  env, jobject thiz)
{
	Analytics::getInstance()->stopSession();
}
}

Analytics* Analytics::_pInstance = NULL;

Analytics::Analytics()
{
	_pAnalytics = AgentManager::getInstance()->getAnalyticsPlugin();
	if(!_pAnalytics) return;
	_pAnalytics->setDebugMode(true);
}

Analytics::~Analytics()
{

}

Analytics* Analytics::getInstance()
{
    if (_pInstance == NULL) {
        _pInstance = new Analytics();
    }
    return _pInstance;
}

void Analytics::purge()
{
    if (_pInstance)
    {
        delete _pInstance;
        _pInstance = NULL;
    }
}

void Analytics::startSession()
{
	if(!_pAnalytics) return;
	_pAnalytics->startSession();
}

void Analytics::stopSession()
{
	if(!_pAnalytics) return;
	_pAnalytics->stopSession();
}

void Analytics::setSessionContinueMillis(long millis)
{
	if(!_pAnalytics) return;
	_pAnalytics->setSessionContinueMillis(millis);
}

void Analytics::setCaptureUncaughtException(bool isEnabled)
{
	if(!_pAnalytics) return;
	_pAnalytics->setCaptureUncaughtException(isEnabled);
}

void Analytics::logError(string errorId, string message)
{
	if(!_pAnalytics) return;
	_pAnalytics->logError(errorId.c_str(),message.c_str());
}

void Analytics::logEvent(string eventId)
{
	if(!_pAnalytics) return;
	_pAnalytics->logEvent(eventId.c_str());
}

void Analytics::logEvent(string eventId, map<string, string> paramMap)
{
	if(!_pAnalytics) return;
	_pAnalytics->logEvent(eventId.c_str(), &paramMap);
}

void Analytics::logTimedEventBegin(string eventId)
{
	if(!_pAnalytics) return;
	_pAnalytics->logTimedEventBegin("logTimedEventBegin");
}
void Analytics::logTimedEventEnd(string eventId)
{
	if(!_pAnalytics) return;
	_pAnalytics->logTimedEventEnd(eventId.c_str());
}

void Analytics::setAccount()
{
	if(!_pAnalytics || !isFunctionSupported("setAccount")) return;

	map<string, string> paramMap;
	paramMap["Account_Id"] = "123456";
	paramMap["Account_Name"] = "test";
	paramMap["Account_Type"] = Analytics::ConvertToString(ANONYMOUS);
	paramMap["Account_Level"] = "1";
	paramMap["Account_Age"] = "1";
	paramMap["Account_Operate"] = Analytics::ConvertToString(LOGIN);
	paramMap["Account_Gender"] = Analytics::ConvertToString(MALE);
	paramMap["Server_Id"] = "1";

	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("setAccount",&data, NULL);
}

void Analytics::onChargeRequest()
{
	if(!_pAnalytics || !isFunctionSupported("onChargeRequest")) return;

	map<string, string> paramMap;
	paramMap["Order_Id"] = "123456";
	paramMap["Product_Name"] = "test";
	paramMap["Currency_Amount"] = Analytics::ConvertToString(2.0);
	paramMap["Currency_Type"] = "1";
	paramMap["Payment_Type"] = "1";
	paramMap["Virtual_Currency_Amount"] = Analytics::ConvertToString(100);

	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("onChargeRequest",&data, NULL);
}

void Analytics::onChargeOnlySuccess()
{
	if(!_pAnalytics || !isFunctionSupported("onChargeOnlySuccess")) return;

	map<string, string> paramMap;
	paramMap["Order_Id"] = "123456";
	paramMap["Product_Name"] = "test";
	paramMap["Currency_Amount"] = Analytics::ConvertToString(2.0);
	paramMap["Currency_Type"] = "1";
	paramMap["Payment_Type"] = "1";
	paramMap["Virtual_Currency_Amount"] = Analytics::ConvertToString(100);
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("onChargeOnlySuccess",&data, NULL);
}

void Analytics::onChargeSuccess()
{
	if(!_pAnalytics || !isFunctionSupported("onChargeSuccess")) return;

	PluginParam data("123456");
	_pAnalytics->callFuncWithParam("onChargeSuccess",&data, NULL);
}

void Analytics::onChargeFail()
{
	if(!_pAnalytics || !isFunctionSupported("onChargeFail")) return;

	map<string, string> paramMap;
	paramMap["Order_Id"] = "123456";
	paramMap["Fail_Reason"] = "test";
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("onChargeFail",&data, NULL);
}

void Analytics::onPurchase()
{
	if(!_pAnalytics || !isFunctionSupported("onPurchase")) return;

	map<string, string> paramMap;
	paramMap["Item_Id"] = "123456";
	paramMap["Item_Type"] = "test";
	paramMap["Item_Count"] = Analytics::ConvertToString(2);
	paramMap["Vitural_Currency"] = "1";
	paramMap["Currency_Type"] = AgentManager::getInstance()->getChannelId();
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("onPurchase",&data, NULL);
}

void Analytics::onUse()
{
	if(!_pAnalytics || !isFunctionSupported("onUse")) return;

	map<string, string> paramMap;
	paramMap["Item_Id"] = "123456";
	paramMap["Item_Type"] = "test";
	paramMap["Item_Count"] = Analytics::ConvertToString(2);
	paramMap["Use_Reason"] = "1";
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("onUse",&data, NULL);
}

void Analytics::onReward()
{
	if(!_pAnalytics || !isFunctionSupported("onReward")) return;

	map<string, string> paramMap;
	paramMap["Item_Id"] = "123456";
	paramMap["Item_Type"] = "test";
	paramMap["Item_Count"] = Analytics::ConvertToString(2);
	paramMap["Use_Reason"] = "1";
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("onReward",&data, NULL);
}

void Analytics::startLevel()
{
	if(!_pAnalytics || !isFunctionSupported("startLevel")) return;

	map<string, string> paramMap;
	paramMap["Level_Id"] = "123456";
	paramMap["Seq_Num"] = "1";
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("startLevel",&data, NULL);
}

void Analytics::finishLevel()
{
	if(!_pAnalytics || !isFunctionSupported("finishLevel")) return;

	PluginParam data("123456");
	_pAnalytics->callFuncWithParam("finishLevel",&data, NULL);
}

void Analytics::failLevel()
{
	if(!_pAnalytics || !isFunctionSupported("failLevel")) return;

	map<string, string> paramMap;
	paramMap["Level_Id"] = "123456";
	paramMap["Fail_Reason"] = "test";
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("failLevel",&data, NULL);
}

void Analytics::startTask()
{
	if(!_pAnalytics || !isFunctionSupported("startTask")) return;

	map<string, string> paramMap;
	paramMap["Task_Id"] = "123456";
	paramMap["Task_Type"] = Analytics::ConvertToString(GUIDE_LINE);
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("startTask",&data, NULL);
}

void Analytics::finishTask()
{
	if(!_pAnalytics || !isFunctionSupported("finishTask")) return;

	PluginParam data("123456");
	_pAnalytics->callFuncWithParam("finishTask",&data, NULL);
}

void Analytics::failTask()
{
	if(!_pAnalytics || !isFunctionSupported("failTask")) return;

	map<string, string> paramMap;
	paramMap["Task_Id"] = "123456";
	paramMap["Fail_Reason"] = "test";
	PluginParam data(paramMap);
	_pAnalytics->callFuncWithParam("failTask",&data, NULL);
}

bool Analytics::isFunctionSupported(string functionName)
{
	if(!_pAnalytics) return false;
	_pAnalytics->isFunctionSupported(functionName);
}

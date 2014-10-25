#include "IncludeForCpp.h"
#include "Clock.h"
#include <iostream>

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

using namespace std;

static Clock* pInstance = NULL;
MissionPool* _pool = NULL;

Clock* Clock::getInstance(void)
{
    if(pInstance == NULL){
        pInstance = new Clock();
    }
    
	return pInstance;
}


bool Clock::checkMission()
{
	bool bRet = _pool->checkRemind();

	_pool->handleExpire();

	return bRet;
}


Clock::Clock()
{
	_pool = xMissionPool;
	//startTiming();
}


Clock::~Clock(void)
{
}

void Clock::startTiming()
{
	CCLOG("startTiming");
	cocos2d::JniMethodInfo methodInfo;


	  if (!JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity",
			  "showLocalNotification", "(Ljava/lang/String;II)V"))
	  {
	    return;
	  }

	  string str = "abc";

	  jstring stringArg = methodInfo.env->NewStringUTF(str.c_str());
	  methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, stringArg, 1, 1);
	  //return;
	  methodInfo.env->DeleteLocalRef(stringArg);
	  methodInfo.env->DeleteLocalRef(methodInfo.classID);
}

//void Clock::startTiming()
//{
//	return;
//
//    JniMethodInfo methodInfo;
//    jobject jobj;
//
//    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,
//    		"org/cocos2dx/cpp/AppActivity", "getActivity", "()Ljava/lang/Object;");
//
//    if (isHave)
//    {
//        jobj = methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
//
//        isHave = JniHelper::getMethodInfo(methodInfo,
//        		"org/cocos2dx/cpp/AppActivity", "startTiming", "()V");
//
//    	if(isHave)
//    	{
//    		methodInfo.env->CallVoidMethod(jobj, methodInfo.methodID);
//    	}
//    }
//}

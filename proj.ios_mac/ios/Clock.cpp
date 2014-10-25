#include "IncludeForCpp.h"
#include "Clock.h"
#include <thread>           //C++ 11 的多线程
#include <iostream>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h> 
#include "platform/android/jni/JniHelper.h" 
#include <android/log.h> 
#endif 

static Clock* pInstance = NULL;

void timing(Clock *clock);

Clock* Clock::getInstance(void)
{
    if(pInstance == NULL){
        pInstance = new Clock();
    }
    
	return pInstance;
}


bool Clock::checkMission()
{
	CCLOG("ok for ios");
	_pool->checkRemind();
	_pool->handleExpire();
    
    return true;
}


Clock::Clock()
{
    _pool = xMissionPool;
    //startTiming();
}


Clock::~Clock()
{
    
}


void Clock::startTiming()
{
    //创建单独的计时线程
    std::thread t(timing, this);
    t.detach();
}


void timing(Clock *clock)
{
	do
	{
		//在这里写入新线程将要执行的代码
        std::this_thread::sleep_for(chrono::seconds(10));

        clock->checkMission();
	} while (true);
}





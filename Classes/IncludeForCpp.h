//
//  IncludeForCpp.h
//  Begins
//
//  Created by luoxp on 14-7-22.
//
//  禁止在头文件中include这个文件, 这个文件仅仅方便在cpp中include

#pragma once

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#endif

//#include "Clock.h"
//#include "Tool.h"
#include "Database.h"
//#include "MissionPool.h"
//#include "Mission.h"
//#include "Log.h"
//#include "User.h"
//#include "GestureLayer.h"
//#include "SceneManager.h"
//#include "XmlData.h"
//#include "Dialog.h"
//#include "MTNotificationQueue.h"

//#include "TodayScene.h"
//#include "NewScene.h"
//#include "DetailScene.h"
//#include "FrequencyScene.h"


using namespace cocos2d;
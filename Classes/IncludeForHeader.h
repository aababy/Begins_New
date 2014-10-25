//
//  IncludeForHeader.h
//  Begins
//
//  Created by luoxp on 14-7-22.
//
//

#pragma once

#include <string>
#include <vector>
#include "cocos2d.h"
#include "ui/UIWidget.h"                                               //cocos studio ui

//暂时禁止使用新的 using namespace
using std::string;
using std::vector;
using cocos2d::Ref;
using cocos2d::Node;
using cocos2d::Layer;
using cocos2d::Scene;
using cocos2d::Director;
using cocos2d::Point;
using cocos2d::Label;

//////////////////////////////////////////////////  前置声明

namespace cocos2d {
namespace ui {
    class Button;
    class ImageView;
    class Text;
    class TextField;
    class ScrollView;
    class Layout;
    class LoadingBar;
	class ListView;
    class CheckBox;
    class ListView;
}
    
namespace extension {
    class EditBox;
    class EditBoxDelegate;
}
}

namespace game_event {
    class event_dispatch;
}

enum class TouchEventType;

using namespace cocos2d;
using namespace ui;
using extension::EditBox;
using extension::EditBoxDelegate;

////////////////////////////////////////////////////////////////////////// 全局
#define	IN_WINDOWS              0

// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_FILE             "sms_echo.ogg"
#define MUSIC_FILE              "background.mp3"
#define TEST                    0
#else
#define EFFECT_FILE             "effect1.wav"
#define MUSIC_FILE              "background.mp3"
#define TEST                    1
#endif // CC_PLATFORM_ANDROID

////////////////////////////////////////////////////////////////////////// 事件
#define	REMIND_MSG				"REMIND_MSG"
#define EXPIRE_MSG              "EXPIRE_MSG"

////////////////////////////////////////////////////////////////////////// 函数
#define ALI_LEFT(node)			(node)->getContentSize().width/2
#define ALI_UP(node)			(node)->getContentSize().height/2
#define ALI_CEN(width)			(width/2)
#define ADD(p)					(addChild(p))

////////////////////////////////////////////////////////////////////////// 尺寸
#define FONTNAME				"Arial"
#define FONTSIZE				(40)
#define ROW_H					(80)

////////////////////////////////////////////////////////////////////////// 颜色
#define COLOR_SL_GARY			ccc4(50, 50, 50, 255)
#define COLOR_SL_NORMAL			ccc3(50, 50, 50)
#define COLOR_SL_FOCUS			ccc3(227, 108, 9)


#define COLOR_DA_CANCEL			ccc3(84, 141, 212)
#define COLOR_DA_OK				ccc3(250, 192, 143)
#define COLOR_DA_BG				ccc3(0, 0, 0)

////////////////////////////////////////////////////////////////////////// 枚举
enum SceneTag
{
    SCENE_NONE                  = 0,
	SCENE_TODAY,
	SCENE_NEW,
	SCENE_DETAIL,
	SCENE_FREQUENCY
};

enum DialogTag
{
    DIALOG_INVALID              = 0,
    DIALOG_LEFT,
	DIALOG_RIGHT,
};

enum MissionType
{
    MISSION_NORMAL                  = 0,
	MISSION_DAILY,
};

enum class DialogEvent
{
    YES                  = 0,
	NO,
};

struct SceneData {
    SceneTag aTag;
    int iData;
    void* pData;
};

struct Time
{
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int year;
    
	string str;
};



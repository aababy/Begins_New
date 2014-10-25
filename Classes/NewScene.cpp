#include "IncludeForCpp.h"
#include "NewScene.h"

enum UITag {
    MISSION_NAME = 9,
    CHECK_NORMAL = 10,
    CHECK_DAILY = 14,
    REMIND_TIME = 16,
    SCORE = 18,
    CLOSE_TIME = 20,
};


Scene* NewScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = NewScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    GestureLayer *gesture = GestureLayer::create(nullptr, CC_CALLBACK_1(NewScene::back, layer));
    scene->addChild(gesture);
    
    // return the scene
    return scene;
}

bool NewScene::init()
{
    if (CCLayer::init())
    {
        _uiLayer = Layer::create();
        addChild(_uiLayer);
        
        _widget = dynamic_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Scenes/NewScene.ExportJson"));
        _uiLayer->addChild(_widget);
        
        auto screenSize = CCDirector::getInstance()->getWinSize();
        auto rootSize = _widget->getSize();
        _uiLayer->setPosition(Point((screenSize.width - rootSize.width) / 2,
                                    (screenSize.height - rootSize.height) / 2));
        
        missionNameTxt = static_cast<TextField*>(_widget->getChildByTag(MISSION_NAME));
        remindTimeTxt = static_cast<TextField*>(_widget->getChildByTag(REMIND_TIME));
        closeTimeTxt = static_cast<TextField*>(_widget->getChildByTag(CLOSE_TIME));
        scoreTxt = static_cast<TextField*>(_widget->getChildByTag(SCORE));

        noraml = static_cast<CheckBox*>(_widget->getChildByTag(CHECK_NORMAL));
        noraml->setSelectedState(true);
        daily = static_cast<CheckBox*>(_widget->getChildByTag(CHECK_DAILY));
        
        return true;
    }
    return false;
}

void NewScene::back(void*)
{
    if (missionNameTxt->getStringValue().length() == 0)
    {
        xSM->back();
    }
    else
    {
        xDialog->showYesNo(xStr("create"), CC_CALLBACK_2(NewScene::onDialog, this));
    }
}

void NewScene::onDialog(int id, DialogTag tag)
{
    if (tag == DIALOG_LEFT) {
        Clock *clock = xClock;
        
        Time ctime = getCurrentTime();
        Time rtime = str2MTime(remindTimeTxt->getStringValue());
        Time stime = str2MTime(closeTimeTxt->getStringValue());
        
        Mission *pMission = new Mission();
        pMission->eType = getType();
        
        //插入普通任务
        bool bFreq[7];
        for (int i = 0; i < 7; i++) {
            if (pMission->eType == MISSION_NORMAL) {
                bFreq[i] = false;
            }
            else
            {
                bFreq[i] = true;
            }
        }
        
        xDatabase->insertMission(pMission->eType, missionNameTxt->getStringValue().c_str(), ctime, rtime, stime, scoreTxt->getStringValue().c_str(), (char*)bFreq, missionNameTxt->getStringValue().length());
        
        xSM->back();
    } else {
        //取消
    }
}

MissionType NewScene::getType()
{
    if (noraml->getSelectedState()) {
        return MISSION_NORMAL;
    } else if(daily->getSelectedState()){
        return MISSION_DAILY;
    }
    
	return MISSION_NORMAL;
}

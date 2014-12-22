#include "IncludeForCpp.h"
#include "DetailScene.h"


enum UITag {
    OK = 33,
    FREQUENCY = 34,
    CANCEL = 186,
    MISSION_DETAIL = 111,
    MISSION_NAME = 120,
    UNFINISHED = 187,
    DELAY = 188,
};


Scene* DetailScene::createScene(int iTodayIdx)
{
    xMissionPool->_iTodayIdx = iTodayIdx;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = DetailScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    GestureLayer *gesture = GestureLayer::create(nullptr, CC_CALLBACK_1(DetailScene::back, layer));
    scene->addChild(gesture);
    
    // return the scene
    return scene;
}

bool DetailScene::init()
{
    if (CCLayer::init())
    {
        _widget = initRoot("R/DetailScene.json", this);

        btnOK = initButton(OK, _widget, CC_CALLBACK_2(DetailScene::onButton, this));
        btnCancel = initButton(CANCEL, _widget, CC_CALLBACK_2(DetailScene::onButton, this));
        btnFrequency = initButton(FREQUENCY, _widget, CC_CALLBACK_2(DetailScene::onButton, this));
        initButton(UNFINISHED, _widget, CC_CALLBACK_2(DetailScene::onButton, this));
        initButton(DELAY, _widget, CC_CALLBACK_2(DetailScene::onButton, this));
        txtMissionDetail = (TextField*)Helper::seekWidgetByTag(_widget, MISSION_DETAIL);
        txtMissionName = (Text*)Helper::seekWidgetByTag(_widget, MISSION_NAME);

        Mission *mission = xMissionPool->_vMissions.at(xMissionPool->_iTodayIdx);
        txtMissionName->setString(mission->sName);
        
        return true;
    }
    return false;
}

void DetailScene::onButton(Ref *pSender, Widget::TouchEventType type)
{
    if(type != Widget::TouchEventType::ENDED)
    {
        return;
    }
    
    Widget *widget = (Widget*)pSender;
    int iTag = widget->getTag();
    
    switch (iTag) {
        case OK:
        {
            xMissionPool->endMission(xMissionPool->_iTodayIdx, BY_MANUAL);
        }
            break;
        case CANCEL:
        {
            Mission *mission = xMissionPool->_vMissions.at(xMissionPool->_iTodayIdx);
            xMissionPool->removeMission(mission);
        }
            break;
        case FREQUENCY:
        {
            xSM->forward(SCENE_FREQUENCY);
        }
            break;
        case DELAY:
        {
            xMissionPool->delay(xMissionPool->_iTodayIdx);
        }
            break;
        case UNFINISHED:
        {
            xMissionPool->endMission(xMissionPool->_iTodayIdx, BY_FORCE);
        }
            break;
        default:
            break;
    }
    
}

void DetailScene::back(void*)
{
    xSM->back();
}

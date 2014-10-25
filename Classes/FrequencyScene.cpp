#include "IncludeForCpp.h"
#include "FrequencyScene.h"

enum UITag {
    MONDAY = 30,
};


Scene* FrequencyScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = FrequencyScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    GestureLayer *gesture = GestureLayer::create(nullptr, CC_CALLBACK_1(FrequencyScene::back, layer));
    scene->addChild(gesture);
    
    // return the scene
    return scene;
}

bool FrequencyScene::init()
{
    if (CCLayer::init())
    {
        _widget = initRoot("R/FrequencyScene.json", this);

        Mission *mission = xMissionPool->_vMissions.at(xMissionPool->_iTodayIdx);
        
        for (int i = 0; i < 7; i++) {
            day[i] = (CheckBox*)Helper::seekWidgetByTag(_widget, MONDAY + i);

            if (mission->bFrequency[i]) {
                day[i]->setSelectedState(true);
            }
        }
        
        return true;
    }
    return false;
}

void FrequencyScene::back(void*)
{
    updateFrequency();
    xSM->back();
}

void FrequencyScene::updateFrequency()
{
    bool bFreq[7];
    for (int i = 0; i < 7; i++) {
        if (day[i]->getSelectedState()) {
            bFreq[i] = true;
        }
        else
        {
            bFreq[i] = false;
        }
    }
    
    Mission *mission = xMissionPool->_vMissions.at(xMissionPool->_iTodayIdx);
    
    xDatabase->updateBlobByID((char*)bFreq, mission->iMissionID);
}

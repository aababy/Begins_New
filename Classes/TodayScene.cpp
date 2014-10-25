#include "IncludeForCpp.h"
#include "TodayScene.h"


enum UITag {
    kScore = 3,
    kList,
    kMax,
};


Scene* TodayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TodayScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    GestureLayer *gesture = GestureLayer::create(CC_CALLBACK_1(TodayScene::forwardToNewScene, layer), nullptr);
    scene->addChild(gesture);

    // return the scene
    return scene;
}

bool TodayScene::init()
{
    if (CCLayer::init())
    {
        _widget = initRoot("Scenes/TodayScene.ExportJson", this);
        
        Text* score = (Text*)Helper::seekWidgetByTag(_widget, kScore);
        
        xMissionPool->getMission();
        score->setString(itostr(xMissionPool->getScore()));
        
        //列表
        listView = (ListView*)Helper::seekWidgetByTag(_widget, kList);
        listView->addEventListenerListView(this, listvieweventselector(TodayScene::selectedItemEvent));
        
        updateList(NULL);
        
        CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TodayScene::updateList), REMIND_MSG, NULL);
        CCNotificationCenter::getInstance()->addObserver(this, callfuncO_selector(TodayScene::updateList), EXPIRE_MSG, NULL);
        
        return true;
    }
    return false;
}

TodayScene::~TodayScene()
{
    CCNotificationCenter::getInstance()->removeAllObservers(this);
}

void TodayScene::updateList(Ref *pSender)
{
    listView->removeAllItems();
    
    // add default item
    for (int i = 0; i < xMissionPool->_vMissions.size(); ++i)
    {
        listView->pushBackDefaultItem();
    }
    
    Vector<Widget*> items = listView->getItems();
    
    for (int i = 0; i < items.size(); i++) {
        Layout * bg = (Layout*)items.at(i);
//        bg->setBackGroundColorType(LAYOUT_COLOR_SOLID);
//        
//        if (i % 2 == 0) {
//            bg->setBackGroundColor(Color3B(39, 10, 34));
//        } else {
//            bg->setBackGroundColor(Color3B(39, 40, 10));
//        }
     
        Text * labName = (Text*)Helper::seekWidgetByTag(bg, 2);
        Text * labTime = (Text*)Helper::seekWidgetByTag(bg, 3);
        
        Mission *mission = xMissionPool->_vMissions.at(i);
        labName->setText(mission->sName);
        labTime->setText(getShowTime(mission->_scTime));
    }
}

void TodayScene::selectedItemEvent(Ref *pSender, ListViewEventType type)
{
    switch (type)
    {
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_START:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child start index = %ld", listView->getCurSelectedIndex());
            break;
        }
        case cocos2d::ui::LISTVIEW_ONSELECTEDITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            
            xSM->forward(SCENE_DETAIL, listView->getCurSelectedIndex(), nullptr);
            break;
        }
        default:
            break;
    }
}

void TodayScene::forwardToNewScene(void *)
{
    xSM->forward(SCENE_NEW);
}

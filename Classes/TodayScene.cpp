#include "IncludeForCpp.h"
#include "TodayScene.h"


enum UITag {
    kScore = 3,
    kList,
    kStart = 138,
    kCheckAll = 189,
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
        _widget = initRoot("R/TodayScene.json", this);
        
        Text* score = (Text*)Helper::seekWidgetByTag(_widget, kScore);
        
        xMissionPool->getMission();
        score->setString(itostr(xMissionPool->getScore()));

        initButton(kStart, _widget, CC_CALLBACK_2(TodayScene::onButton, this));
        initButton(kCheckAll, _widget, CC_CALLBACK_2(TodayScene::onButton, this));
        
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

    Layout *layout = initRootForCell("R/TodayScene.json", this);

    // add default item
    for (int i = 0; i < xMissionPool->_vMissions.size(); ++i)
    {
        Layout *cell = (Layout*)layout->clone();

        Text * labName = (Text*)Helper::seekWidgetByTag(cell, 2);
        Text * labTime = (Text*)Helper::seekWidgetByTag(cell, 3);

        Mission *mission = xMissionPool->_vMissions.at(i);
        labName->setString(mission->sName);
        labTime->setString(getShowTime(mission->_scTime));

        listView->pushBackCustomItem(cell);
    }
}

void TodayScene::onButton(Ref *pSender, Widget::TouchEventType type)
{
    if(type != Widget::TouchEventType::ENDED) return;
    
    int iTag = ((Widget*)pSender)->getTag();
    
    xClock->startTiming();
    
    switch (iTag) {
        case kStart:
        {
        }
            break;
        case kCheckAll:
        {
            xMissionPool->checkRemind();
            xMissionPool->handleExpire();
        }
            break;
        default:
            break;
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

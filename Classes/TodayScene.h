#pragma once

#include "IncludeForHeader.h"

class TodayScene : public Layer
{
public:
    static Scene* createScene();
    ~TodayScene();
    bool init();
    CREATE_FUNC(TodayScene);
    
    void forwardToNewScene(void *);
    
protected:
    void updateList(Ref *pSender);
    void selectedItemEvent(Ref *pSender, ListViewEventType type);
    // a selector callback
    //void menuCloseCallback(Ref* pSender, TouchEventType type);
    void onButton(Ref *pSender, Widget::TouchEventType type);
    
protected:
    Layout* _widget;
    ListView* listView;
    Text* _score;
};
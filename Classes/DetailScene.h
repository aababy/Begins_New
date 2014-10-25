#pragma once

#include "IncludeForHeader.h"


class DetailScene : public Layer
{
public:
    static Scene* createScene(int iTodayIdx);
    bool init();
    CREATE_FUNC(DetailScene);
    
    void onDialog(int id, DialogTag tag);
    void onButton(Ref *pSender, Widget::TouchEventType type);
    void back(void*);

    
protected:
    Layer*      _uiLayer;
    Layout*     _widget;
    
    Button*     btnOK;
    Button*     btnCancel;
    Button*     btnFrequency;

    TextField*  txtMissionDetail;
    Text*       txtMissionName;
};

#pragma once

#include "IncludeForHeader.h"

class NewScene : public Layer
{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(NewScene);
    
    void back(void*);
    void onDialog(int id, DialogTag tag);
       
protected:
    MissionType getType();
    
    Layer*      _uiLayer;
    Layout*     _widget;
    TextField*  missionNameTxt;
    TextField*  remindTimeTxt;
    TextField*  closeTimeTxt;
    TextField*  scoreTxt;
    
    CheckBox*   daily;
    CheckBox*   noraml;
};
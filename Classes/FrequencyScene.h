#pragma once

#include "IncludeForHeader.h"

class FrequencyScene : public Layer
{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(FrequencyScene);
    void back(void*);
    void updateFrequency();
        
protected:
    Layer*      _uiLayer;
    Layout*     _widget;
    
    CheckBox*   day[7];
};

/*

USING_NS_CC;
USING_NS_CC_EXT;

using namespace std;

#define  MOVE_DIS			(100)

class Frequency : public CCLayer
{
public:
	Frequency(void);
	~Frequency(void);

	CREATE_FUNC(Frequency);
	virtual bool init();
	static CCScene* scene();

	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	//void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void registerWithTouchDispatcher();
	void touchDownAction(Ref *senderz, CCControlEvent controlEvent);
	CCEditBox*  createEditBox(const char *string, Point point);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

	virtual void editBoxReturn(CCEditBox* editBox);
	virtual void editBoxEditingDidBegin(CCEditBox* editBox);
	virtual void editBoxEditingDidEnd(CCEditBox* editBox);
	virtual void editBoxTextChanged(CCEditBox* editBox, const string& text);
	void touchEvent(Ref *pSender, TouchEventType type);   
	void onRemind(Ref* obj);
	void layout();

	Size  _winsize;
	Point obTouchBegan;
	Dialog *dialog;

	MissionPool * _pool;

	UICheckBox *ch[7];

	SelectLabel *_pobLabel[10];
	int _iLabelIdx;

	Shortcut *_s;
	MTimer *obTimer;
	UILayer *_layer;
};

*/
//
//  CCDialog.h
//  SingleEye
//
//  Created by gwsoft on 1/13/14.
//
//

#ifndef __SingleEye__CCDialog__
#define __SingleEye__CCDialog__

#include "IncludeForHeader.h"


#define xDialog                 (Dialog::getInstance())

#define DIALOG_YES              (xStr("ok"))
#define DIALOG_NO               (xStr("cancel"))

#define kDialogHandlerPriority  (kCCMenuHandlerPriority - 1)
#define kDialogZOrder           (128)


typedef std::function<void(int, DialogTag)>  ccDialogCallback;

//类型分为 Yes, YesNo, MidNo, LeftRightNo
class Dialog : public Layer
{
public:
    static Dialog * getInstance();

    //不要在create, onEnter, init 内调用这个函数.
    void show(const char* txt);
    void showYes(const char* txt, const ccDialogCallback& onButton);
    void showYesNo(const char* txt, const ccDialogCallback& onButton);
        
    void show(const char* txt, const char* leftImageName, const char *rightImageName, const ccDialogCallback& onButton);
    void show(const char* txt, const char* midImageName, const ccDialogCallback& onButton);
    void onButton(Ref *pSender, Widget::TouchEventType type);
    
    void setDialogID(int ID);
    
private:
    Dialog();
    virtual bool init();
    
    // 重写触摸函数，永远返回 true ，屏蔽其它层，达到 “模态” 效果
    bool onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
   
    ccDialogCallback    m_onDialog;
    int                 m_id;
    
    static void destroy();
    static void setEnabled(bool value);
    DialogTag getCallbackTag(int iTag);

    Button*     m_pLeft;
    Button*     m_pRight;
    Label*      m_pTxt;
    
    Point     m_pLeftBtnOldPoint;
    Layout*     m_pRootLayer;
};




#endif /* defined(__SingleEye__CCDialog__) */

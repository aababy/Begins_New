//
//  Dialog.cpp
//  SingleEye
//
//  Created by gwsoft on 1/13/14.
//
//
#include "IncludeForCpp.h"
#include "Dialog.h"


enum UITag
{
    LEFT = 26,
    RIGHT = 28,
    TEXT = 29,
};


//static Dialog* instance = NULL;

Dialog * Dialog::getInstance()
{
    static Dialog instance;    
    return &instance;
}

Dialog::Dialog()
{
    m_id = 0;
    init();
}

bool Dialog::init()
{
    Layer::init();

    m_pRootLayer = initRoot("R/Dialog.json", this);

    m_pLeft = initButton(LEFT, m_pRootLayer, CC_CALLBACK_2(Dialog::onButton, this));
    m_pRight = initButton(RIGHT, m_pRootLayer, CC_CALLBACK_2(Dialog::onButton, this));
    
    m_pTxt = (Label*)Helper::seekWidgetByTag(m_pRootLayer, TEXT);

    m_pLeftBtnOldPoint = m_pLeft->getPosition();
    
    auto screenSize = Director::getInstance()->getWinSize();
    auto rootSize = m_pRootLayer->getSize();
    setPosition(Point((screenSize.width - rootSize.width) / 2,
                      (screenSize.height - rootSize.height) / 2));
    
    return true;
    
}

void Dialog::show(const char* txt)
{
    show(txt, DIALOG_YES, NULL, NULL);
}


void Dialog::showYes(const char* txt, const ccDialogCallback& onButton)
{
    show(txt, DIALOG_YES, onButton);
}

void Dialog::showYesNo(const char* txt, const ccDialogCallback& onButton)
{
    show(txt, DIALOG_YES, DIALOG_NO, onButton);
}

void Dialog::show(const char* txt, const char* midImageName, const ccDialogCallback& onButton)
{
    if (getParent() != NULL) {
        return;
    }
    
    show(txt, midImageName, NULL, onButton);
    
    m_pLeft->setPosition(ccp(0, m_pLeftBtnOldPoint.y));
    m_pRight->setEnabled(false);
}

void Dialog::show(const char* txt, const char* leftImageName, const char *rightImageName, const ccDialogCallback& onButton)
{
    if (getParent() != NULL) {
        return;
    }
    
    m_pLeft->setPosition(m_pLeftBtnOldPoint);
    m_pRight->setEnabled(true);
    
    m_pLeft->setTitleText(leftImageName);
    m_pRight->setTitleText(rightImageName);

    m_pTxt->setString(txt);
    
    m_onDialog = onButton;
    
    if (getParent() == NULL) {
        Scene *pRunScene = Director::getInstance()->getRunningScene();
        
        if (pRunScene) {
            pRunScene->addChild(this, kDialogZOrder);
        }
    }
    
    
    setDialogID(0);
}

void Dialog::onButton(Ref *pSender, Widget::TouchEventType type)
{
    if(type != Widget::TouchEventType::ENDED)
    {
        return;
    }
    
    Widget *widget = (Widget*)pSender;
    int iTag = widget->getTag();
    
    Scene *pRunScene = Director::getInstance()->getRunningScene();
    if (m_onDialog) {
        pRunScene->removeChild(this);
        m_onDialog(m_id, getCallbackTag(iTag));
    }
    else
    {
        pRunScene->removeChild(this);
    }
}

DialogTag Dialog::getCallbackTag(int iTag)
{
    switch (iTag) {
        case LEFT:
            return DIALOG_LEFT;
        case RIGHT:
            return DIALOG_RIGHT;
        default:
            return DIALOG_INVALID;
    }
}

bool Dialog::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void Dialog::setEnabled(bool value)
{
    Dialog *dialog = Dialog::getInstance();
    Scene *pRunScene = Director::getInstance()->getRunningScene();
    
    if (value) {
        pRunScene->addChild(dialog, kDialogZOrder);
    }
    else
    {
        pRunScene->removeChild(dialog);
    }
}

void Dialog::setDialogID(int id)
{
    m_id = id;
}

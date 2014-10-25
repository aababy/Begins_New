//
//  GestureLayer.cpp
//  SingleEye
//
//  Created by luoxp on 3/13/14.
//
//
#include "IncludeForCpp.h"
#include "GestureLayer.h"

#define MOVE_DIS                    (100)


GestureLayer* GestureLayer::create(const ccGestureCallback& fromRight, const ccGestureCallback& fromLeft)
{
    GestureLayer *pRet = new GestureLayer(fromRight, fromLeft);
    if (pRet)
    {
        pRet->autorelease();             
        return pRet;
    }
    else
    {
        delete pRet;
        return NULL;
    }
}


GestureLayer::GestureLayer(const ccGestureCallback& fromRight, const ccGestureCallback& fromLeft)
{
    init(fromRight, fromLeft);
}

bool GestureLayer::init(const ccGestureCallback& fromRight, const ccGestureCallback& fromLeft)
{
    if (CCLayerColor::init()) {
        auto listener = EventListenerTouchOneByOne::create();

        listener->onTouchBegan = CC_CALLBACK_2(GestureLayer::onTouchBegan, this);
        listener->onTouchEnded = CC_CALLBACK_2(GestureLayer::onTouchEnded, this);
        
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        setFromLeft(fromLeft);
        setFromRight(fromRight);
    }
    
    return true;
}

void GestureLayer::setFromRight(const ccGestureCallback& fromRight)
{
    onMoveToLeft = fromRight;
}

void GestureLayer::setFromLeft(const ccGestureCallback& fromLeft)
{
    onMoveToRight = fromLeft;
}

bool GestureLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    bool bRet = true;
    beganPoint = pTouch->getLocation();
   
    return true;
}

void GestureLayer::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    Point endedPoint = pTouch->getLocation();
    
	int iDisX = beganPoint.x - endedPoint.x;
	int iDisY = beganPoint.y - endedPoint.y;
    
    //左右滑动 or 上下滑动
	if (abs(iDisX) > abs(iDisY))
	{
        //滑动超过一定距离
		if (abs(iDisX) > MOVE_DIS)
		{
            if (iDisX > 0) {
                if (onMoveToLeft) {
                    onMoveToLeft(nullptr);
                }
            }
            else
            {
                if (onMoveToRight) {
                    onMoveToRight(nullptr);
                }                                
            }
		}
	}
}

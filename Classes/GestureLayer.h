//
//  GestureLayer.h
//  SingleEye
//
//  Created by luoxp on 3/13/14.
//
//

#ifndef __SingleEye__Block__
#define __SingleEye__Block__

#include "IncludeForHeader.h"

typedef std::function<void(void*)>  ccGestureCallback;

class GestureLayer : public cocos2d::CCLayerColor
{        
public:
    static GestureLayer* create(const ccGestureCallback& fromRight, const ccGestureCallback& fromLeft);

    void setFromRight(const ccGestureCallback& fromRight);
    void setFromLeft(const ccGestureCallback& fromLeft);
    
private:    
    GestureLayer(const ccGestureCallback& fromRight, const ccGestureCallback& fromLeft);
    virtual bool init(const ccGestureCallback& fromRight, const ccGestureCallback& fromLeft);
    
    // 重写触摸函数，永远返回 true ，屏蔽其它层，达到 “模态” 效果
    bool onTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void onTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    ccGestureCallback onMoveToRight;
    ccGestureCallback onMoveToLeft;
    
    Point beganPoint;
};


#endif /* defined(__SingleEye__Block__) */

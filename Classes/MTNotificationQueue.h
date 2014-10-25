//
//  MTNotificationQueue.h
//  Demo
//
//  Created by KodeLover on 8/25/13.
//
//

#ifndef __Demo__MTNotificationQueue__
#define __Demo__MTNotificationQueue__

#include "cocos2d.h"
#include <pthread.h>
#include <vector>

using namespace cocos2d;
using namespace std;

#define xMTNotify      (MTNotificationQueue::getInstance())


class MTNotificationQueue : public Ref {
    
public:
    
    static MTNotificationQueue* getInstance();
    
    void postNotifications(float in_fDeltaTime);
    
    void postNotification(const char* in_pArrCharName, Ref* in_pCcObj);
    
    void update(float dt);
    
private:
    
    MTNotificationQueue();
    
    ~MTNotificationQueue();
    
private:
    
	static MTNotificationQueue* sm_pInstance;
    
 	class CGarbo {
    public:
        ~CGarbo() {
            if (MTNotificationQueue::sm_pInstance) {
                delete MTNotificationQueue::sm_pInstance;
            }
            sm_pInstance = NULL;
        }
 	};
    
 	static CGarbo sm_oCGarbo;
    
    typedef struct {
        string m_oStrName;
        Ref* m_pCcObj;
    } NotificationArgs;
    
    vector<NotificationArgs> m_oVecNotifications;
};

#endif /* defined(__Demo__MTNotificationQueue__) */
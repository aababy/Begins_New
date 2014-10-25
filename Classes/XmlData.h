//
//  XmlData.h
//  FishingJoy
//
//  Created by Ringo_D on 12-9-25.
//
//

#ifndef __FishingJoy__XmlData__
#define __FishingJoy__XmlData__

#include "cocos2d.h"

#define xStr(key) XmlData::sharedXmlData()->stringFromKey(key)


USING_NS_CC;
using namespace std;

class XmlData : public Ref
{
public:    
    static XmlData* sharedXmlData();

    const char* stringFromKey(string key);
    int intFromKey(string key);
    bool booleanFromKey(string key);
    Point pointFromKey(string key);
    Rect rectFromKey(string key);
    Size sizeFromKey(string key);
    
    /**
     *	@brief	 内存不足时调用
     */
    void purge();
    
    CC_SYNTHESIZE_READONLY(string, _staticDataPath, XmlDataPath);

protected:
    CCDictionary* _dictionary;
private:
    XmlData();
    ~XmlData();
    bool init();
};
#endif /* defined(__FishingJoy__XmlData__) */

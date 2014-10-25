//
//  tool.cpp
//  Begins
//
//  Created by luoxp on 14-7-22.
//
//
#include "IncludeForCpp.h"
#include "Tool.h"

Button * initButton(int iTag, Widget* root, Widget::ccWidgetTouchCallback callback)
{
    Button *btn = (Button*)Helper::seekWidgetByTag(root, iTag);
    btn->setPressedActionEnabled(true);
    btn->addTouchEventListener(callback);

    return btn;
}

ImageView * initImageView(int iTag, Widget* root)
{
    ImageView *image = (ImageView*)Helper::seekWidgetByTag(root, iTag);
    return image;
}

CheckBox * initCheckBox(int iTag, Widget* root, const CheckBox::ccCheckBoxCallback& callback)
{
    CheckBox * check = (CheckBox*)Helper::seekWidgetByTag(root, iTag);
    check->addEventListener(callback);
    return check;
}

Layout * initRoot(const std::string& filename, Layer *layer)
{
    Node* ui = NodeReader::getInstance()->createNode(filename);
    layer->addChild(ui);
    
    Layout* root = (Layout*)(ui->getChildren().at(0));
    Size size = Director::getInstance()->getVisibleSize();
    root->setContentSize(size);
    
    return root;
}

Layout * initLayout(int iTag, Widget* root, Widget::ccWidgetTouchCallback callback)
{
    Layout *btn = (Layout*)Helper::seekWidgetByTag(root, iTag);
    btn->addTouchEventListener(callback);
    
    return btn;
}

string itostr(int i)
{
	char buf[30];
	sprintf(buf, "%d", i);
    
	return string(buf);
}

string getString(char *sz)
{
	string str;
	if (sz != NULL)
	{
		str = string(sz);
	}
    
	return str;
}

Button* initUIButton(int tag, SEL_TouchEvent selector, Layout* root, Ref* target)
{
    Button* button = static_cast<Button*>(root->getChildByTag(tag));
    
    //CCASSERT(button != nullptr, "error");
    
    button->addTouchEventListener(target, selector);
        
    return button;
}

Time getCurrentTime()
{
	Time mtime;
    
#if 0 //(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	mtime.year = tm->tm_year + 1900;
	mtime.month = tm->tm_mon + 1;
	mtime.day = tm->tm_mday;
	mtime.hour=tm->tm_hour;
	mtime.minute=tm->tm_min;
	mtime.second=tm->tm_sec;
#else
	//struct cc_timeval now;
	//CCTime::gettimeofdayCocos2d(&now, NULL);
	//struct tm *tm;
    
	//const time_t * t = (const time_t *)now.tv_sec;
    
	//tm = localtime(t);
	//mtime.year = tm->tm_year + 1900;
	//mtime.month = tm->tm_mon + 1;
	//mtime.day = tm->tm_mday;
	//mtime.hour=tm->tm_hour;
	//mtime.minute=tm->tm_min;
	//mtime.second=tm->tm_sec;
	//long millSecond= now.tv_sec * 1000 + now.tv_usec / 1000;
    
	unsigned long long timestamp = time(NULL);
	struct tm *ptm = localtime((time_t*)&timestamp);
    
	mtime.year = ptm->tm_year + 1900;
	mtime.month = ptm->tm_mon + 1;
	mtime.day = ptm->tm_mday;
	mtime.hour = ptm->tm_hour;
	mtime.minute = ptm->tm_min;
	mtime.second = ptm->tm_sec;
	//return (now.tv_sec * 1000 + now.tv_usec / 1000);
#endif
    
	//////////////////////////////////////////////////////////////////////////
	char temp[30];
    
	sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d",
            mtime.year, mtime.month, mtime.day, mtime.hour, mtime.minute, mtime.second);
    
	mtime.str = string(temp);
    
	return mtime;
}

Time str2MTime(const string &str)
{
	char buf[5];
    
	Time mtime;
    
	if (str.length() < 8)
	{
		mtime.str = string("null");
		return mtime;
	}
	
	buf[0] = str[0];
	buf[1] = str[1];
	buf[2] = NULL;
	
	mtime.year = 2014;
	mtime.month = atoi(buf);
    
	buf[0] = str[2];
	buf[1] = str[3];
	mtime.day = atoi(buf);
    
	buf[0] = str[4];
	buf[1] = str[5];
	mtime.hour = atoi(buf);
    
	buf[0] = str[6];
	buf[1] = str[7];
	mtime.minute = atoi(buf);
    
	mtime.second = 0;
    
	char temp[30];
    
	sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d",
            mtime.year, mtime.month, mtime.day, mtime.hour, mtime.minute, mtime.second);
    
	mtime.str = string(temp);
    
	return mtime;
}

Time str2MTimeForDB(const string &str)
{
	char buf[5];
    
	Time mtime;
    
	if (str.length() < 8)
	{
		mtime.str = string("null");
		return mtime;
	}
	
	buf[0] = str[5];
	buf[1] = str[6];
	buf[2] = NULL;
	
	mtime.year = 2014;
	mtime.month = atoi(buf);
    
	buf[0] = str[8];
	buf[1] = str[9];
	mtime.day = atoi(buf);
    
	buf[0] = str[11];
	buf[1] = str[12];
	mtime.hour = atoi(buf);
    
	buf[0] = str[14];
	buf[1] = str[15];
	mtime.minute = atoi(buf);
    
	mtime.second = 0;
    
    char temp[30];
    
	sprintf(temp, "%04d-%02d-%02d %02d:%02d:%02d",
            mtime.year, mtime.month, mtime.day, mtime.hour, mtime.minute, mtime.second);
    
	mtime.str = string(temp);
    
	return mtime;
}

string getShowTime(Time &mtime)
{
    char temp[30];
    
	sprintf(temp, "%02d-%02d",
            mtime.month, mtime.day);
    
	return string(temp);
}

int cycleNum(bool bAdd, int iCount, int *idx)
{
    if (bAdd == true)
    {
        if (*idx >= iCount - 1)
        {
            *idx = 0;
        }
        else
        {
            (*idx)++;
        }
    }
    else if (bAdd == false)
    {
        if ((*idx) <= 0)
        {
            (*idx) = iCount - 1;
        }
        else
        {
            (*idx)--;
        }
    }
    
    return (*idx);
}
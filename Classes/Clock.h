#pragma once

#include "IncludeForHeader.h"

#define xClock                  Clock::getInstance()

class MissionPool;

//: public Ref

class Clock
{
public:
    static Clock* getInstance();
	bool checkMission();
private:
    Clock();
	~Clock(void);
    void startTiming();
    
    MissionPool *_pool;
};


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
    void startTiming();
private:
    Clock();
	~Clock(void);

    MissionPool *_pool;
};


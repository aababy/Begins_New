#pragma once

#include "IncludeForHeader.h"

#define xMissionPool        MissionPool::getInstance()

class Mission;
class User;
class Database;


enum ACTION_BY
{
	BY_MANUAL		= 0,
	BY_EXPIRE,
    BY_FORCE,       //强制结束
};

class MissionPool
{
public:
    static MissionPool* getInstance(void);
	MissionPool(void *data);
	~MissionPool(void);
	void clean(vector<Mission*> &vec);
	void getMission();
	bool checkRemind();
	int getScore();
	void handleExpire();
	void updateRemind();
	void endMission(int idx, ACTION_BY eAction);
    void removeMission(Mission *miss);
    void delay(int idx);
	int _iTodayIdx;
	vector <Mission *> _vMissions;		//这个vector通常有很多条
	vector <Mission *> _vReminds;		//这个通常只有几条
	vector <Mission *> _vExpire;		//这个通常只有几条

	User *_user;

	Database *_db;
};


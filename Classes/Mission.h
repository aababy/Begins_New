#pragma once

#include "IncludeForHeader.h"

struct MissionInfo
{
	int			id;			//唯一id号.
	int			type;		//类型, 如普通
	string		name;		//名称
	int			cmonth;		//创建的月份
	int			cday;		//创建的日期
};

/**************************************************************************
对应db里面的数据
table mission
int			id;			//唯一id号.		根据时间产生.
int			type;		//类型, 如普通
string		name;		//名称
int			cmonth		//创建的月份
int			cday		//创建的日期


**************************************************************************/

class Mission
{
public:
	Mission(void);
	Mission(MissionInfo &info);
	~Mission(void);

	int			iMissionID;
	string		sName;
	MissionType	eType;
	int			_iScore;

	Time		_crTime;
	Time		_reTime;
	Time		_scTime;

	//////////////////////////////////////////////////////////////////////////
	int			_iCurPro;
	int			_iTotalPro;
    bool        bFrequency[7];
};


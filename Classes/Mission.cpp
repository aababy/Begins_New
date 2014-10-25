#include "Mission.h"


Mission::Mission(void)
{
	eType = MISSION_NORMAL;
	_iCurPro = 0;
	_iTotalPro = 0;
}


Mission::Mission( MissionInfo &info )
{
	sName = info.name;
	eType = (MissionType)info.type;
}

Mission::~Mission(void)
{
}

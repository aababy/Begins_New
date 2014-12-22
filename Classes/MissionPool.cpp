#include "IncludeForCpp.h"
#include "MissionPool.h"

static MissionPool* pInstance = NULL;

MissionPool* MissionPool::getInstance(void)
{
    if(pInstance == NULL){
        pInstance = new MissionPool(xDatabase);
    }
    
	return pInstance;
}


MissionPool::MissionPool(void *data)
{
	_db = (Database*)data;
	_user = new User();
}


MissionPool::~MissionPool(void)
{
	clean(_vMissions);
	clean(_vReminds);

	delete _user;
}


void MissionPool::clean(vector<Mission*> &vec)
{
	for (vector<Mission*>::iterator it = vec.begin() ; it != vec.end(); ++it)
	{
		delete *it;
	}

	vec.clear();
}


void MissionPool::getMission()
{
	clean(_vMissions);
	_db->GetMissions(&_vMissions);
}


bool MissionPool::checkRemind()
{
	//1. 查询是否有任务需要提醒
	clean(_vReminds);
	_db->getReminds(&_vReminds);

	//2. 如果有, 更新提醒
	if (_vReminds.size() != 0)
	{
		//如果在前台, 提醒对话框,
		updateRemind();
        
        xMTNotify->postNotification(REMIND_MSG, NULL);
        
        return true;
	}
    else
    {
        return false;
    }
}


void MissionPool::updateRemind()
{
	for (unsigned int i = 0; i < _vReminds.size(); i++)
	{
		switch(_vReminds.at(i)->eType)
		{
		case MISSION_NORMAL:
			{
				_db->updateRemindTime(_vReminds.at(i), 0);
			}
			break;
		case MISSION_DAILY:
			{
                //获得今天是星期几
                Mission *mission = _vReminds.at(i);
                int iWeekdayOfNext = _db->getWeekday(mission->_reTime.str);        //0表示星期天, 让0表示星期一, 所以得到的就是明天的值

                //查找离自己最近的一个有提醒的星期
                int iDiffer = 1;
                for (int i = 0; i < 7; i++) {
                    if (mission->bFrequency[iWeekdayOfNext] == true) {
                        break;
                    }
                    else
                    {
                        cycleNum(true, 7, &iWeekdayOfNext);
                        iDiffer++;
                    }
                }
                
                //根据差值, 决定增加的天数
				_db->updateRemindTime(_vReminds.at(i), iDiffer);
			}
			break;
		default:
			break;
		}
	}
}


int MissionPool::getScore()
{
	_user->iScore = _db->getScore();
	return _user->iScore;
}


void MissionPool::handleExpire()
{
	//1. 查询是否有到期任务
	clean(_vExpire);
	_db->getExpire(&_vExpire);

	//2. 如果有, 执行"超时扣分"操作
	if (_vExpire.size() > 0)
	{
		for (unsigned int i = 0; i < _vExpire.size(); i++)
		{
			endMission(i, BY_EXPIRE);
		}
        
        xMTNotify->postNotification(EXPIRE_MSG, NULL);
	}
}


void MissionPool::endMission(int idx, ACTION_BY eAction)
{
	Mission *miss;

	if (eAction == BY_MANUAL)
	{
		miss = _vMissions.at(idx);

		//1. 计算得分
		_db->updateScore(miss->_iScore);
	}
	else if (eAction == BY_EXPIRE)
	{
		miss = _vExpire.at(idx);

		//1. 计算得分
		_db->updateScore(miss->_iScore * -1);
	}
    else if (eAction == BY_FORCE)
    {
        miss = _vMissions.at(idx);
        
        //1. 计算得分
        _db->updateScore(miss->_iScore * -1);
    }
    
	//2. 插入end
	_db->insertMission(miss, "end");

	//3. 更新mission
	if (miss->eType == MISSION_NORMAL)
	{
		_db->deleteMission(miss->iMissionID);
	} 
	else if(miss->eType == MISSION_DAILY)
	{
        //获得今天是星期几
        int iWeekdayOfNext = _db->getWeekday(miss->_scTime.str);        //0表示星期天, 让0表示星期一, 所以得到的就是明天的值
        
        //查找离自己最近的一个有提醒的星期
        int iDiffer = 1;
        for (int i = 0; i < 7; i++) {
            if (miss->bFrequency[iWeekdayOfNext] == true) {
                break;
            }
            else
            {
                cycleNum(true, 7, &iWeekdayOfNext);
                iDiffer++;
            }
        }
        
		_db->updateExpireTime(miss, iDiffer);
	}
}

void MissionPool::removeMission(Mission *miss)
{
    _db->deleteMission(miss->iMissionID);
}

void MissionPool::delay(int idx)
{
    Mission *miss = _vMissions.at(idx);
    
    //1. 更新mission
    if (miss->eType == MISSION_NORMAL)
    {
        _db->updateRemindTime(miss, 1);
        _db->updateExpireTime(miss, 1);
    }
    else if(miss->eType == MISSION_DAILY)
    {
        //获得今天是星期几
        int iWeekdayOfNext = _db->getWeekday(miss->_scTime.str);        //0表示星期天, 让0表示星期一, 所以得到的就是明天的值
        
        //查找离自己最近的一个有提醒的星期
        int iDiffer = 1;
        for (int i = 0; i < 7; i++) {
            if (miss->bFrequency[iWeekdayOfNext] == true) {
                break;
            }
            else
            {
                cycleNum(true, 7, &iWeekdayOfNext);
                iDiffer++;
            }
        }
        
        _db->updateRemindTime(miss, iDiffer);
        _db->updateExpireTime(miss, iDiffer);
    }
}

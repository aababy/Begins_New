#include "Database.h"

#include <stdio.h>
#include <assert.h>
#include "stdlib.h"
#include "sqlite3.h"
#include "IncludeForCpp.h"


// singleton stuff
static Database* pInstance = NULL;
static sqlite3 *_db;


Database* Database::getInstance()
{
    if(pInstance == NULL){
        pInstance = new Database();
    }
    return pInstance;
}

Database::Database()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_rc = sqlite3_open("c://database.db", &_db);
#else
	string path=CCFileUtils::getInstance()->getWritablePath() + "begins.db";
	_rc = sqlite3_open(path.c_str(), &_db);
#endif

	CreateTable();

	_initialized = true;
	_queryP.self = this;
}


Database::~Database(void)
{
	if( _initialized) 
	{
		sqlite3_close(_db);
	}
}


void Database::CreateTable(void)
{
	////////////////////////////////////////////////////////////////////////// create mission
	execute("CREATE TABLE IF NOT EXISTS mission( \
			missionid	INTEGER primary key autoincrement, \
			type		INTEGER, \
			missionname TEXT, \
			crtime		DATETIME, \
			retime		DATETIME, \
			sctime		DATETIME, \
			score		INTEGER, \
			frequency	BLOB \
			)");


	////////////////////////////////////////////////////////////////////////// create end
	execute( "CREATE TABLE IF NOT EXISTS end( \
			 missionid		INTEGER primary key autoincrement, \
			 type			INTEGER, \
			 missionname	TEXT, \
			 crtime			DATETIME, \
			 retime			DATETIME, \
			 sctime			DATETIME, \
			 score			INTEGER \
			 )");


	CreateUser();
}


void Database::insertMission(int type, const char *name, Time &timeCreate, Time &timeRemind, Time &timeScore, const char * score, char * freq, int len)
{
	execute("insert into mission(missionid, type, missionname, crtime, retime, sctime, score) \
			values(null, %d, %Q, datetime(%Q), datetime(%Q), datetime(%Q), %q)",
			type, name, timeCreate.str.c_str(), timeRemind.str.c_str(), timeScore.str.c_str(), score);
    
    //执行完后单独插入 blob
    insertBlob(freq, name, len);
}

void Database::insertBlob(char * freq, const char *name, int len)
{
    sqlite3_stmt* pStmt = NULL;
    const char* sql = "UPDATE mission SET frequency = ? where missionname = ?";
    
    //int nRtn = sqlite3_prepare(_db, "insert into mission values ('mmmm.rar',?);", -1, &pStmt, 0);
    int nRtn = sqlite3_prepare_v2(_db, sql, -1, &pStmt, NULL);
    
    if (nRtn == SQLITE_OK)
    {
        nRtn = sqlite3_bind_blob(pStmt, 1, freq, sizeof(bool)*7, SQLITE_STATIC);
        if (nRtn == SQLITE_OK)
        {
            nRtn = sqlite3_bind_text(pStmt, 2, name, len, SQLITE_STATIC);
            
            nRtn = sqlite3_step(pStmt);
            if (nRtn == SQLITE_DONE)
            {
                CCLOG("insert succ!/n");
            }
        }
        sqlite3_finalize(pStmt);
    }

}


void Database::updateBlobByID(char * freq, int id)
{
    sqlite3_stmt* pStmt = NULL;
    const char* sql = "UPDATE mission SET frequency = ? where missionid = ?";
    
    //int nRtn = sqlite3_prepare(_db, "insert into mission values ('mmmm.rar',?);", -1, &pStmt, 0);
    int nRtn = sqlite3_prepare_v2(_db, sql, -1, &pStmt, NULL);
    
    if (nRtn == SQLITE_OK)
    {
        nRtn = sqlite3_bind_blob(pStmt, 1, freq, sizeof(bool)*7, SQLITE_STATIC);
        if (nRtn == SQLITE_OK)
        {
            nRtn = sqlite3_bind_int(pStmt, 2, id);
            
            nRtn = sqlite3_step(pStmt);
            if (nRtn == SQLITE_DONE)
            {
                CCLOG("insert succ!/n");
            }
        }
        sqlite3_finalize(pStmt);
    }
    
}


void Database::GetMissions(vector<Mission*> *vec)
{
	query(SQL_GetMissions, (void*)vec, 
		"select * from mission order by retime");
}


void Database::getReminds(vector<Mission*> *vec)
{
	query(SQL_GetReminds, vec, 
		"select * from mission where retime < datetime('now', 'localtime');");
}


void Database::CreateUser(void)
{
	////////////////////////////////////////////////////////////////////////// 任务table (5)
	const char *sql = "create table if not exists user( \
					  username TEXT primary key,\
					  score INTEGER \
					  );";


	char *errorMsg = NULL; 
	int ok = sqlite3_exec(_db, sql, NULL, NULL, &errorMsg);

	if(errorMsg != NULL) {
		CCLOG("exec sql %s fail with msg: %s", sql, errorMsg);   
		sqlite3_free(_db);   
	}   


	const char *sql1 = "insert into user values('luoxp', 0)";

	ok = sqlite3_exec(_db, sql1, NULL, NULL, &errorMsg);
}


void Database::setScore(int iScore)
{	
	execute("update user set score = %d WHERE username = 'luoxp'", iScore);
}


int Database::getScore()
{
	int ok = 0;
	int iScore;
	string sql ="select * from user";
	sqlite3_stmt *stmt;
	ok = sqlite3_prepare_v2(_db, sql.c_str(), -1, &stmt, NULL);
	if (ok != SQLITE_OK)
	{
		return 0;
	}

	while(sqlite3_step(stmt) == SQLITE_ROW)  
	{  
		iScore = sqlite3_column_int(stmt, 1); 
	}


	ok |= sqlite3_finalize(stmt);

	if( ok != SQLITE_OK && ok != SQLITE_DONE && ok != SQLITE_ROW)
		printf("Error in localStorage.getItem()\n");

	return iScore;
}


void Database::getExpire(vector<Mission*> *vec)
{
	query(SQL_GetExpire, vec, 
		"select * from mission where sctime < datetime('now', 'localtime');");
}


/*************************************************************************

*************************************************************************/
bool Database::execute(const char* format, ...)
{
	char *errmsg = NULL; 

	//格式化输入sql
	va_list ap;
	va_start(ap, format);
	char *sql = sqlite3_vmprintf(format, ap);
	va_end(ap);

	_rc = sqlite3_exec(_db, sql, NULL, NULL, &errmsg);

	//错误处理
	if(_rc != SQLITE_OK) {   
		CCLOG("ERROR %s fail with msg: %s", sql, errmsg);   
	}

	sqlite3_free(errmsg);
	sqlite3_free(sql);
	return true;
}


bool Database::query( SQL_TAG eTag, void* pData, const char* format, ... )
{
	char *errmsg = NULL; 

	//格式化输入sql
	va_list ap;
	va_start(ap, format);
	char *sql = sqlite3_vmprintf(format, ap);
	va_end(ap);
		
	//执行sql
    _eTag = eTag;
	_queryP.pData = pData;

	_rc = sqlite3_exec(_db, sql, Database::onQuery, &_queryP, &errmsg);

	//错误处理
	if(_rc != SQLITE_OK) {   
		CCLOG("ERROR %s fail with msg: %s", sql, errmsg);   
	}

	sqlite3_free(errmsg);
	sqlite3_free(sql);
	return true;
}



int Database::onQuery(void *pData, int argc, char* value[], char* table_name[])
{
	QUERY_P *queryP = (QUERY_P *)pData;
	Database *self = (Database *)queryP->self;

	switch (self->_eTag)
	{
	case SQL_GetReminds:
	case SQL_GetExpire:
	case SQL_GetMissions:
		{
			Mission	*miss = new Mission();
			
			miss->iMissionID = (int)atoi(value[0]);
			miss->eType = (MissionType)atoi(value[1]);
			miss->sName = string(value[2]);
			miss->_crTime = str2MTimeForDB(getString(value[3]));
			miss->_reTime = str2MTimeForDB(getString(value[4]));
			miss->_scTime = str2MTimeForDB(getString(value[5]));
			miss->_iScore = (int)atoi(value[6]);
            
            if (value[7] != nullptr) {
                memcpy(miss->bFrequency, value[7], sizeof(bool)*7);
            }
           
			vector<Mission*> *vec = (vector<Mission*> *)queryP->pData;
			vec->push_back(miss);
		}
		break;
    case SQL_GetWeekday:
        {
            self->m_iWeekday = (int)atoi(value[0]);
        }
        break;
	default:
		break;
	}

	return 0;
}

void Database::updateScore(int iScore)
{
	execute("update user set score = score + (%d) WHERE username = 'luoxp'", iScore);
}

void Database::insertMission(Mission *miss, const char *szTableName)
{
	execute("insert into %q(missionid, type, missionname, crtime, retime, sctime, score) \
			values(null, %d, %Q, datetime(%Q), datetime(%Q), datetime(%Q), %d)", 
			szTableName, miss->eType, miss->sName.c_str(), miss->_crTime.str.c_str(), miss->_reTime.str.c_str(), 
			miss->_scTime.str.c_str(), miss->_iScore);
}
 
void Database::updateExpireTime(Mission *miss, int iDay)
{
    execute("UPDATE mission SET sctime = datetime(%Q, '+%d day') where missionid = %d",
    miss->_scTime.str.c_str(), iDay, miss->iMissionID);
}

void Database::updateRemindTime(Mission *miss, int iDay)
{
    if (iDay == 0)
    {
        //临时设置为null, 后期可以增加已提醒标识.
        execute("UPDATE mission SET retime = null where missionid = %d",
        miss->iMissionID);
    }
    else
    {
        execute("UPDATE mission SET retime = datetime(%Q, '+%d day') where missionid = %d",
        miss->_reTime.str.c_str(), iDay, miss->iMissionID);
    }
}

void Database::deleteMission(int id)
{
	execute("delete from mission where missionid = %d", id);
}

void Database::printError()
{
    CCLOG("%s", sqlite3_errmsg(_db));
}

int Database::getWeekday(string& date)
{
    char temp[100];
    sprintf(temp, "'%s','localtime')", date.c_str());
    
    string sTemp = "select strftime('%w', ";
    sTemp+=temp;
    
    query(SQL_GetWeekday, NULL, sTemp.c_str(), NULL);
    
	return m_iWeekday;
}



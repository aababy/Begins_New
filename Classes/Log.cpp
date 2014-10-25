#include "IncludeForCpp.h"
#include "Log.h"

using namespace std;
// singleton stuff
static Log* pInstance = NULL;


Log* Log::getInstance(void)
{
    if(pInstance == NULL){
        pInstance = new Log();
    }
    
	return pInstance;
}

bool Log::init()
{
	string fileName = CCFileUtils::getInstance()->getWritablePath()+"log.txt";
	_fp = fopen(fileName.c_str(), "a");
	return true;
}

void Log::alog(const char *str)
{
	fwrite(str, 1, strlen(str), _fp);
	fflush(_fp);
}


Log::Log(void)
{
	init();
}


Log::~Log(void)
{	
	if (_fp)
	{
		fclose(_fp);
	}
}

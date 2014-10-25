#pragma once

#define xLog                (Log::getInstance())

class Log
{
public:
    static Log* getInstance(void);
	virtual bool init();
	void alog(const char *str);
	FILE* _fp;
    
private:
	Log(void);
	~Log(void);
};


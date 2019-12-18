#pragma once
#include <ctime>
class TimeMgr
{
	clock_t start;
	clock_t end;
	double curTime;

public:
	void InitTime();
	void UpdateTime();
	double getTime();
};


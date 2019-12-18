#include "TimeMgr.h"

void TimeMgr::InitTime() {
	curTime = 0;
	start = clock();
}

void TimeMgr::UpdateTime() {
	end = clock();
	curTime += (double)(end - start);

	start = clock();
}

double TimeMgr::getTime() {
	return curTime;
}

#include "Timer.hpp"

Timer::Timer(void) { return; }

Timer::Timer(int diff):
  _diffTime(diff)
{
	   this->_refTimer = _getMilliCount();
     return;
}

Timer::~Timer() { return; }



int 		Timer::_getMilliCount(void) {
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + tb.time * 1000;
	return nCount;
}


bool		Timer::update(void) {
	this->_newTimer = _getMilliCount();
	if (difftime(_newTimer, _refTimer) > _diffTime) {
		this->_refTimer = _getMilliCount();
		this->_newTimer = _getMilliCount();
		return true;
	}
	return false;
}

#include "Timer.hpp"

Timer::Timer(void) { return; }

Timer::Timer(float diff):
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
void        Timer::resetDiff(float diff) {
    this->_diffTime = diff;
}
void        Timer::changeDiff(float newDiff) {
    this->_diffTime /= newDiff;
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

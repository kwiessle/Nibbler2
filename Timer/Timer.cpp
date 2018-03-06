#include "Timer.hpp"

Timer::Timer() {
	this->_refTimer = _getMilliCount();
	this->_newTimer = _getMilliCount();
	this->_diffTime = 1000;
}

Timer::Timer(int diff): _diffTime(diff){
	this->_refTimer = _getMilliCount();
}


Timer::~Timer() {
}



int 		Timer::_getMilliCount() {
	timeb tb;
	ftime(&tb);
	int nCount = tb.millitm + tb.time * 1000;
	return nCount;
}


bool		Timer::update() {
	this->_newTimer = _getMilliCount();
	if (difftime(_newTimer, _refTimer) > _diffTime) {
		this->_refTimer = _getMilliCount();
		this->_newTimer = _getMilliCount();
		return true;
	}
	return false;
}

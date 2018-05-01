#include "Timer.hpp"

Timer::Timer(void) { return; }

Timer::Timer(Timer const &src) { *this = src; }

Timer::Timer(float diff):
  _diffTime(diff)
{
   this->_refTimer = _getMilliCount();
   return;
}

Timer::~Timer() { return; }

Timer   &Timer::operator=(Timer const &rhs) {
    this->_diffTime = rhs._diffTime;
    return *this;
}

int     Timer::_getMilliCount(void) {
    timeb tb;
    ftime(&tb);
    int nCount = tb.millitm + tb.time * 1000;
    return nCount;
}
void    Timer::resetDiff(float diff) {
    this->_diffTime = diff;
}
void    Timer::changeDiff(float newDiff) {
    this->_diffTime -= newDiff;
}

int     Timer::getDiff(void) const {
    return this->_diffTime;
}

bool    Timer::needUpdate(void) {
    int checker = _getMilliCount();
    if (difftime(checker, _refTimer) > _diffTime) {
        return true;
    }
    return false;
}

bool    Timer::update(void) {
    this->_newTimer = _getMilliCount();
    if (difftime(_newTimer, _refTimer) > _diffTime) {
        this->_refTimer = _getMilliCount();
        this->_newTimer = _getMilliCount();
        return true;
    }
    return false;
}

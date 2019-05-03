
#ifndef DelayHelper_h
#define DelayHelper_h

#if defined(ARDUINO) && ARDUINO >= 100

#include "Arduino.h"

#else

#include "WProgram.h"

#endif

class DelayHelper
{
public:
	DelayHelper() {
		m_endMS = 0;
	};

	void startDelay(uint32_t  delayMS) {
		m_endMS = millis()+delayMS;
	}

	bool isDone() {return millis() > m_endMS;}

protected:
	uint32_t		m_endMS;

};

#endif

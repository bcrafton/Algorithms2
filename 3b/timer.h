/**
 * timer.h
 * Brian Crafton and Oliver Scott
 * The timer header
 *
 */
#ifndef TIMER_H_
#define TIMER_H_

#include <time.h>

class Timer
{
private:
	clock_t duration;
	clock_t startTime;
	clock_t stopTime;
public:
	Timer();
	void stop();
	void restart();
	double getDuration() const;
};


#endif /* TIMER_H_ */

/**
 * timer.cpp
 * Brian Crafton and Oliver Scott
 * The timer object for tracking execution time
 *
 */
#include "timer.h"

/*
	constructor for a timer object. takes the time of the object constrcutrion
*/
Timer::Timer()
{
	startTime = clock();
}
/*
	gets the time when the method is called
*/
void Timer::stop()
{
	stopTime = clock();
	duration = stopTime - startTime;
}
/*
	gets the duration between the start and stop field
*/
double Timer::getDuration() const
{
	return ((double)duration)/CLOCKS_PER_SEC;
}

/**
 * resets the start time of the clock
 */
void Timer::restart()
{
	startTime = clock();
}

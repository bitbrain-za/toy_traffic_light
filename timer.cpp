/* Copyright 2018 Philip Barlow
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights 
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
 * copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 */

#include "Arduino.h"
#include "timer.h"

Timer *timerList[MAX_TIMERS];
int freeSlots;

void initTimerModule()
{
	for(int i = 0 ; i < MAX_TIMERS ; i++)
	{
		timerList[i] = NULL;
	}
	freeSlots = MAX_TIMERS;
}

void timerModuleTick(int milliseconds)
{
	for(int i = 0 ; i < MAX_TIMERS ; i++)
	{
		if(NULL != timerList[i])
			timerList[i]->tick(milliseconds);
	}
}

Timer* Timer::create(int period)
{
	if(0 == freeSlots)
	{
		return NULL;
	}

	return new Timer(period);
}

Timer::Timer(int period)
{
	_period = period;
	_running = true;
	_expired = false;
	_count = 0;
	_index = -1;

	for(int i = 0 ; i < MAX_TIMERS ; i++)
	{
		if(NULL == timerList[i])
		{
			timerList[i] = this;
			_index = i;
			freeSlots--;
		}
	}
}

Timer::~Timer()
{
	if(_index >= 0)
	{
		timerList[_index] = NULL;
		freeSlots++;
	}
}

void Timer::tick(int milliseconds)
{
	if(_running && !_expired)
	{
		_count += milliseconds;
		if(_count >= _period)
		{
			_expired = true;
		}
	}
}

void Timer::start()
{
	_running = true;
}

void Timer::stop()
{
	_running = false;
}

void Timer::restart()
{
	stop();
	_count = 0;
	start();
}

void Timer::reset(int period)
{
	stop();
	_period = period;
	_count = 0;
	start();
}

bool Timer::expired()
{
	return _expired;
}
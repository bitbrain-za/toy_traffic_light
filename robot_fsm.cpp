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
#include "config.h"
#include "timer.h"
#include "heartbeat.h"
#include "robot_fsm.h"

/***********************
* --== Properties ==-- *
***********************/

ROBOT_STATES robot::_state;
Timer* robot::_state_timer;
light* robot::_light1;
light* robot::_light2;
Arrow* robot::_arrow;

/********************
* --== Methods ==-- *
*********************/

void robot::init(void)
{
	_state = BOOT0;
	_state_timer = Timer::create(BOOT_TIMING);
	_light1 = light::create(LIGHT1_G, LIGHT1_O, LIGHT1_R);
	_light2 = light::create(LIGHT2_G, LIGHT2_O, LIGHT2_R);
	_arrow = Arrow::create(ARROWG, ARROWO);
}

void robot::run(void)
{
	_arrow->run();
	switch(_state)
	{
		case BOOT0:
		_light1->turnOn(RED);
		_light2->turnOn(RED);
		if(_state_timer->expired())
		{
			_state_timer->reset(BOOT_TIMING);
			_state = BOOT1;
		}
		break;

		case BOOT1:
		_light1->turnOn(ORANGE);
		_light2->turnOn(ORANGE);
		if(_state_timer->expired())
		{
			_state_timer->reset(BOOT_TIMING);
			_state = BOOT2;
		}
		break;

		case BOOT2:
		_light1->turnOn(GREEN);
		_light2->turnOn(GREEN);
		if(_state_timer->expired())
		{
			_state_timer->reset(GO_TIME_BASE + random(GO_TIME_RAND_MAX));
			Heartbeat::normal();
			_state = GO1_STOP2;
		}
		break;

		case GO1_STOP2:
		_light1->go();
		_light2->stop();
		if(_state_timer->expired())
		{
			_state_timer->reset(SLOW_TIME);
			_state = SLOW1_STOP2;
		}
		break;

		case SLOW1_STOP2:
		_light1->slow();
		_light2->stop();
		if(_state_timer->expired())
		{
			_state_timer->reset(GO_TIME_BASE + random(GO_TIME_RAND_MAX));
			_state = STOP1_GO2;
			_arrow->go();
		}
		break;

		case STOP1_GO2:
		_light1->stop();
		_light2->go();
		if(_state_timer->expired())
		{
			_state_timer->reset(SLOW_TIME);
			_state = STOP1_SLOW2;
			_arrow->caution();
		}
		break;

		case STOP1_SLOW2:
		_light1->stop();
		_light2->slow();
		if(_state_timer->expired())
		{
			_state_timer->reset(GO_TIME_BASE + random(GO_TIME_RAND_MAX));
			_state = GO1_STOP2;
			_arrow->stop();
		}
		break;

	}
}
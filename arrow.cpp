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
#include "arrow.h"

Arrow* Arrow::create(int green_pin, int orange_pin)
{
	return new Arrow(green_pin, orange_pin);
}

Arrow::Arrow(int green_pin, int orange_pin)
{
	_flash_timer = Timer::create(FLASH_TIME);
	_flash_timer->stop();

	_green = green_pin;
	_orange = orange_pin;

	pinMode(_green, OUTPUT);
	pinMode(_orange, OUTPUT);

	_state = ARROW_STOP;
	digitalWrite(_green, ARROW_START_STATE);
	digitalWrite(_orange, ARROW_START_STATE);
}

void Arrow::go()
{
	_state = ARROW_GO;
	_flash_timer->restart();
}

void Arrow::caution()
{
	_state = ARROW_CAUTION;
	_flash_timer->stop();
}

void Arrow::stop()
{
	_state = ARROW_STOP;
	_flash_timer->stop();
}

void Arrow::run()
{
	static bool green_is_on = false;

	switch(_state)
	{
		case ARROW_GO:
		digitalWrite(_orange, low);
		if(_flash_timer->expired())
		{
			_flash_timer->restart();
			if(green_is_on)
			{
				digitalWrite(_green, low);
			}
			else
			{
				digitalWrite(_green, high);
			}
			green_is_on = !green_is_on;
		}
		break;

		case ARROW_CAUTION:
		digitalWrite(_green, low);
		digitalWrite(_orange, high);
		break;

		default:
		case ARROW_STOP:
		digitalWrite(_green, low);
		digitalWrite(_orange, low);
		break;

	}
}
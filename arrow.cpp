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


/*! \fn Arrow* Arrow::create(int green_pin, int orange_pin)
    \brief Factory method for the arrow class, initialises
    with green and orange pins.
    Green will flash, orange is constant
    \param green_pin The pin to the Green Arrow
    \param orange_pin The pin to the Orange Arrow
    \retval pointer to the new instance
*/
Arrow* Arrow::create(int green_pin, int orange_pin)
{
	return new Arrow(green_pin, orange_pin);
}

/*! \fn Arrow::Arrow(int green_pin, int orange_pin)
    \brief Arrow class constructor, use the factory method instead
    \param green_pin The pin to the Green Arrow
    \param orange_pin The pin to the Orange Arrow
*/
Arrow::Arrow(int green_pin, int orange_pin)
{
	_flash_timer = Timer::create(FLASH_TIME);
	_flash_timer->stop();

	_green = green_pin;
	_orange = orange_pin;

	/* see http://arduino-info.wikispaces.com/ArduinoPower#4-8 */
	digitalWrite(_green, ARROW_START_STATE);
	digitalWrite(_orange, ARROW_START_STATE);
	pinMode(_green, OUTPUT);
	pinMode(_orange, OUTPUT);

	_state = ARROW_STOP;
}

/*! \fn void Arrow::go()
    \brief Triggers the go state:
    	- Green Arrow flashes
    	- Orange Arrow off
*/
void Arrow::go()
{
	_state = ARROW_GO;
	_flash_timer->restart();
}

/*! \fn void Arrow::caution()
    \brief Triggers the caution state:
    	- Green Arrow off
    	- Orange Arrow on
*/
void Arrow::caution()
{
	_state = ARROW_CAUTION;
	_flash_timer->stop();
}

/*! \fn void Arrow::stop()
    \brief Triggers the stop state:
    	- Green Arrow off
    	- Orange Arrow off
*/
void Arrow::stop()
{
	_state = ARROW_STOP;
	_flash_timer->stop();
}

/*! \fn void Arrow::run()
    \brief FSM for the arrow. Run in the main loop
*/
void Arrow::run()
{
	static bool green_is_on = false;

	switch(_state)
	{
		case ARROW_GO:
		digitalWrite(_orange, RELAY_OPEN);
		if(_flash_timer->expired())
		{
			_flash_timer->restart();
			if(green_is_on)
			{
				digitalWrite(_green, RELAY_OPEN);
			}
			else
			{
				digitalWrite(_green, RELAY_CLOSED);
			}
			green_is_on = !green_is_on;
		}
		break;

		case ARROW_CAUTION:
		digitalWrite(_green, RELAY_OPEN);
		digitalWrite(_orange, RELAY_CLOSED);
		break;

		default:
		case ARROW_STOP:
		digitalWrite(_green, RELAY_OPEN);
		digitalWrite(_orange, RELAY_OPEN);
		break;

	}
}
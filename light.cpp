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
#include "light.h"

light* light::create(int green_pin, int orange_pin, int red_pin)
{
	return new light(green_pin, orange_pin, red_pin);
}

light::light(int green_pin, int orange_pin, int red_pin)
{
	_green = green_pin;
	_orange = orange_pin;
	_red = red_pin;

	digitalWrite(_green, RELAY_OPEN);
	digitalWrite(_orange, RELAY_OPEN);
	digitalWrite(_red, RELAY_OPEN);

	pinMode(_green, OUTPUT);
	pinMode(_orange, OUTPUT);
	pinMode(_red, OUTPUT);
}

void light::turnOn(COLOURS colour)
{
	int pin;
	switch(colour)
	{
		case GREEN:
		pin = _green;
		break;

		case ORANGE:
		pin = _orange;
		break;

		case RED:
		pin = _red;
		break;

		default:
		pin = -1;
		break;
	}
	if(pin != -1)
		digitalWrite(pin, RELAY_CLOSED);
}

void light::turnOff(COLOURS colour)
{
	int pin;
	switch(colour)
	{
		case GREEN:
		pin = _green;
		break;

		case ORANGE:
		pin = _orange;
		break;

		case RED:
		pin = _red;
		break;

		default:
		pin = -1;
		break;
	}
	if(pin != -1)
		digitalWrite(pin, RELAY_OPEN);
}

void light::go(void)
{
	turnOn(GREEN);
	turnOff(ORANGE);
	turnOff(RED);
}

void light::slow(void)
{
	turnOff(GREEN);
	turnOn(ORANGE);
	turnOff(RED);
}

void light::stop(void)
{
	turnOff(GREEN);
	turnOff(ORANGE);
	turnOn(RED);
}

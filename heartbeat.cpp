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

/***********************
* --== Properties ==-- *
***********************/

int Heartbeat::_pin;
SYS_STATE Heartbeat::_state;
Timer* Heartbeat::_pulse_timer;

/********************
* --== Methods ==-- *
*********************/

Heartbeat::init(int pin)
{
	pinMode(pin, OUTPUT);
	_pin = pin;
  _pulse_timer = Timer::create(PULSE_PERIOD);
  boot();
}

void Heartbeat::boot()
{
  _state = err_boot;
  _pulse_timer->reset(250);
}

void Heartbeat::normal()
{
  _state = err_normal;
  _pulse_timer->reset(PULSE_PERIOD);
}

void Heartbeat::error(int errorCode)
{
  _state = errorCode;
  _pulse_timer->reset(PULSE_PERIOD);
}

/*
For boot we just flash
While running the state can be put onto the LED
Pulse codes:
  1 - Normal
  2 - Error
Timing configurable in config.h
*/
void Heartbeat::pump()
{
  static bool LED_is_on = false;
  static int pulses = 0;

  if(err_boot == _state)
  {
    if(_pulse_timer->expired())
    {
      if(LED_is_on)
      {
        digitalWrite(_pin, LOW);
      }
      else
      {
        digitalWrite(_pin, HIGH);
      }

      LED_is_on = !LED_is_on;
      _pulse_timer->restart();
    }
  }
  else
  {
    if(_pulse_timer->expired())
    {
      if(0 == pulses)
      {
        pulses = _state;
        _pulse_timer->reset(PULSE_PERIOD);
      }
      else
      {
        if(LED_is_on)
        {
          digitalWrite(_pin, LOW);
          pulses--;
        }
        else
        {
          digitalWrite(_pin, HIGH);
        }
        LED_is_on = !LED_is_on;
        _pulse_timer->reset(PUMP_PERIOD);
      }
    }
  }
}
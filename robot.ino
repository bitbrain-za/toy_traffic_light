/*
*     ____  __                                             __   ______           _________         __    _       __    __
*    / __ \/ /___ ___  ______ __________  __  ______  ____/ /  /_  __/________ _/ __/ __(_)____   / /   (_)___ _/ /_  / /______
*   / /_/ / / __ `/ / / / __ `/ ___/ __ \/ / / / __ \/ __  /    / / / ___/ __ `/ /_/ /_/ / ___/  / /   / / __ `/ __ \/ __/ ___/
*  / ____/ / /_/ / /_/ / /_/ / /  / /_/ / /_/ / / / / /_/ /    / / / /  / /_/ / __/ __/ / /__   / /___/ / /_/ / / / / /_(__  )
* /_/   /_/\__,_/\__, /\__, /_/   \____/\__,_/_/ /_/\__,_/    /_/ /_/   \__,_/_/ /_/ /_/\___/  /_____/_/\__, /_/ /_/\__/____/
*               /____//____/                                                                           /____/
*	
*	This project provides some simple traffic lights for a three way junction. Intended for play only!
*	Throughout the project the vernacular 'robot' is used in place of the more cumbersome 'traffic light'.
*
* Required Libraries:
* 	- https://playground.arduino.cc/Code/Timer1
*
*	See config.h to modify timing and hardware connections
*
* Copyright 2018 Philip Barlow
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
*
*/

#include <TimerOne.h>
#include "config.h"
#include "timer.h"
#include "heartbeat.h"
#include "robot_fsm.h"

void isr_sys_tick();

void setup() 
{
	/* Psuedo random is fine, no need to use AN */
	randomSeed(0x7062);

	/* HW timer used as base tick for sys timers */
  Timer1.initialize(SYS_TICK * 1000);
  Timer1.attachInterrupt( isr_sys_tick );
	initTimerModule();
	Heartbeat::init(LED_BUILTIN);
	robot::init();
}

void loop() 
{
	Heartbeat::pump();
  robot::run();
}

void isr_sys_tick()
{
	timerModuleTick(SYS_TICK);
}
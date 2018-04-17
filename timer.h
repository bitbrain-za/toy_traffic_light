#ifndef TIMER_H
#define TIMER_H

#define MAX_TIMERS 10

class Timer
{
public:
	static Timer* create(int period);
	void start();
	void stop();
	void reset(int period);
	void restart();
	void tick(int milliseconds);
	bool expired();
	~Timer();

private:
	Timer(int period);
	bool _running;
	bool _expired;
	int _period;
	int _count;	
	int _index;
};

void initTimerModule();
void timerModuleTick(int milliseconds);

#endif

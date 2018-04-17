#ifndef LED_H
#define LED_H

typedef enum
{
	err_boot = 0,
	err_normal = 1,
	err_res = 2,
}SYS_STATE;

class Heartbeat
{
public:
	static init(int pin);
	static void boot();
	static void normal();
	static void error(int errorCode);
	static void pump(void);

private:
	static int _pin;
	static SYS_STATE _state;
	static Timer* _pulse_timer;
};

#endif

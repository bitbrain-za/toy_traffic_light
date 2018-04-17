#ifndef ARROW_H_
#define ARROW_H_

typedef enum
{
	ARROW_GO,
	ARROW_CAUTION,
	ARROW_STOP,
}ARROW_STATE;

class Arrow
{
public:
	static Arrow* create(int green_pin, int orange_pin);
	Arrow(int green_pin, int orange_pin);
	void go(void);
	void caution(void);
	void stop(void);
	void run();

private:
	int _green;
	int _orange;
	Timer* _flash_timer;
	ARROW_STATE _state;
};


#endif
#ifndef ROBOFSM_H_
#define ROBOFSM_H_

#include "light.h"
#include "arrow.h"

typedef enum
{
	BOOT0,
	BOOT1,
	BOOT2,
	GO1_STOP2,
	SLOW1_STOP2,
	STOP1_GO2,
	STOP1_SLOW2,
}ROBOT_STATES;

class robot
{
public:
	static void init(void);
	static void run(void);

private:
	static ROBOT_STATES _state;
	static Timer* _state_timer;

	static light* _light1;
	static light* _light2;

	static Arrow* _arrow;
};


#endif
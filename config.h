#ifndef CONFIG_H_
#define CONFIG_H_

#define SYS_TICK 1 	/* milliseconds */

/* Relay Pins */
#define RELAY_1 2
#define RELAY_2 3
#define RELAY_3 4
#define RELAY_4 5
#define RELAY_5 6
#define RELAY_6 7
#define RELAY_7 8
#define RELAY_8 9

/* Relay to Light signals */
#define LIGHT1_G 	RELAY_1
#define LIGHT1_O 	RELAY_2
#define LIGHT1_R 	RELAY_3
#define LIGHT2_G 	RELAY_6
#define LIGHT2_O 	RELAY_7
#define LIGHT2_R 	RELAY_8

#define ARROWG 		RELAY_4
#define ARROWO 		RELAY_5

/* Robot Timing */
#define GO_TIME_BASE  		5000
#define GO_TIME_RAND_MAX  10000
#define SLOW_TIME					3000
#define FLASH_TIME				500

#define BOOT_TIMING 	1000

#define PULSE_PERIOD 	1000
#define PUMP_PERIOD 	100

#define REVERSE_LOGIC 1

#if REVERSE_LOGIC
#define RELAY_CLOSED 	LOW
#define RELAY_OPEN 		HIGH
#else
#define RELAY_CLOSED 	LOW
#define RELAY_OPEN 		HIGH
#endif

/* During the bootup process should the arrows be lit or not */
#define ARROW_START_STATE RELAY_CLOSED


#endif
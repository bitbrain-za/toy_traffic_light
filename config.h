#ifndef CONFIG_H_
#define CONFIG_H_


#define SYS_TICK 1 	/* milliseconds */

/* Relay Pins */
#define LIGHT1_G 	1	
#define LIGHT1_O 	1
#define LIGHT1_R 	1
#define LIGHT2_G 	1
#define LIGHT2_O 	1
#define LIGHT2_R 	1

#define ARROWG 		1
#define ARROWO 		1

/* Robot Timing */
#define GO_TIME_BASE  		5000
#define GO_TIME_RAND_MAX  10000
#define SLOW_TIME					3000
#define FLASH_TIME				500

#define BOOT_TIMING 	1000

#define PULSE_PERIOD 	1000
#define PUMP_PERIOD 	100

#define REVERSE_LOGIC 0

#if REVERSE_LOGIC
#define high LOW
#define low HIGH
#else
#define high LOW
#define low HIGH
#endif

/* During the bootup process should the arrows be lit or not */
#define ARROW_START_STATE high


#endif
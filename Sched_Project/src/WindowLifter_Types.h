#ifndef WINDOWLIFTER_TYPEDEF                 /* To avoid double inclusion */
#define WINDOWLIFTER_TYPEDEF

/* Defines for buttons and pinch signal pins, 				 */
/* and pressed/active states. Correspondence w/ GPIO number. */
#define UP_BUTTON 			64
#define DOWN_BUTTON 		65
#define PRESSED 			0

#define ANTI_PINCH_BUTTON 	66 
#define ACTIVE_STATE 		0

#define DOWN_LED 			46
#define UP_LED 				47

/* Defines for highest and lowest LED. Correspondence w/ PORTC GPIO number. */
#define LED_LEVEL_MAX 		43 	 
#define LED_LEVEL_MIN 		34

/* Enum to hold machine's current state */
typedef enum { 			
	WAIT_STATE,
	AUTO_UP_STATE,
	AUTO_DOWN_STATE,
	MANUAL_UP_STATE,
	MANUAL_DOWN_STATE,
	ANTI_PINCH_STATE,
	BLOCKED_STATE
}E_WINDOWLIFTER_CURRENTSTATE;

/* enum to hold a value depending on the pressed button*/


/* BYTES */

/* WORDS */


/* LONGS and STRUCTURES */



#endif

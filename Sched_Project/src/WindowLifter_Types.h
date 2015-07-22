#ifndef _WINDOWLIFTER_TYPEDEF_                 /* To avoid double inclusion */
#define _WINDOWLIFTER_TYPEDEF_

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
	/*VALIDATION_STATE,*/
	/*MODE_DECISION_STATE,*/
	AUTO_UP_STATE,
	AUTO_DOWN_STATE,
	MANUAL_UP_STATE,
	MANUAL_DOWN_STATE,
	ANTI_PINCH_STATE,
	BLOCKED_STATE
}E_WINDOWLIFTER_CURRENTSTATE;

/* enum to hold a value depending on the pressed button*/
/*typedef enum {			
	NO_SIGNAL,
	BUTTON_UP_SIGNAL,
	BUTTON_DOWN_SIGNAL,
	ANTI_PINCH_SIGNAL
}E_WINDOWLIFTER_INPUTSIGNAL;*/


/* BYTES */

/* WORDS */


/* LONGS and STRUCTURES */



#endif
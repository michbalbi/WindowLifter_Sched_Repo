#ifndef _WINDOWLIFTER_TYPEDEF_                 /* To avoid double inclusion */
#define _WINDOWLIFTER_TYPEDEF_

/* Defines for buttons and pinch signal pins, 				 */
/* and pressed/active states. Correspondence w/ GPIO number. */
#define UP_BUTTON 		6
#define DOWN_BUTTON 	7
#define PRESSED 		0

#define PINCH_SIGNAL 	66 
#define ACTIVE_STATE 	0

#define DOWN_LED 		46
#define UP_LED 			47

/* Defines for highest and lowest LED. Correspondence w/ PORTC GPIO number. */
#define LED_LEVEL_MAX 	43 	 
#define LED_LEVEL_MIN 	34


/* Está bien aquí? */
typedef enum { 			/* enum to hold movement value */
	DISABLED,
	AUTO_UP,
	AUTO_DOWN,
	MANUAL_UP,
	MANUAL_DOWN,
	PINCH
}E_WINDOWLIFTER_MOVEMENTLIST;

typedef enum {			/* enum to hold a value depending on the pressed button*/
	NONE,
	BUTTON_UP,
	BUTTON_DOWN
}E_WINDOWLIFTER_BUTTONLIST;


/* BYTES */

/* WORDS */


/* LONGS and STRUCTURES */



#endif
/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %WindowLifter_PeriodicTasks.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 10 2015 %
*=============================================================================*/
/* DESCRIPTION : C source file for the implemented timer functions.           */
/*============================================================================*/
/* FUNCTION COMMENT : This file contains the definition for the functions     */
/* that are called at certain time intervals.                                 */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 10/07/2015  |                               | Michele Balbi    */
/* 	First draft of file. Moving the functions from the main.c module.         */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "conti_typedefs.h"
#include "MPC5606B_GPIO_lib.h"
#include "MPC5606B_PIT_lib.h"
#include "WindowLifter_PeriodicTasks.h"
#include "WindowLifter.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */


/* Private functions */
/* ----------------- */

/* Exported functions */
/* ------------------ */
/*****************************************************************
 *  Name                 :	WindowLifter_TimersInit
 *  Description          :	Timer Iinitialization.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Initializes timers, loads time values
 							and enables interrupts for timers.
 ******************************************************************/
 void WindowLifter_TimersInit(void){

	/* Timer init, loading times values, enable Timer INTs */
    TIMER_INIT();
    TIMER_LOAD_VALUE_MS(10,0);
    TIMER_LOAD_VALUE_MS(500,1);
    TIMER_LOAD_VALUE_MS(400,4);
    TIMER_LOAD_VALUE_MS(5000,5);
    TIMER_ENABLE_INT(0);		
    TIMER_ENABLE_INT(1);
    TIMER_ENABLE_INT(4);
    TIMER_ENABLE_INT(5);
 }
 
/*****************************************************************
 *  Name                 :	WindowLifter_Task_10MS
 *  Description          :	Timer Interrupt handler for the 10ms.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Check if input signals are still active
 							after 10ms, to filter glitches.
 							If the signals are valid, set AUTO modes
 							and start timersfor 500ms to check for 
 							MANUAL modes.
 ******************************************************************/
 void WindowLifter_Task_10MS(void){
 	TIMER_STOP(0); /* Disable 10ms automatic recount. */
 	if(INPUT_STATE(DOWN_BUTTON)==PRESSED && re_button_pressed==BUTTON_DOWN &&  rub_led_level>=LED_LEVEL_MIN){
 		re_move = AUTO_DOWN;
		TIMER_STOP(4);
		TIMER_START(4);
 	} 	
 	
 	if(INPUT_STATE(UP_BUTTON)==PRESSED && re_button_pressed==BUTTON_UP && rub_led_level<LED_LEVEL_MAX){
 		re_move = AUTO_UP;
		TIMER_STOP(4);
		TIMER_START(4);
 	}
 	
 	if(INPUT_STATE(PINCH_SIGNAL)==ACTIVE_STATE && (re_move==AUTO_UP || re_move==MANUAL_UP)){
		re_move=PINCH;
	} 
 	
 	TIMER_CLEAR_INT_FLAG(0);
 }
 
 /*****************************************************************
 *  Name                 :	WindowLifter_Task_500MS
 *  Description          :	Timer Interrupt handler for the 500ms.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  If buttons are still pressed after 500ms
 							MANUAL modes are activated.
 ******************************************************************/
 void WindowLifter_Task_500MS(void){
 	TIMER_STOP(1); /* Disable 500ms automatic recount. */
 	if(INPUT_STATE(DOWN_BUTTON)==PRESSED && re_button_pressed==BUTTON_DOWN && rub_led_level>=LED_LEVEL_MIN){
 		re_move = MANUAL_DOWN;
 	} 	
 	
 	if(INPUT_STATE(UP_BUTTON)==PRESSED && re_button_pressed==BUTTON_UP && rub_led_level<LED_LEVEL_MAX){
 		re_move = MANUAL_UP;
 	} 
 	
 	re_button_pressed = NONE;
 	TIMER_CLEAR_INT_FLAG(1);
 }
 
 /*****************************************************************
 *  Name                 :	WindowLifter_Task_400MS
 *  Description          :	Timer Interrupt handler for the 400ms
 							count between LEDs' change of state.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Checks movement state through re_move,
 							if button is pressed (in case of manual
 							modes) and calls routines to turn ON/OFF
 							the next LED. Also calls the routine to
 							end the LED switching, if necessary.
 ******************************************************************/
 void WindowLifter_Task_400MS(void){
 	
 	if(re_move==PINCH){						
		if(rub_led_level>=LED_LEVEL_MIN){  /* Any LEDs still ON?      */
			WindowLifter_TurnOFFLED();	   /* Yes. Turn OFF next LED. */
		}else{							   
			WindowLifter_StopMovement();   /* No. Stop movement and   */
			re_move=PINCH;				   /* start 5s blocking count.*/
			TIMER_STOP(5);
			TIMER_START(5); 			
		}
 	}
 
 	/* Decisions for UP movements. */
 	if((INPUT_STATE(UP_BUTTON)==PRESSED && re_move==MANUAL_UP) || re_move==AUTO_UP){
 		if(rub_led_level<LED_LEVEL_MAX){   /* Check LED limits */
 			WindowLifter_TurnONLED();
 		}else{
 			WindowLifter_StopMovement();   /* If limit was reached, stop movement.	 */
 		}
 	}else{
 		if(re_move==MANUAL_UP){				/* If manual UP is active but its button */
 			WindowLifter_StopMovement();    /* isn't pressed anymore, stop movement. */
 		}
 	}
 	
 	/* Decisions for DOWN movements. */
 	if((INPUT_STATE(DOWN_BUTTON)==PRESSED && re_move==MANUAL_DOWN) || re_move==AUTO_DOWN){
		if(rub_led_level>=LED_LEVEL_MIN){
			WindowLifter_TurnOFFLED();		/* If limit was reached, stop movement.	 */
		}else{
 			WindowLifter_StopMovement();
 		}
 	}else{
 		if(re_move==MANUAL_DOWN){			/* If manual DOWN is active but its button */
 			WindowLifter_StopMovement();    /* isn't pressed anymore, stop movement. */
 		}
 	}
 	
 	TIMER_CLEAR_INT_FLAG(4);
 }
 
 /**************************************************************
 *  Name                 :	WindowLifter_Task_5S
 *  Description          :	This is the Timer Interrupt handler
 							for the 5s count to block the module.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Disables the 5s timer and resets
 							re_move so signals can be read again.
 **************************************************************/
 void WindowLifter_Task_5S(void){
 	
 	TIMER_STOP(5);
 	re_move=DISABLED;
 	
 	TIMER_CLEAR_INT_FLAG(5);
 }

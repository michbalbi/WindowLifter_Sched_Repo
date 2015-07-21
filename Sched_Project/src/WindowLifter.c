/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %WindowLifter.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 17 2015 %
*=============================================================================*/
/* DESCRIPTION : C source code for the Window Lifter's main functionality.    */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source used in the Window     */
/* Lifter initialization.                                                     */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  |                               | Michele Balbi    */
/* 	First draft.                                                              */
/*============================================================================*/

/* Includes */
/* -------- */
#include "conti_typedefs.h"
#include "WindowLifter.h"
#include "MPC5606B_GPIO_lib.h"

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
T_UBYTE rub_led_level = LED_LEVEL_MAX;

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */
E_WINDOWLIFTER_CURRENTSTATE re_currentstate = WAIT_STATE;
/*E_WINDOWLIFTER_INPUTSIGNAL re_inputsignal = NO_SIGNAL;*/

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
*  Name                 :	WindowLifter_CheckLimits
*  Description          :	Routine to stop the LED switching.
*  Parameters           :	void
*  Return               :	void
*  Critical/explanation :   Change re_currentstate to stop movement.
							Turn OFF LED indicators.
******************************************************************/
void WindowLifter_CheckLimits(void){
	
	if((re_currentstate==AUTO_UP_STATE || re_currentstate==MANUAL_UP_STATE) && rub_led_level==LED_LEVEL_MAX){
 		WindowLifter_StopMovement();
 	}
 	
 	if((re_currentstate==AUTO_DOWN_STATE || re_currentstate==MANUAL_DOWN_STATE) && rub_led_level<LED_LEVEL_MIN){
 		WindowLifter_StopMovement();
 	}
 	
 	if((re_currentstate==MANUAL_UP_STATE) && INPUT_STATE(UP_BUTTON)!=PRESSED){
 		WindowLifter_StopMovement();
 	}
	
	if((re_currentstate==MANUAL_DOWN_STATE) && INPUT_STATE(DOWN_BUTTON)!=PRESSED){
 		WindowLifter_StopMovement();
 	}
 	
 	if(re_currentstate==ANTI_PINCH_STATE && rub_led_level<LED_LEVEL_MIN){
 		WindowLifter_StopMovement();
 		re_currentstate=BLOCKED_STATE;
 	}
}

/*****************************************************************
*  Name                 :	WindowLifter_StopMovement
*  Description          :	Routine to stop the LED switching.
*  Parameters           :	void
*  Return               :	void
*  Critical/explanation :   Change re_currentstate to stop movement.
							Turn OFF LED indicators.
******************************************************************/
void WindowLifter_StopMovement(void){
	OUTPUT_LOW(UP_LED);
	OUTPUT_LOW(DOWN_LED);
	re_currentstate=WAIT_STATE;
}

 /*****************************************************************
 *  Name                 :	WindowLifter_Move1LevelUp
 *  Description          :	Routine to turn ON next LED.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Turn ON next LED and keep OFF the UP
 							movement LED indicator.
 ******************************************************************/
 void WindowLifter_Move1LevelUp(void){
 	OUTPUT_HIGH(UP_LED);
	OUTPUT_LOW(DOWN_LED);
	rub_led_level++;
	OUTPUT_HIGH(rub_led_level);
 }
 
 /*****************************************************************
 *  Name                 :	WindowLifter_Move1LevelDown
 *  Description          :	Routine to turn OFF next LED.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Turn OFF next LED and keep ON the DOWN
 							movement LED indicator.
 ******************************************************************/
 void WindowLifter_Move1LevelDown(void){
	OUTPUT_LOW(UP_LED);
	OUTPUT_HIGH(DOWN_LED);
	OUTPUT_LOW(rub_led_level);
	rub_led_level--;
 }

/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %WindowLifter.c%
* Instance:         1
* %version:         1.2 %
* %created_by:      Luis Medina %
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
/*  1.0      | 17/07/2015  |                               | Luis Medina      */
/* 	First draft.                                                              */
/*----------------------------------------------------------------------------*/
/*  1.1      | 10/07/2015  |                               | Michele Balbi    */
/* 	Implemented CheckLimits function.                                         */
/*----------------------------------------------------------------------------*/
/*  1.2      | 27/07/2015  |                               | Luis Medina      */
/* 	StopMovement function is now static.                                      */
/* 	Cleaner code and removed commented code due to MISRA checks.              */
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
static T_UBYTE rub_led_level = LED_LEVEL_MAX;

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */
E_WINDOWLIFTER_CURRENTSTATE re_currentstate = WAIT_STATE;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */
static void WindowLifter_StopMovement(void);


/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */


/* Private functions */
/* ----------------- */
/*****************************************************************
*  Name                 :	WindowLifter_StopMovement
*  Description          :	Routine to stop the LED switching.
*  Parameters           :	void
*  Return               :	void
*  Critical/explanation :   Change state to WAIT so movement is stopped.
							Turn OFF LED indicators.
******************************************************************/
static void WindowLifter_StopMovement(void){
	OUTPUT_LOW(UP_LED);
	OUTPUT_LOW(DOWN_LED);
	re_currentstate=WAIT_STATE;
}
 
/* Exported functions */
/* ------------------ */
/*****************************************************************
*  Name                 :	WindowLifter_CheckLimits
*  Description          :	Routine to stop the LED switching.
*  Parameters           :	void
*  Return               :	void
*  Critical/explanation :   Checks if the movement shall be stopped
							because of LED range limits, the release
							of a button while in MANUAL movement state 
							or a valid Anti Pinch signal.
							
							Calls StopMovement routine to turn off
							indicators.							
******************************************************************/
void WindowLifter_CheckLimits(void){
	
	/* Stop if UP movement is active and highest LED is reached */
	if((re_currentstate==AUTO_UP_STATE || re_currentstate==MANUAL_UP_STATE) && rub_led_level==LED_LEVEL_MAX){
 		WindowLifter_StopMovement();
 	}
 	
 	/* Stop if DOWN movement is active and lowest LED is reached */
 	if((re_currentstate==AUTO_DOWN_STATE || re_currentstate==MANUAL_DOWN_STATE) && rub_led_level<LED_LEVEL_MIN){
 		WindowLifter_StopMovement();
 	}
 	
 	/* Stop if MANUAL UP state is active and the corresponding button is released */
 	if((re_currentstate==MANUAL_UP_STATE) && INPUT_STATE(UP_BUTTON)!=PRESSED){
 		WindowLifter_StopMovement();
 	}
	
	/* Stop if MANUAL DOWN state is active and the corresponding button is released */
	if((re_currentstate==MANUAL_DOWN_STATE) && INPUT_STATE(DOWN_BUTTON)!=PRESSED){
 		WindowLifter_StopMovement();
 	}
 	
 	/* Stop if ANTI PINCH state is active and lowest LED is reached. Set to BLOCKED state */
 	if(re_currentstate==ANTI_PINCH_STATE && rub_led_level<LED_LEVEL_MIN){
 		WindowLifter_StopMovement();
 		re_currentstate=BLOCKED_STATE;
 	}
 }


 /*****************************************************************
 *  Name                 :	WindowLifter_Move1LevelUp
 *  Description          :	Routine to turn ON next LED.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Turn ON next LED and sets LED indicators.
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
 *  Critical/explanation :  Turn OFF next LED and sets LED indicators.
 ******************************************************************/
 void WindowLifter_Move1LevelDown(void){
	OUTPUT_LOW(UP_LED);
	OUTPUT_HIGH(DOWN_LED);
	OUTPUT_LOW(rub_led_level);
	rub_led_level--;
 }

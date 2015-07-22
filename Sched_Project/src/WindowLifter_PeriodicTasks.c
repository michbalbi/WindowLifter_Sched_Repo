/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %WindowLifter_PeriodicTasks.c%
* Instance:         1
* %version:         1.2 %
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
/*----------------------------------------------------------------------------*/
/*  1.1      | 20/07/2015  |                               | Michele Balbi    */
/* 	Added Polling function to detect pressed buttons.                         */
/*----------------------------------------------------------------------------*/
/*  1.2      | 22/07/2015  |                               | Michele Balbi    */
/* 	Modified Polling function to avoid wrong state changes.                   */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "conti_typedefs.h"
#include "MPC5606B_GPIO_lib.h"
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
#define ZERO 				0U
#define TEN_MS				8U
#define FIVE_HUNDRED_MS 	400U
#define FOUR_HUNDRED_MS		10U
#define FIVE_S				1000U

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
 *  Name                 :	WindowLifter_Task_Polling
 *  Description          :	
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  
 ******************************************************************/
 void WindowLifter_Task_Polling(void){
 
 	static T_UWORD luw_up_counter=ZERO, luw_down_counter=ZERO, luw_pinch_counter=ZERO;
  	
 	if(INPUT_STATE(ANTI_PINCH_BUTTON)==PRESSED){
 		luw_pinch_counter++;
 		
 		if(luw_pinch_counter>=TEN_MS && (re_currentstate == AUTO_UP_STATE || re_currentstate == MANUAL_UP_STATE)){
 			re_currentstate = ANTI_PINCH_STATE;
 		}
 	}else{
 		luw_pinch_counter=0;
 	}
 	
 	if(INPUT_STATE(UP_BUTTON)==PRESSED && re_currentstate!=ANTI_PINCH_STATE && re_currentstate!=BLOCKED_STATE && luw_down_counter==0){
 		luw_up_counter++;
 		
 		if(luw_up_counter>=TEN_MS && re_currentstate == WAIT_STATE){
 			re_currentstate = AUTO_UP_STATE;
 		}
 		
 		/*if(luw_up_counter>=TEN_MS && (re_currentstate == AUTO_DOWN_STATE || re_currentstate == MANUAL_DOWN_STATE)){
 			WindowLifter_StopMovement();
 			luw_up_counter=ZERO;
 		}*/
 		
 		if(luw_up_counter>=FIVE_HUNDRED_MS && re_currentstate == AUTO_UP_STATE){
 			re_currentstate = MANUAL_UP_STATE;
 		}
 	}else{
 		luw_up_counter=ZERO;
 	}
 	
 	if(INPUT_STATE(DOWN_BUTTON)==PRESSED && re_currentstate!=BLOCKED_STATE && luw_up_counter==0){
 		luw_down_counter++;
 		
 		if(luw_down_counter>=TEN_MS && re_currentstate == WAIT_STATE){
 			re_currentstate = AUTO_DOWN_STATE;
 		}
 		
 		/*if(luw_down_counter>=TEN_MS && (re_currentstate == AUTO_UP_STATE || re_currentstate == MANUAL_UP_STATE)){
 			WindowLifter_StopMovement();
 			luw_down_counter=ZERO;
 		}*/
 		
 		if(luw_down_counter>=FIVE_HUNDRED_MS && re_currentstate == AUTO_DOWN_STATE){
 			re_currentstate = MANUAL_DOWN_STATE;
 		}
 	}else{
 		luw_down_counter=ZERO;
 	} 	
 	
 	if(re_currentstate!=WAIT_STATE){
 		WindowLifter_CheckLimits();
 	}
 }
 
 /*****************************************************************
 *  Name                 :	WindowLifter_Task_400MS
 *  Description          :	Timer Interrupt handler for the 400ms
 							count between LEDs' change of state.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Checks movement state through re_currentstate,
 							if button is pressed (in case of manual
 							modes) and calls routines to turn ON/OFF
 							the next LED. Also calls the routine to
 							end the LED switching, if necessary.
 ******************************************************************/
 void WindowLifter_Task_400MS(void){
 	
 	static T_UWORD luw_counter=0;
 
 	luw_counter++;
 	
 	if(luw_counter==FOUR_HUNDRED_MS){
 		luw_counter=ZERO;
 		
 		if(re_currentstate==AUTO_UP_STATE || re_currentstate==MANUAL_UP_STATE){
 			WindowLifter_Move1LevelUp();
	 	}
	 	
	 	if(re_currentstate==AUTO_DOWN_STATE || re_currentstate==MANUAL_DOWN_STATE || re_currentstate==ANTI_PINCH_STATE){
	 		WindowLifter_Move1LevelDown();
	 	}
 	} 	
 }
 
 /**************************************************************
 *  Name                 :	WindowLifter_Task_5S
 *  Description          :	This is the Timer Interrupt handler
 							for the 5s count to block the module.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Disables the 5s timer and resets
 							re_currentstate so signals can be read again.
 **************************************************************/
 void WindowLifter_Task_5S(void){
 	
 	static T_UWORD luw_counter=0;
 	
 	if(re_currentstate==BLOCKED_STATE){
 		luw_counter++; 		
 	}
 	
 	if(luw_counter==FIVE_S){
 		luw_counter=ZERO;
 		re_currentstate=WAIT_STATE;
 	}
 }

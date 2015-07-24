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
 *  Description          :	This task assigns the appropiate state 
 							to the state machine.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Executed each 1.25ms, polles the buttons,
 							implements counters to filter the debounce.
 ******************************************************************/
 void WindowLifter_Task_Polling(void){
 
 	/* Counters for UP/DOWN/PINCH signals */ 
 	static T_UWORD luw_up_counter=ZERO, luw_down_counter=ZERO, luw_pinch_counter=ZERO;
  	
  	/* Count the time the Anti Pinch signal is present to filter glitches. */
 	if(INPUT_STATE(ANTI_PINCH_BUTTON)==PRESSED){
 		luw_pinch_counter++;
 		
 		/* If 10ms pass, only enter ANTI PINCH state if the current state is AUTO/MANUAL UP */
 		if(luw_pinch_counter>=TEN_MS && (re_currentstate == AUTO_UP_STATE || re_currentstate == MANUAL_UP_STATE)){
 			re_currentstate = ANTI_PINCH_STATE;
 		}
 	}else{
 		/* Reset Anti Pinch signal counter. */
 		luw_pinch_counter=0;
 	}
 	
 	/* Count the time the UP signal is present to filter glitches, only if the system isn't in BLOCKED/ANTI PINCH state. */
 	if(INPUT_STATE(UP_BUTTON)==PRESSED && re_currentstate!=ANTI_PINCH_STATE && re_currentstate!=BLOCKED_STATE && luw_down_counter==0){
 		luw_up_counter++;
 		
 		/* If 10ms pass, only enter AUTO UP state if the current state is WAIT */ 		
 		if(luw_up_counter>=TEN_MS && re_currentstate == WAIT_STATE){
 			re_currentstate = AUTO_UP_STATE;
 		}
 		
 		/* If 10ms pass, only enter MANUAL UP state if the current state is already AUTO */ 		
 		if(luw_up_counter>=FIVE_HUNDRED_MS && re_currentstate == AUTO_UP_STATE){
 			re_currentstate = MANUAL_UP_STATE;
 		}
 	}else{
 		/* Reset UP button signal counter every time it is detected as released. */
 		luw_up_counter=ZERO;
 	}
 	
 	/* Count the time the DOWN signal is present to filter glitches, only if the system isn't in BLOCKED/ANTI PINCH state. */
 	if(INPUT_STATE(DOWN_BUTTON)==PRESSED && re_currentstate!=BLOCKED_STATE && luw_up_counter==0){
 		luw_down_counter++;
 		
 		/* If 10ms pass, only enter AUTO DOWN state if the current state is WAIT */
 		if(luw_down_counter>=TEN_MS && re_currentstate == WAIT_STATE){
 			re_currentstate = AUTO_DOWN_STATE;
 		}
 		
 		/* If 10ms pass, only enter MANUAL DOWN state if the current state is already AUTO */
 		if(luw_down_counter>=FIVE_HUNDRED_MS && re_currentstate == AUTO_DOWN_STATE){
 			re_currentstate = MANUAL_DOWN_STATE;
 		}
 	}else{
 		/* Reset DOWN button signal counter every time it is detected as released */
 		luw_down_counter=ZERO;
 	} 	
 	
 	/* Check if the movement should continue while the system isn't in WAIT state. */
 	if(re_currentstate!=WAIT_STATE){
 		WindowLifter_CheckLimits();
 	}
 }
 
 /*****************************************************************
 *  Name                 :	WindowLifter_Task_400MS
 *  Description          :	Task handler for the 400ms count between 
 							LEDs' change of state.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Implements a counter to validate de 400ms
 							since the task is called each 40ms.
 							
 							Checks the state through re_currentstate,
 							and calls routines to turn ON/OFF
 							the next LED.
 ******************************************************************/
 void WindowLifter_Task_400MS(void){
 	
 	/* Counter to check if 400ms periods occur. */
 	static T_UWORD luw_counter=0;
 
 	luw_counter++;
 	
 	/* Each time the 400ms periods are valid, reset the counter and check the active states to do the appropriate movement. */
 	if(luw_counter==FOUR_HUNDRED_MS){
 		luw_counter=ZERO;
 		
 		/* Turn on next LED (window up) if any UP state is active. */
 		if(re_currentstate==AUTO_UP_STATE || re_currentstate==MANUAL_UP_STATE){
 			WindowLifter_Move1LevelUp();
	 	}
	 	
	 	/* Turn off next LED (window down) if any DOWN state is active. */
	 	if(re_currentstate==AUTO_DOWN_STATE || re_currentstate==MANUAL_DOWN_STATE || re_currentstate==ANTI_PINCH_STATE){
	 		WindowLifter_Move1LevelDown();
	 	}
 	} 	
 }
 
 /**************************************************************
 *  Name                 :	WindowLifter_Task_5S
 *  Description          :	This is the task used to block the module
 							if it enters the Anti Pinch state.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Implements a counter to validate de 5s
 							since the task is called each 5ms.
 							
 							Sets the state to WAIT so signals 
 							can be read again.
 **************************************************************/
 void WindowLifter_Task_5S(void){
 	
 	/* Counter used to validate the 5 seconds period. */
 	static T_UWORD luw_counter=ZERO;
 	
 	/* The counter should only count while in BLOCKED state. */
 	if(re_currentstate==BLOCKED_STATE){
 		luw_counter++; 		
 	}
 	
 	/* Once the 5 seconds pass, unlock the system. */
 	if(luw_counter==FIVE_S){
 		luw_counter=ZERO;
 		re_currentstate=WAIT_STATE;
 	}
 }

/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %main.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 13 2015 %
*=============================================================================*/
/* DESCRIPTION : C source template file for the scheduler application.        */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source code which prepares    */
/* the environment for the execution of the scheduler.                        */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/2015  |                               | Michele Balbi    */
/* 	First draft of the file. Includes used libraries.                         */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "conti_typedefs.h"
#include "MPC5606B_GPIO_lib.h"
#include "MPC5606B_ClkInit.h"
#include "MPC5606B_INTERRUPTS_lib.h"
#include "MPC5606B_PIT_lib.h"
#include "MemAlloc_Cfg.h"
#include "Sch.h"

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
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/



/* ---------------- MAIN FUNCTION -------------------------- */
/**************************************************************
 *  Name                 :	main
 *  Description          :
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  The main routine initializes the
 							peripherals used in this system.
 **************************************************************/
int main(void) {
	
	initModesAndClock();    /* Initialize mode entries and system clock */
	disableWatchdog();      /* Disable watchdog */
	initPeriClkGen();       /* Initialize peripheral clock generation for DSPIs */
	
	MemAllocInit(&MemAllocConfig);
	
	/*GPIO_AS_OUTPUT(PC2);
	GPIO_AS_OUTPUT(PC3);
	GPIO_AS_OUTPUT(PC4);
	GPIO_AS_OUTPUT(PC5);
	GPIO_AS_OUTPUT(PC6);
	GPIO_AS_OUTPUT(PC7);
	
	OUTPUT_LOW(PC2);
	OUTPUT_LOW(PC3);
	OUTPUT_LOW(PC4);
	OUTPUT_LOW(PC5);
	OUTPUT_LOW(PC6);
	OUTPUT_LOW(PC7);*/
	
	GPIO_AS_OUTPUT(LED1);
	GPIO_AS_OUTPUT(LED2);
	GPIO_AS_OUTPUT(LED3);
	GPIO_AS_OUTPUT(LED4);
	
	/* Interrupts init, SW Mode */
    INT_SW_VECTOR_MODE();
    
    Sch_Init(&cs_SchConfig);
    
    INTC_InstallINTCInterruptHandler(Sch_OSTick, PIT0_Vector, PRIORITY13);
    INT_LOWER_CPR(PRIORITY0);
    INTC_InitINTCInterrupts(); 
    
    Sch_Start(); 
	
	for (;;) { 	} /* Execution shall never reach this for*/
}


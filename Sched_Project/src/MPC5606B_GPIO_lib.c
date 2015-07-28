/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_GPIO_lib.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 17 2015 %
*=============================================================================*/
/* DESCRIPTION : C source code for GPIO configuration.                        */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source code used to initialize*/
/* the GPIO pins.                                                             */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  |                               | Michele Balbi    */
/* 	Added GPIO_Init() function.                                               */
/*============================================================================*/

/* Includes */
/* -------- */
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
/********************************************************************************
 *  Name                 :	GPIO_Init
 *  Description          :	GPIO configuration function.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This routine configures the GPIOs used in the 
 							application.
 ********************************************************************************/
 void GPIO_Init(void){
 
 	GPIO_AS_OUTPUT(PC2);
	GPIO_AS_OUTPUT(PC3);
	GPIO_AS_OUTPUT(PC4);
	GPIO_AS_OUTPUT(PC5);
	GPIO_AS_OUTPUT(PC6);
	GPIO_AS_OUTPUT(PC7);
	GPIO_AS_OUTPUT(PC8);
	GPIO_AS_OUTPUT(PC9);
	GPIO_AS_OUTPUT(PC10);
	GPIO_AS_OUTPUT(PC11);
	
	GPIO_AS_OUTPUT(PC14);
	GPIO_AS_OUTPUT(PC15);
	
	GPIO_AS_INPUT(PUSH1);
	GPIO_AS_INPUT(PUSH2);
	GPIO_AS_INPUT(PUSH3);
	
	OUTPUT_HIGH(PC2);
	OUTPUT_HIGH(PC3);
	OUTPUT_HIGH(PC4);
	OUTPUT_HIGH(PC5);
	OUTPUT_HIGH(PC6);
	OUTPUT_HIGH(PC7);
	OUTPUT_HIGH(PC8);
	OUTPUT_HIGH(PC9);
	OUTPUT_HIGH(PC10);
	OUTPUT_HIGH(PC11);
	
	OUTPUT_LOW(PC14);
	OUTPUT_LOW(PC15);
	
 }
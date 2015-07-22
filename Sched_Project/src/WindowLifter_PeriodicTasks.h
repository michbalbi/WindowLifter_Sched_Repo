/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %WindowLifter_PeriodicTasks.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for the timer functions.                         */
/*============================================================================*/
/* FUNCTION COMMENT :  This files contains the prototypes for the implemented */
/* timer functions.                                                           */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 10/07/2015  |                               | Michele Balbi    */
/* First Draft.																  */
/*============================================================================*/

#ifndef _TIMER_MODULE_H_                         /* To avoid double inclusion */
#define _TIMER_MODULE_H_

/* Includes */
/* -------- */
#include "conti_typedefs.h"
#include "WindowLifter_Types.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void WindowLifter_Task_Polling(void);
/*extern void WindowLifter_Task_10MS(void);*/
extern void WindowLifter_Task_400MS(void);
/*extern void WindowLifter_Task_500MS(void);*/
extern void WindowLifter_Task_5S(void);


/* Functions macros */


/* Exported defines */




#endif



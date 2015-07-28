/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %WindowLifter.h%
* Instance:         1
* %version:         1.2 %
* %created_by:      Luis Medina  %
* %date_created:    July 17 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for the Window Lifter's main functionality.      */
/*============================================================================*/
/* FUNCTION COMMENT :   										              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 17/07/2015  |                               | Luis Medina      */
/* First Draft 																  */
/*----------------------------------------------------------------------------*/
/*  1.1      | 20/07/2015  |                               | Michele Balbi    */
/* Added prototype for exported function CheckLimits. Removed StopMovement.   */
/*----------------------------------------------------------------------------*/
/*  1.2      | 27/07/2015  |                               | Luis Medina      */
/* Cleaner code. Deleted commented code due to MISRA checks.				  */
/*============================================================================*/

#ifndef WINDOWLIFTER_H                               /* To avoid double inclusion */
#define WINDOWLIFTER_H

/* Includes */
/* -------- */
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
extern E_WINDOWLIFTER_CURRENTSTATE re_currentstate;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void WindowLifter_CheckLimits(void);
extern void WindowLifter_Move1LevelUp(void);
extern void WindowLifter_Move1LevelDown(void);
 
/* Functions macros */


/* Exported defines */


#endif



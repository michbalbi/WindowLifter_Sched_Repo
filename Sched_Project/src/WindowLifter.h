/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %WindowLifter.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
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
/*  1.0      | 17/07/2015  |                               | Michele Balbi    */
/* First Draft 																  */
/*============================================================================*/

#ifndef _SCH_H_                               /* To avoid double inclusion */
#define _SCH_H_

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
extern T_UBYTE rub_led_level;

/* WORDS */


/* LONGS and STRUCTURES */
extern E_WINDOWLIFTER_MOVEMENTLIST re_move;
extern E_WINDOWLIFTER_BUTTONLIST re_button_pressed;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void WindowLifter_StopMovement(void);
extern void WindowLifter_Move1LevelUp(void);
extern void WindowLifter_Move1LevelDown(void);
 
/* Functions macros */


/* Exported defines */


#endif



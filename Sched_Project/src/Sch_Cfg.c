/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %Sch_Cfg.c%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    July 13 2015 %
*=============================================================================*/
/* DESCRIPTION : C source code for the scheduler's task configuration table.  */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source used in the scheduler's*/
/* configuration table.                                                       */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 13/07/2015  |                               | Michele Balbi    */
/* 	First draft.                                                              */
/*============================================================================*/

/* Includes */
/* -------- */
#include "Sch_Cfg.h"
#include "Sch_Tasks.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */

/*const S_TASK_DESCRIPTOR cas_SchTaskDescriptorConfig[] = {
	{0, MASK_3P125MS, 	TASK_3P125MS, 	(void*)0    },
	{1, MASK_6P25MS,	TASK_6P25MS, 	(void*)0    },
	{2, MASK_12P5MS, 	TASK_12P5MS, 	(void*)0    },
	{3, MASK_25MS, 		TASK_25MS, 		(void*)0    },
	{5, MASK_50MS, 		TASK_50MS, 		(void*)0    },
	{6, MASK_100MS, 	TASK_100MS, 	(void*)0    },
};*/

const S_TASK_DESCRIPTOR cas_SchTaskDescriptorConfig[] = {
	{0, MASK_3P125MS, 	TASK_3P125MS, 	Sch_Task_3P125MS},
	{1, MASK_6P25MS,	TASK_6P25MS, 	Sch_Task_6P25MS },
	{2, MASK_12P5MS, 	TASK_12P5MS, 	Sch_Task_12P5MS },
	{3, MASK_25MS, 		TASK_25MS, 		Sch_Task_25MS   },
	{5, MASK_50MS, 		TASK_50MS, 		Sch_Task_50MS   },
	{6, MASK_100MS, 	TASK_100MS, 	Sch_Task_100MS  },
};

const S_SCH_CONFIG cs_SchConfig = {
	(sizeof(cas_SchTaskDescriptorConfig)/sizeof(cas_SchTaskDescriptorConfig[0])),
	cas_SchTaskDescriptorConfig
};

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



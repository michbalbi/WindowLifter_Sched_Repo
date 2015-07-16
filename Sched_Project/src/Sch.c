/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %Sch.c%
* Instance:         1
* %version:         1.1 %
* %created_by:      Michele Balbi %
* %date_created:    July 13 2015 %
*=============================================================================*/
/* DESCRIPTION : C source code for the scheduler's main functionality.        */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source used in the scheduler's*/
/* initialization, including the tick callback function.                      */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 13/07/2015  |                               | Michele Balbi    */
/* 	First draft.                                                              */
/*----------------------------------------------------------------------------*/
/*  1.1      | 16/07/2015  |                               | Michele Balbi    */
/* 	Function documentation.                                                   */
/*============================================================================*/

/* Includes */
/* -------- */
#include "conti_typedefs.h"
#include "MPC5606B_INTERRUPTS_lib.h"
#include "MPC5606B_PIT_lib.h"
#include "Sch_Types.h"
#include "Sch.h"
#include "MemAlloc.h"


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
const S_SCH_CONFIG *rps_SchConfig_ptr;

S_SCH_TASK_CONTROL *ras_SchTaskControlBlock_ptr;

/*S_SCH_TASK_CONTROL ras_SchTaskControlBlock[] = {
	{TASK_STATE_SUSPENDED, (void*)0 },
	{TASK_STATE_SUSPENDED, (void*)0 },
	{TASK_STATE_SUSPENDED, (void*)0 },
	{TASK_STATE_SUSPENDED, (void*)0 },
	{TASK_STATE_SUSPENDED, (void*)0 },
	{TASK_STATE_SUSPENDED, (void*)0 },
};*/

S_SCH_CONTROL rs_SchControl = {
	0,
	TASK_BKG,
	SCH_UNINIT,
};


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

/********************************************************************************
 *  Name                 :	Sch_Background
 *  Description          :	The Scheduler's task executed repeatedly to call the
 							appropriate task when marked as READY.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  Iterate all tasks and see which one is marked as READY
 	   						and execute it via their function ptr and mark it as RUNNING.
 	   						Also update the SchControl.SchTaskRunning field.
 	   						After the execution of the task, its state is changed
 	   						to SUSPENDED.
 ********************************************************************************/
 void Sch_Background(void){
 
 	   	T_UBYTE lub_i, lub_NumberOfTasks;
 		lub_NumberOfTasks = rps_SchConfig_ptr->SchNumberOfTasks;
 	
 	   for(;;){
 	   
 	   		for(lub_i=0; lub_i<lub_NumberOfTasks; lub_i++){	
 				
 				if(ras_SchTaskControlBlock_ptr[lub_i].SchTaskState == TASK_STATE_READY){
 					rs_SchControl.SchStatus = SCH_RUNNING;
 					rs_SchControl.SchTaskRunning = rps_SchConfig_ptr->SchTaskDescriptor->SchTaskId;
 					ras_SchTaskControlBlock_ptr[lub_i].SchTaskState = TASK_STATE_RUNNING;
 					(ras_SchTaskControlBlock_ptr[lub_i].TaskFunctionControlPtr)();
 					ras_SchTaskControlBlock_ptr[lub_i].SchTaskState = TASK_STATE_SUSPENDED;	
 				}	
 			}
 	   		rs_SchControl.SchTaskRunning = TASK_BKG;
 			rs_SchControl.SchStatus = SCH_IDLE;	
 	   }
 }

/* Exported functions */
/* ------------------ */
/********************************************************************************
 *  Name                 :	Sch_Init
 *  Description          :	Scheduler's initialization function.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This routine prepares the scheduler to run. 
 							Initializes the Task Control Block according to the
 							number of configured tasks, suding a memory allocation algorithm,
 							marking all tasks as SUSPENDED.
 							Configures the timer used as the system's tick.
 							Sets the scheduler's counter to 0 and its status to INITIALIZED.
 ********************************************************************************/
 void Sch_Init(const S_SCH_CONFIG *lps_SchConfig){
 	T_UBYTE lub_i, lub_NumberOfTasks;
 	S_TASK_DESCRIPTOR * lp_TaskDescriptorPtr; 
 	rps_SchConfig_ptr = lps_SchConfig;
 	
 	lp_TaskDescriptorPtr = (S_TASK_DESCRIPTOR *)(lps_SchConfig->SchTaskDescriptor);
 	lub_NumberOfTasks = lps_SchConfig->SchNumberOfTasks;
 	
 	ras_SchTaskControlBlock_ptr = (S_SCH_TASK_CONTROL*)MemAlloc(sizeof(S_SCH_TASK_CONTROL)*lub_NumberOfTasks);
 	
 	for(lub_i=0; lub_i<lub_NumberOfTasks; lub_i++){
 		
 		/* Set all tasks to SUSPENDED */
 		ras_SchTaskControlBlock_ptr[lub_i].SchTaskState = TASK_STATE_SUSPENDED;
 		ras_SchTaskControlBlock_ptr[lub_i].TaskFunctionControlPtr = lp_TaskDescriptorPtr->TaskFunctionPtr;
 		lp_TaskDescriptorPtr++;
 	}
  	
    TIMER_LOAD_VALUE_CYCLES(49999U,0); /*781.25 us to cycles*/
    TIMER_ENABLE_INT(0);
    TIMER_INIT();
  	
 	rs_SchControl.SchCounter = 0;
 	rs_SchControl.SchStatus = SCH_INIT;
 }
 
 /******************************************************************************
 *  Name                 :	Sch_Start
 *  Description          :	Scheduler's Start routine.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This routine starts the execution of the scheduler.
 							Sets its status to RUNNING.
 							Starts the timer used as the tick.
 							Calls the scheduler's background task.
 ******************************************************************************/
 void Sch_Start(void){
 	rs_SchControl.SchStatus = SCH_RUNNING;
 	TIMER_START(0);
 	Sch_Background();
 }
 
 /******************************************************************************
 *  Name                 :	Sch_Stop
 *  Description          :	Scheduler's Stop routine.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This routine stops the execution of the scheduler.
 							Sets its status to HALTED.
 							Stops the timer used as the tick.
 ******************************************************************************/
 void Sch_Stop(void){
 	TIMER_STOP(0);
 	rs_SchControl.SchStatus = SCH_HALTED;
 }

/******************************************************************************
 *  Name                 :	Sch_OSTick
 *  Description          :	Scheduler's Stop routine.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  This is the callback routine for the timer.
 							In this function the scheduelr's counter is increased
 							and compared against eachs task's configured mask and
 							offset to determine if it shall be executed. If so,
 							the task is marked as READY
 ******************************************************************************/
 void Sch_OSTick(void){
 	T_UBYTE lub_i, lub_NumberOfTasks;
 	S_TASK_DESCRIPTOR * lp_TaskDescriptorPtr; 
 	
 	TIMER_CLEAR_INT_FLAG(0);
 	lp_TaskDescriptorPtr = (S_TASK_DESCRIPTOR *)(rps_SchConfig_ptr->SchTaskDescriptor);
 
 	rs_SchControl.SchCounter++;
 	lub_NumberOfTasks = rps_SchConfig_ptr->SchNumberOfTasks;
 	
 	/* Compare counter with each task mask and offset. Mark
 	   task as READY accordingly */   
   	for(lub_i=0; lub_i<lub_NumberOfTasks; lub_i++){
   		
   		if(((lp_TaskDescriptorPtr->SchTaskMask)&(rs_SchControl.SchCounter))==(lp_TaskDescriptorPtr->SchTaskOffset)){
   			ras_SchTaskControlBlock_ptr[lub_i].SchTaskState = TASK_STATE_READY;
   		}
   		
   		lp_TaskDescriptorPtr++;
   		
   	}
 	
 }
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */ 

#include "can.h"
#include "usart.h"    

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId worker1Handle;
osThreadId worker2Handle;

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void work1Task(void const * argument);
void worker2Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of worker1 */
  osThreadDef(worker1, work1Task, osPriorityAboveNormal, 0, 128);
  worker1Handle = osThreadCreate(osThread(worker1), NULL);

  /* definition and creation of worker2 */
  osThreadDef(worker2, worker2Task, osPriorityNormal, 0, 128);
  worker2Handle = osThreadCreate(osThread(worker2), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* work1Task function */
void work1Task(void const * argument)
{

  /* USER CODE BEGIN work1Task */
  /* Infinite loop */
  for(;;)
  {
	  osSignalWait(0x0001, osWaitForever);
	  info_print(&(hcan1.pRxMsg->Data[0]));
	  //info_print("ss");
  }
  /* USER CODE END work1Task */
}

/* worker2Task function */
void worker2Task(void const * argument)
{
  /* USER CODE BEGIN worker2Task */
  /* Infinite loop */
  for(;;)
  {
	  osDelay(100);
	  hcan2.pTxMsg->StdId = 0x123;
	  hcan2.pTxMsg->RTR = CAN_RTR_DATA;
	  hcan2.pTxMsg->IDE = CAN_ID_STD;
	  hcan2.pTxMsg->DLC = 8;
	  hcan2.pTxMsg->Data[0] = 'C';
	  hcan2.pTxMsg->Data[1] = 'A';
	  hcan2.pTxMsg->Data[2] = 'N';
	  hcan2.pTxMsg->Data[3] = ' ';
	  hcan2.pTxMsg->Data[4] = 'T';
	  hcan2.pTxMsg->Data[5] = 'e';
	  hcan2.pTxMsg->Data[6] = 's';
	  hcan2.pTxMsg->Data[7] = 't';

	  HAL_CAN_Transmit(&hcan2, 10);
	  osDelay(10000);
  }
  /* USER CODE END worker2Task */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

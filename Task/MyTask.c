/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: MyTask.c
Description		: 主要实现系统多任务管理功能
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-22
Modify			: 
Modify Time		: 
******************************************************************************/
#include "MyTask.h"
#include "Fifo.h"
#include "Memory.h"
#include "Debugprintf.h"
#include "Command.h"
#include "Analysis.h"
#include "Wifi.h"
#include "Pack.h"
#include "WifiCon.h"
#include "ReCmd.h"
#include "Function.h"

#define START_TASK_PRIO		1
#define START_STK_SIZE 		32
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

#define MASTER1_TASK_PRIO		2
#define MASTER1_STK_SIZE 		256
TaskHandle_t MASTER1Task_Handler;
void master1_task(void *pvParameters);

#define MASTER2_TASK_PRIO		3
#define MASTER2_STK_SIZE 		512
TaskHandle_t MASTER2Task_Handler;
void master2_task(void *pvParameters);

#define MASTER3_TASK_PRIO		4
#define MASTER3_STK_SIZE 		64
TaskHandle_t MASTER3Task_Handler;
void master3_task(void *pvParameters);

#define MASTER4_TASK_PRIO		4
#define MASTER4_STK_SIZE 		64
TaskHandle_t MASTER4Task_Handler;
void master4_task(void *pvParameters);

void start_system()
{
	xTaskCreate((TaskFunction_t )start_task,
				(const char*    )"start_task",
				(uint16_t       )START_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )START_TASK_PRIO,
				(TaskHandle_t*  )&StartTask_Handler);
	vTaskStartScheduler();
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();

	xTaskCreate((TaskFunction_t )master1_task,
				(const char*    )"master1_task",
				(uint16_t       )MASTER1_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER1_TASK_PRIO,
				(TaskHandle_t*  )&MASTER1Task_Handler);

	xTaskCreate((TaskFunction_t )master2_task,
				(const char*    )"master2_task",
				(uint16_t       )MASTER2_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER2_TASK_PRIO,
				(TaskHandle_t*  )&MASTER2Task_Handler);

	xTaskCreate((TaskFunction_t )master3_task,
				(const char*    )"master3_task",
				(uint16_t       )MASTER3_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER3_TASK_PRIO,
				(TaskHandle_t*  )&MASTER3Task_Handler);

	xTaskCreate((TaskFunction_t )master4_task,
				(const char*    )"master4_task",
				(uint16_t       )MASTER4_STK_SIZE,
				(void*          )NULL,
				(UBaseType_t    )MASTER4_TASK_PRIO,
				(TaskHandle_t*  )&MASTER4Task_Handler);

	vTaskDelete(StartTask_Handler);
	taskEXIT_CRITICAL();
}

void master1_task(void *pvParameters)//任务一用于232通信
{
//	u8 buf[10];
	u8 len;
	u8 lentemp;
	u8 tagtype,type,taglen;
	u8 buf[12];
	Wifi_t.respond = true;
	while(1)
	{
		TogglePin(LED1);
		if(!fifo_empty(&TagCacheFifo))
		{
			if(info_out_fifo(&TagCacheFifo,&len,&tagdata.data[0]))
			{
				find_tag(tagdata.data,&lentemp,&tagdata.tag[0]);
			}
//			if(fifo_gets(&TagCacheFifo,buf,10))
//			{
//				printf_232("232=%s",buf);
//				printf("232->wifi=%s",buf);
//			}
		}
		memset(buf,0,sizeof(buf));
		if((!fifo_empty(&TagFifo))&&(Wifi_t.respond == true))
		{
			tag_out_fifo(&TagFifo,&tagtype,&type,&taglen,&buf[0]);
			Pack(buf,taglen,0x0a);
			Wifi_t.respond = false;
		}
		vTaskDelay(50);
	}
}

void master2_task(void *pvParameters)//用于数据打包如对
{
	u16 tmp;
	u8 buf[256];
	wifi_reset();
	while(1)
	{
		wifi_con();
		if(Wifi_t.connect)
		{
			if(!fifo_empty(&WifiFifo))
			{
				tmp = fifo_find(&WifiFifo,(u8 *)"msg!ok",6);
				if(fifo_cmp(&WifiFifo,tmp,(u8 *)"msg!ok",6))
				{
					fifo_Clr(&WifiFifo);
					Wifi_t.respond = true;
				}

				tmp = fifo_validSize(&WifiFifo);
				memset(buf,0,sizeof(buf));
				if(fifo_gets(&WifiFifo,buf,tmp))
				{
					printf_232("link_wifi->%s\r\n",buf);
					Analysis_cmd(buf);
				}
			}
		}
		else
		{
			fifo_Clr(&WifiFifo);
		}
		vTaskDelay(50);
	}
}
void master3_task(void *pvParameters)//实现报警功能和盘点功能
{
	while(1)
	{
		//TogglePin(LED4);
		vTaskDelay(150);
	}
}

void master4_task(void *pvParameters)//简单任务
{
	while(1)
	{
		Count_time();
		if(RunFlag.alame)
		{
			TogglePin(LED2);
		}
		if(RunFlag.autof)
		{
			//RunFlag.autonum++;
			TogglePin(LED4);
		}
		vTaskDelay(100);
	}
}



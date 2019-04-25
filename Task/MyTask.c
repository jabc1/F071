#include "MyTask.h"
#include "Fifo.h"
#include "Memory.h"
#include "Debugprintf.h"
#include "Command.h"
#include "Analysis.h"
#include "Wifi.h"
#include "Pack.h"
#include "WifiCon.h"

#define START_TASK_PRIO		1
#define START_STK_SIZE 		32
TaskHandle_t StartTask_Handler;
void start_task(void *pvParameters);

#define MASTER1_TASK_PRIO		2
#define MASTER1_STK_SIZE 		512
TaskHandle_t MASTER1Task_Handler;
void master1_task(void *pvParameters);

#define MASTER2_TASK_PRIO		3
#define MASTER2_STK_SIZE 		256
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
	xTaskCreate((TaskFunction_t )start_task,            //������
				(const char*    )"start_task",          //��������
				(uint16_t       )START_STK_SIZE,        //�����ջ��С
				(void*          )NULL,                  //���ݸ��������Ĳ���
				(UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
				(TaskHandle_t*  )&StartTask_Handler);   //������              
	vTaskStartScheduler();          //�����������
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();			//�����ٽ���

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

	vTaskDelete(StartTask_Handler);	//ɾ����ʼ����
	taskEXIT_CRITICAL();			//�˳��ٽ���
}

void master1_task(void *pvParameters)//����һ����232ͨ��
{
	u8 buf[10];
	while(1)
	{
		TogglePin(LED1);
		if(!fifo_empty(&TagCacheFifo))
		{
			if(fifo_gets(&TagCacheFifo,buf,10))
			{
				printf_232("232=%s",buf);
				printf_wifi("%s",buf);
			}
		}
		vTaskDelay(50);
	}
}

void master2_task(void *pvParameters)//�������ݴ�����
{
	u8 buf[10];
	wifi_reset();
	while(1)
	{
		TogglePin(LED3);
		if(!fifo_empty(&WifiFifo))
		{
			if(fifo_gets(&WifiFifo,buf,10))
			{
				printf_wifi("%s",buf);
				printf_232("wifi receive=%s",buf);
			}
		}
		wifi_con();
		vTaskDelay(100);
	}
}
void master3_task(void *pvParameters)//������
{
	while(1)
	{
		TogglePin(LED4);
		vTaskDelay(150);
	}
}

void master4_task(void *pvParameters)//������
{
	while(1)
	{
		TogglePin(LED2);
		vTaskDelay(120);
	}
}



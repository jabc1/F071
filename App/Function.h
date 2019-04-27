/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Function.h
Description		: 主要实现上位机下发指令执行功能相关宏定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-27
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _function_h
#define _function_h

#include "arm_base_define.h"

#define		VER			"VER_1.0.1_20190427"


typedef struct{
	u8 *head;
	u8 *id;
	u8 *iddata;
	u8 *cmd;
	u8 *cmddata;
}_Cmd;

struct attr_exe_data
{
	u8 *cmd;
	RunStatus (*exe_attr)(u8 *,u8 *);
};

typedef struct
{
	u8 alame;
	u8 tim;
}_Run_s;



RunStatus MsgDeal(u8 *data,u32 len);
RunStatus Inv_fun(u8 *cmd,u8 *data);
RunStatus Alarm_fun(u8 *cmd,u8 *data);
RunStatus Ver_fun(u8 *cmd,u8 *data);

#endif



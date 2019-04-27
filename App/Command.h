/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Command.h
Description		: 主要实现读标签命令功能相关定义
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-26
Modify			: 
Modify Time		: 
******************************************************************************/
#ifndef _command_h
#define _command_h
#include "arm_base_define.h"
u16 cal_crc16_ext(u16 initval ,u8 *ptr, u8 len);

u8 send_data(u8 *data,u8 len);





#endif




/************Copyright(C) Kaikai Technology 2019-03-29***********************
File name		: Function.c
Description		: ��Ҫʵ����λ���·�ָ��ִ�й���
Platform		: MDK V5.26.0.0
Version			: V1.0
Author			: Jason
Create Time		: 2019-04-27
Modify			: 
Modify Time		: 
******************************************************************************/
#include "Function.h"
#include "Debugprintf.h"

_Run_s RunFlag;

const struct attr_exe_data SysAttrTable[] =
{
	{(u8 *)"inventory",Inv_fun},
	{(u8 *)"alarm",Alarm_fun},
	{(u8 *)"version",Ver_fun},
};

/*******************************************************************************
* @Function		:u8 GetAttrNum(void)
* @Description	:��ȡ�б���
* @Input		:null
* @Output		:null
* @Return		:len
* @Others		:null
*******************************************************************************/
u8 GetAttrNum(void)
{
	return (sizeof(SysAttrTable)/sizeof(struct attr_exe_data));
}

/*******************************************************************************
* @Function		:RunStatus MsgDeal(u8 *data,u32 len)
* @Description	:������������ִ�й��ܣ�����û���õ����Է��Ժ�Э�������ʱ�������
* @Input		:u8 *data,u32 len
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus MsgDeal(u8 *data,u32 len)
{
	u8 i;
	u8 count;
	_Cmd *Pack;

	const struct attr_exe_data* p_attr_exe = SysAttrTable;

	count = GetAttrNum();
	Pack = (_Cmd *)data;

	for(i=0;i<count;i++)
	{
		if(strcmp((char *)Pack->cmd,(char *)p_attr_exe->cmd)==0)
		{
			if(p_attr_exe->exe_attr != NULL)
			{
				p_attr_exe->exe_attr(Pack->cmd,Pack->cmddata);
			}
			return RUN_OK;
		}
		p_attr_exe++;
	}
	if(i==count)
	{
		return RUN_ERROR;
	}
	return RUN_OK;
}



/*******************************************************************************
* @Function		:RunStatus Inv_fun(u8 *cmd,u8 *data)
* @Description	:ִ���̵�����ƽʱĬ����10s�̵㣬��������Ϊʵʱ�̵㣬5min��ָ��Զ��̵�
* @Input		:u8 *cmd,u8 *data
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus Inv_fun(u8 *cmd,u8 *data)
{
	u16 val;
	if(strncmp((char *)cmd,(char *)"inventory",strlen((char *)cmd))!=0)
	{
		return RUN_ERROR;
	}
	val = atoi((char *)data);

	RunFlag.tim = val;

	printf("inventory time %d\r\n",val);
	return RUN_OK;
}

/*******************************************************************************
* @Function		:RunStatus Alarm_fun(u8 *cmd,u8 *data)
* @Description	:ִ�б�������
* @Input		:u8 *cmd,u8 *data
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus Alarm_fun(u8 *cmd,u8 *data)
{
	if(strncmp((char *)cmd,(char *)"alarm",5)!=0)
	{
		return RUN_ERROR;
	}
	if(strncmp((char *)data,(char *)"yes",3)==0)
	{
		printf("Alarm_fun start");
		RunFlag.alame = true;
	}
	else if(strncmp((char *)data,(char *)"no",2)==0)
	{
		printf("Alarm_fun end");
		RunFlag.alame = false;
	}
	return RUN_OK;
}

/*******************************************************************************
* @Function		:RunStatus Ver_fun(u8 *cmd,u8 *data)
* @Description	:ִ�в�ѯ�汾����
* @Input		:u8 *cmd,u8 *data
* @Output		:null
* @Return		:RunStatus
* @Others		:null
*******************************************************************************/
RunStatus Ver_fun(u8 *cmd,u8 *data)
{
	if(strncmp((char *)cmd,(char *)"version",7)!=0)
	{
		return RUN_ERROR;
	}
	if(strncmp((char *)data,(char *)"?",1)==0)
	{
		printf("%s\r\n",VER);
	}
	return RUN_OK;
}







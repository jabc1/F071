#include "Function.h"
#include "Debugprintf.h"


typedef struct{
	u8 *head;
	u8 *headdata;
	u8 *id;
	u8 *iddata;
	u8 *inv;
	u8 *invdata;
	u8 *alarm;
	u8 *alarmdata;
}_Cmd;

struct attr_exe_data
{
	u8 *cmd;//��������
	void (*exe_attr)(u8 *,u8 *);//����ִ�в���
};

RunStatus test_1(u8 *cmd,u8 *data)
{
	return RUN_OK;
}









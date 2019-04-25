#ifndef _debugprintf_h
#define _debugprintf_h
#include "arm_base_define.h"
#include "SysUart.h"

void printf_232(const char *format, ...);
void printf_wifi(const char *format, ...);
void pack_printf(u8 *data,u16 len);
#endif

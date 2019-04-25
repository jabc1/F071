#include "Memory.h"

FIFO_t TagCacheFifo;
u8 TagCacheBuf[TagCacheLen];

FIFO_t TagFifo;
u8 TagBuf[TagLen];

FIFO_t WifiFifo;
u8 WifiBuf[WifiLen];

void Init_memory()
{
	fifo_init(&TagCacheFifo,TagCacheBuf,TagCacheLen);
	fifo_init(&TagFifo,TagBuf,TagLen);
	fifo_init(&WifiFifo,WifiBuf,WifiLen);
}










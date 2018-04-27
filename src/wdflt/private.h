#ifndef _WDFLT_PRIVATE_H_
#define _WDFLT_PRIVATE_H_

#pragma once


#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>

#pragma prefast(disable:__WARNING_ENCODE_MEMBER_FUNCTION_POINTER, "Not valid for kernel mode drivers")


extern ULONG gTraceFlags = 0;



#define PTDBG_TRACE_ROUTINES            0x00000001
#define PTDBG_TRACE_OPERATION_STATUS    0x00000002




extern ULONG g_ulLogLevel;

#define LOG_FATAL		0x00
#define LOG_ERROR		0x01
#define LOG_WARNING		0x02
#define LOG_INFO		0x03
#define LOG_DEBUG		0x04

#if DBG

#define WDFLT_DbgPrint(loglevel, _x_)		\
		do										\
		{										\
			if (loglevel <= g_ulLogLevel)		\
			{									\
				DbgPrint("Wdflt: ");			\
				DbgPrint _x_ ;					\
				DbgPrint("\n");					\
			}									\
		} while (0);

#else

#define MyDriver_DbgPrint(loglevel, _x_)

#endif






#endif /* _WDFLT_PRIVATE_H_ */
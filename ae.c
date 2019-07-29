
#ifdef DEBUG
	#include <stdio.h>
	#define xprintf(fmt, ...)	printf("FILE:<%s>,FUN:<%s>,LINE:<%d>,"fmt"\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
	#define xprintf(fmt, ...)
#endif

/* assert宏, assert失败时打印表达式 */
#define xassert(X) 		if(!(X)){										\
								xprintf(" (%s) assert fail!", #X);		\
								assert(0);								\
							}

#define zmalloc malloc

typedef enum
{
	AE_SUCC,
	AE_FAIL,
	AE_ERR,
}ae_status;

/**************************
windows通常不使用文件描述符
**************************/
#ifdef __linux_

#include <fcntl.h>
#include <unistd.h>

ae_status set_fl(int fd, int flags)
{
	int val = 0;

	if(fd < 0 || flags < 0)
	{
		return AE_ERR;
	}

	if(-1 == (val = fcntl(fd, F_GETFL, 0)))
	{
		return AE_ERR;
	}

	val |= flags;

	if(-1 == fcntl(fd, F_SETFL, val))
	{
		return AE_ERR;
	}

	return AE_SUCC;
}

ae_status clr_fl(int fd, int flags)
{
		int val = 0;

	if(fd < 0 || flags < 0)
	{
		return AE_ERR;
	}

	if(-1 == (val = fcntl(fd, F_GETFL, 0)))
	{
		return AE_ERR;
	}

	val &= ~flags;

	if(-1 == fcntl(fd, F_SETFL, val))
	{
		return AE_ERR;
	}

	return AE_SUCC;
}

#endif
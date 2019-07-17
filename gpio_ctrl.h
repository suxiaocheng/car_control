#ifndef __GPIO_CTRL_H__
#define __GPIO_CTRL_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <sys/param.h>
#include <stdint.h>
#include <pthread.h>
#include <microhttpd.h>

#include "debug.h"

enum mode_t {
	MODE_TRUN_LEFT,
	MODE_ACCERATE,
	MODE_TRUN_RIGHT,
	MODE_STOP,
	MODE_BACKWARD,
	MODE_MAX
};

#define GPIO_LEFT_FRONT_FORWARD    0x8
#define GPIO_LEFT_FRONT_BACKWARD   0x9

#define GPIO_RIGHT_FRONT_FORWARD   0x4
#define GPIO_RIGHT_FRONT_BACKWARD  0x5

#define GPIO_LEFT_BACK_FORWARD    0x2
#define GPIO_LEFT_BACK_BACKWARD   0x3

#define GPIO_RIGHT_BACK_FORWARD   0x1
#define GPIO_RIGHT_BACK_BACKWARD  0x0

int init_gpio(void);
int set_mode(int mode);

#endif //__GPIO_CTRL_H__

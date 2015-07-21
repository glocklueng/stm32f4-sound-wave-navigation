#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <stdint.h>

typedef struct{
	float x;
	float y;
}Point;

extern Point pos;

void control_process(void);


#endif


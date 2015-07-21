#ifndef __LOCATION_H__
#define __LOCATION_H__

typedef struct{
	float x;
	float y;
}Point;

extern float delta_t1; //Ta-Tc
extern float delta_t2; //Tb-Ta
extern Point pos;

Point calc_position(float t1, float t2);

#endif

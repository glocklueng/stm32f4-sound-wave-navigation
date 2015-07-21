#include "location.h"
#include <math.h>
#include "util.h"

float delta_t1 = 0; //Ta-Tc
float delta_t2 = 0; //Tb-Ta

Point pos;

#define EQUAL_ZERO	0.00001f
#define VOICE_SPEED 340

Point calc_position(float t1, float t2)
{
	Point res;
	float a, b, c, w, m, n;
	
	if(fabs(t2) < EQUAL_ZERO){		//Ta == Tb
		a = 4*pow2(VOICE_SPEED*t1)-4;
		b = 4*pow3(VOICE_SPEED*t1)-4*VOICE_SPEED*t1;
		c = pow4(VOICE_SPEED*t1)-2*pow2(VOICE_SPEED*t1)+2;
		w = (-b-sqrt(pow2(b)-4*a*c))/(2*a);
		res.x = 0.5f;
		res.y = sqrt(fabs(pow2(w)-0.25f));
		return res;
	}
	
	m = -t1/t2;
	n = (1-pow2(VOICE_SPEED)*t1*t2)*(t1+t2)/(2*t2);
	a = 4*pow2(VOICE_SPEED*t2)*(1+pow2(m))-4;
	b = 8*m*n*pow2(VOICE_SPEED*t2)-4*pow2(VOICE_SPEED*t2)+4;
	c = 4*pow2(n*VOICE_SPEED*t2);
	
	if(t2 > 0){			//Tb>Ta
		res.x = (-b-sqrt(pow2(b)-4*a*c))/(2*a);
		res.y = m*res.x+n;
	}
	else if(t2 < 0){	//Tb<Ta
		res.x = (-b+sqrt(pow2(b)-4*a*c))/(2*a);
		res.y = m*res.x+n;
	}
	return res;
}


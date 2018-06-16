#pragma once

#include "headers.h"


/* some math.h files don't define pi... */
#ifndef M_PI
#define M_PI 3.141592653
#endif

#define RAD(x) (((x)*M_PI)/180.)

#ifdef __STRICT_ANSI__
#define sinf(x) ((float)sin((x)))
#define cosf(x) ((float)cos((x)))
#define atan2f(x, y) ((float)atan2((x), (y)))
#endif 


typedef enum sphereType { PLANET, MOON, STAR } sphereType;

int getCountOfNamesContainingString(std::string folder, std::string name);
void keepFloatBelow360(float *angle);
float fillStar(struct star &s, float posMin, float posMax);
void getRandomVectorWithLength(float length, float *vec);
float randomFloatBetween(float lo, float hi);
int randomIntBetween(int lo, int hi);
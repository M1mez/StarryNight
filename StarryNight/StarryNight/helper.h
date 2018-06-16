#pragma once

#include <sstream>
#include <string>
#include <iostream>
#include <filesystem>

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
typedef enum cubeSide { RIGHT, LEFT, TOP, BOTTOM, FRONT, BACK } cubeSide;

int getCountOfNamesContainingString(std::string folder, std::string name);
void keepFloatBelow360(float *angle);
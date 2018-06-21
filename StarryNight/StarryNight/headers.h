#pragma once

#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <cstdlib> // for exit
#include <Windows.h>
#include <cstdio>
#include <ctime>
#include <string>
#include <cstring>


#include <cmath>
#include <iostream>
#include "helper.h"
#include "tga.h"
#include <sstream>
#include <filesystem>
#include <gl\GL.h>
#include <gl\GLU.h>
#include "glut.h"


struct star {
	GLUquadricObj *starObj;
	float size;
	float vec[3];
	int shrinking = 1;
	float shrinkSpeed;
	float maxSize;
};

#endif

#pragma once

#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <cstdlib> // for exit
#include <windows.h>
#include <cstdio>
#include <string>
#include <cstring>
#include <cmath>
#include <ctime>
#include <iostream>
#include "helper.h"
#include "tga.h"
#include <sstream>
#include <filesystem>
#include "glut.h"
#include <GL/gl.h>  
#include <GL/glu.h> 

struct star {
	GLUquadricObj *starObj;
	float size;
	float vec[3];
};

#endif

#pragma once

#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED

#include <cstdlib> // for exit
#include <Windows.h>
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
#include <gl\GL.h>
#include <gl\GLU.h>


struct star {
	GLUquadricObj *starObj;
	float size;
	float vec[3];
};

#endif

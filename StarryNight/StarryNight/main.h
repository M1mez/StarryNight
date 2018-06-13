#pragma once

#include <stdlib.h> // for exit
#include <stdio.h>
#include <string>
#include <cstring>

#include <glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h> 
#include "tga.h"
#include <math.h>

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

int window;
float advanceByKey = 0.0f;
GLuint texture[6];
GLuint singleTexture;
int animating = 1;

int moving = 0;     /* flag that is true while mouse moves */
int begin_x = 0;        /* x value of mouse movement */
int begin_y = 0;      /* y value of mouse movement */
GLfloat angle_y = 0;  /* angle of spin around y axis of scene, in degrees */
GLfloat angle_x = 0;  /* angle of spin around x axis  of scene, in degrees */




void resize(int width, int height);
void keyPressed(unsigned char key, int x, int y);
void specialKeyPressed(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void display(void);
void init(int width, int height);
void timer(int value);


#pragma once

#include "helper.h"

#include <cstdlib> // for exit
#include <cstdio>
#include <string>
#include <cstring>

#include <glut.h> 
#include <GL/gl.h>  
#include <GL/glu.h> 
#include "tga.h"
#include <cmath>
#include <ctime>

using namespace std;

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
int window;



// variables needing set
int cubeMapTexture = 1;
int wantFullScreen = 0;
int insideSkyBox = 1;
float skyBoxEdgeLength = 50.0f;
string skyboxFolder = "skyboxes/";
string sphereFolder = "spheres/";

string singleCubeTga = "crate.tga";

// self setting variables
int amountOfCubemaps;
float StarSpawnMaxRadius = (skyBoxEdgeLength / 2);
float StarSpawnMinRadius = StarSpawnMaxRadius - skyBoxEdgeLength * 2;

int animating = 1;
float hour = 0.0;
float day = 0.0;
float inc = 0.005;

// skybox
GLuint skyboxSideTextures[6];
GLuint skyboxSingleTexture;
string skyboxString = "starfield";

// planet
GLUquadricObj *planet;
float planetRadius = skyBoxEdgeLength / 6; //fifth of skybox, radius is half that
GLuint planetTexture;
string planetTga = "earthColour.tga";

// moon
GLUquadricObj *moon;
float moonRadius = planetRadius / 3.7;
GLuint moonTexture;
string moonTga = "moonLight.tga";

// player
float playerPosX = 0.0f;
float playerPosZ = 0.0f;
float playerPosY = planetRadius + 2;

float playerSpeed = skyBoxEdgeLength / 50;
int leftPressed = 0;     /* flag that is true while mouse moves */
int begin_x = 0;        /* x value of mouse movement */
int begin_y = 0;      /* y value of mouse movement */
GLfloat angle_x = 0;  /* angle of spin around x axis  of scene, in degrees */
GLfloat angle_y = 0;  /* angle of spin around y axis of scene, in degrees */

// forward declaration
void resize(int width, int height);
void keyPressed(unsigned char key, int x, int y);
void specialKeyPressed(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void display(void);
void init(int width, int height);
void timer(int value);


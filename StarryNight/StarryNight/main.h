#pragma once


#include "headers.h"




using namespace std;


int window;

// variables needing set
int playerShouldMove = 0;
int cubeMapTexture = 1;
int wantFullScreen = 0;
int insideSkyBox = 1;
float skyBoxEdgeLength = 500.0f;
string skyboxFolder = "skyboxes/";
string sphereFolder = "spheres/";

string singleCubeTga = "crate.tga";

// self setting variables
int amountOfCubemaps;
float starSpawnMaxRadius = (skyBoxEdgeLength / 2);
float starSpawnMinRadius = starSpawnMaxRadius - 10;

//int animating = 1;
float hour = 0.0;
float day = 0.0;
float inc = 0.05;

// skybox
GLuint skyboxSideTextures[6];
GLuint skyboxSingleTexture;
string skyboxString = "starfield";

// planet
GLUquadricObj *planet;
float planetRadius = skyBoxEdgeLength / 6;
GLuint planetTexture;
string planetTga = "earthColour.tga";
GLfloat earthpos[] = { 0,-(planetRadius + 2),0 };
GLfloat planetcolors[] = { 1,1,1,1 };

// moon
GLUquadricObj *moon;
float moonRadius = planetRadius / 8;
GLuint moonTexture;
string moonTga = "moonLight.tga";
GLfloat moonpos[] = { (planetRadius * 2),0,0,1 };
GLfloat mooncolors[] = { 1,1,1,1 };

// sun
GLUquadricObj *sun;
float sunRadius = planetRadius / 3;
GLuint sunTexture;
string sunTga = "sun.tga";
GLfloat sunpos[] = { (planetRadius * 3),0,0,1 };
GLfloat suncolors[] = { 1,1,1,1 };

// star
const int starCount = 150;
struct star stars[starCount];
GLfloat starcolors[] = { 1.0f,1.0f,0.2f,1.0f };
float shrinkSpeed = 0.2f;

// player
float playerPosX = 0.0f;
float playerPosZ = 0.0f;
float playerPosY = planetRadius + 2;

// world
float pitch = 0.0f;
float yaw = 0.0f;
float roll = 0.0f;

float pitchChange = 0;
float yawChange = 0;
float rollChange = 0;

GLfloat whitelight[] = { 1,1,1,1 };
GLfloat blacklight[] = { 0,0,0,1 };
GLfloat attenuation[] = { planetRadius / 100 };

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
void LoadTextures();


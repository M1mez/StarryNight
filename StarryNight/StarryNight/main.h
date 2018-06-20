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

int animating = 1;
float hour = 0.0;
float day = 0.0;
float inc = 0.05;

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

// star
const int starCount = 75;
struct star stars[starCount];


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


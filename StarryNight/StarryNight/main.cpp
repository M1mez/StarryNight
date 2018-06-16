#include "main.h"
#include <iostream>

#define GL_CLAMP_TO_EDGE 0x812F


int main(int argc, char **argv)
{
	srand(time(nullptr));
	amountOfCubemaps = getCountOfNamesContainingString(skyboxFolder, skyboxString);
	skyboxString += char('0' + rand() % amountOfCubemaps + 1);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(1280, 960);
	glutInitWindowPosition(GLUT_SCREEN_HEIGHT, GLUT_SCREEN_WIDTH);
	window = glutCreateWindow("Starry Night");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(&specialKeyPressed);
	init(1280, 960);
	glutTimerFunc(15, timer, 1);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	if (wantFullScreen) glutFullScreen();
	glutMainLoop();
	return 0;
}

void reportGLError(const char * msg)
{
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		fprintf(stderr, "OpenGL Error: %s %p\n", msg, errString);
	}
	return;
}

void resize(int width, int height)
{
	// prevent division by zero
	if (height == 0) { height = 1; }

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
}

#pragma region keyPressed
void specialKeyPressed(int key, int x, int y)
{
	//float pitchedX = pitch + angle_y;

	//float sxp = sinf(RAD(angle_y));
	//float syp = 1;//sinf(RAD(1));
	//float cxp = cosf(RAD(angle_y));
	//float cyp = 1;


	float yrotrad = RAD(angle_y);
	cout << "sin: " << sinf(yrotrad) << " cos: " << cosf(yrotrad) << endl;

	keepFloatBelow360(&pitch);
	keepFloatBelow360(&yaw);
	keepFloatBelow360(&roll);

	switch (key) {

	case GLUT_KEY_UP:
		if (playerShouldMove)
		{
			playerPosX -= sinf(yrotrad) * playerSpeed / 10;
			playerPosZ += cosf(yrotrad) * playerSpeed / 10;
		}
		else
		{
			pitch += cosf(yrotrad);
			//yaw += sinf(yrotrad);
			roll += sinf(yrotrad);
/*
			pitch -= cxp * -syp;
			yaw += sxp;
			roll -= cxp * -cyp;*/

		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		if (playerShouldMove)
		{
			playerPosX += sinf(yrotrad) * playerSpeed / 10;
			playerPosZ -= cosf(yrotrad) * playerSpeed / 10;
		}
		else
		{

		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		if (playerShouldMove)
		{
			playerPosX -= cosf(yrotrad) * playerSpeed / 25;
			playerPosZ -= sinf(yrotrad) * playerSpeed / 25;
		}
		else
		{

		}
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		if (playerShouldMove)
		{
			playerPosX += cosf(yrotrad) * playerSpeed / 25;
			playerPosZ += sinf(yrotrad) * playerSpeed / 25;
		}
		else
		{

		}
		glutPostRedisplay();
		break;
	default: break;
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
	case 'W':
	{
		specialKeyPressed(GLUT_KEY_UP, x, y);
		break;
	}
	case 's':
	case 'S':
	{
		specialKeyPressed(GLUT_KEY_DOWN, x, y);
		break;
	}
	case 'a':
	case 'A':
	{
		specialKeyPressed(GLUT_KEY_LEFT, x, y);
		break;
	}
	case 'd':
	case 'D':
	{
		specialKeyPressed(GLUT_KEY_RIGHT, x, y);
		break;
	}
	case 'r':
	case 'R':
		playerPosX = 0.0f;
		playerPosZ = 0.0f;
		playerPosY = planetRadius;
		angle_x = 0;
		angle_y = 0;
		yaw = 0;
		roll = 0;
		pitch = 0;
		break;
	case 27:
		glutDestroyWindow(window);
		exit(0);
		break;
	case 'q':
		animating = animating ? 0 : 1;
		glutPostRedisplay();
		break;
	case '+':
		inc += 0.005;
		break;
	case '-':
		inc -= 0.005;
		break;
	default:
		break;
	}
}
#pragma endregion

#pragma region mouse
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			leftPressed = 1;
			begin_x = x;
			begin_y = y;

		}
		else if (state == GLUT_UP) {
			leftPressed = 0;
			cout << angle_x << "<- x y -> " << angle_y << endl;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			//TODO shooting star appears
		}
		else if (state == GLUT_UP)
		{
			//TODO shooting star fades out, or nothing
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}
void mouseMotion(int x, int y) {

	cout << "x: " << angle_x << " y: " << angle_y << endl;
	if (leftPressed) {
		angle_y = angle_y + (x - begin_x);
		float newAngle = angle_x + (y - begin_y);
		if (newAngle >= 90)
		{
			begin_x = x;
			begin_y = y;
			return;
		}
		if (newAngle <= -90)
		{
			begin_x = x;
			begin_y = y;
			return;
		}
		angle_x = newAngle;
		keepFloatBelow360(&angle_x);
		keepFloatBelow360(&angle_y);

		begin_x = x;
		begin_y = y;

		glutPostRedisplay();
	}
}
#pragma endregion

#pragma region draw
void drawSphere(sphereType type)
{
	GLUquadricObj *sphere = nullptr;
	int radius = 0;
	GLuint texture = 0;

	switch (type)
	{
	case PLANET:
		sphere = planet;
		radius = planetRadius;
		texture = planetTexture;
		break;
	case MOON:
		sphere = moon;
		radius = moonRadius;
		texture = moonTexture;
		break;
	case STAR:

		break;
	default: break;
	}

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBegin(GL_QUADS);

	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, 1);
	gluSphere(sphere, radius, 50, 50);

	glEnd();
	glDisable(GL_TEXTURE_2D);
}
void drawSkyBox()
{
	int textureCount = 0;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	if (cubeMapTexture) glBindTexture(GL_TEXTURE_2D, skyboxSideTextures[textureCount++]);
	else glBindTexture(GL_TEXTURE_2D, skyboxSingleTexture);

	glBegin(GL_QUADS);
	// front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-skyBoxEdgeLength, -skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(skyBoxEdgeLength, -skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(skyBoxEdgeLength, skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-skyBoxEdgeLength, skyBoxEdgeLength, skyBoxEdgeLength);

	if (cubeMapTexture) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, skyboxSideTextures[textureCount++]);
		glBegin(GL_QUADS);
	}

	// back face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyBoxEdgeLength, -skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-skyBoxEdgeLength, skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(skyBoxEdgeLength, skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(skyBoxEdgeLength, -skyBoxEdgeLength, -skyBoxEdgeLength);

	if (cubeMapTexture) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, skyboxSideTextures[textureCount++]);
		glBegin(GL_QUADS);
	}

	// top face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-skyBoxEdgeLength, skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-skyBoxEdgeLength, skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(skyBoxEdgeLength, skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(skyBoxEdgeLength, skyBoxEdgeLength, -skyBoxEdgeLength);

	if (cubeMapTexture) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, skyboxSideTextures[textureCount++]);
		glBegin(GL_QUADS);
	}

	// bottom face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyBoxEdgeLength, -skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(skyBoxEdgeLength, -skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(skyBoxEdgeLength, -skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-skyBoxEdgeLength, -skyBoxEdgeLength, skyBoxEdgeLength);

	if (cubeMapTexture) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, skyboxSideTextures[textureCount++]);
		glBegin(GL_QUADS);
	}

	// right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(skyBoxEdgeLength, -skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(skyBoxEdgeLength, skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(skyBoxEdgeLength, skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(skyBoxEdgeLength, -skyBoxEdgeLength, skyBoxEdgeLength);

	if (cubeMapTexture) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, skyboxSideTextures[textureCount++]);
		glBegin(GL_QUADS);
	}

	// left face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-skyBoxEdgeLength, -skyBoxEdgeLength, -skyBoxEdgeLength);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-skyBoxEdgeLength, -skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-skyBoxEdgeLength, skyBoxEdgeLength, skyBoxEdgeLength);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-skyBoxEdgeLength, skyBoxEdgeLength, -skyBoxEdgeLength);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
#pragma endregion

#pragma region display
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	hour += inc;
	day += inc / 24.0;
	hour = hour - int(hour / 360) * 360;
	day = day - int(day / 365) * 365;

	gluLookAt(-sinf(RAD(angle_y)), sinf(RAD(angle_x)), cosf(RAD(angle_y)),
		0., 0., 0.,
		0., 1., 0.);

	/*glRotatef(angle_y, 0, 1, 0);
	glRotatef(angle_x, 1, 0, 0);*/

	glTranslatef(0, -(planetRadius + 2), 0);


	glRotatef(yaw, 0.0f, 1.0f, 0.0f);
	glRotatef(pitch, 1.0f, 0.0f, 0.0f);
	glRotatef(roll, 0.0f, 0.0f, 1.0f);


	/*glTranslatef(0, -playerPosY, 0);
	if (playerShouldMove)
	{
		glTranslatef(playerPosX, 0, playerPosZ);
	}
	else
	{

		glRotatef(pitch, 1, 0, 0);
		glRotatef(roll, 0, 0, 1);
	}*/

	//planet position only changes if player moves (everything else as well)
	//glPushMatrix();
	drawSphere(PLANET);
	//glPopMatrix();

	// skybox rotates around planet
	glPushMatrix();
	glRotatef(360 * hour / 360, 0.0, 1.0, 0.0);
	//gluPerspective(45.0f, 20, 0.5f, 300.0f);
	drawSkyBox();
	glPopMatrix();

	//Moon
	glPushMatrix();
	float moonRot = 360.0 * day / 2;
	glRotatef(moonRot, 0, 1, 0);
	glTranslatef((planetRadius * 5), 0, 0);
	//glRotatef(-moonRot, 0, 1, 0);
	//glTranslatef(sinf(moonRot / 12) * (planetRadius * 5), 0, cosf(moonRot / 12) * (planetRadius * 5));

	//glRotatef(moonRot, 0.0, 1.0, 0.0);
	drawSphere(MOON);

	glPopMatrix();


	glutSwapBuffers();
}
#pragma endregion

#pragma region init
void init(int width, int height)
{
	planet = gluNewQuadric();
	moon = gluNewQuadric();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	resize(width, height);

	GLint format;
	GLsizei w, h;
	tgaInfo *info = 0;
	int mode;

#pragma region skyBox
	if (cubeMapTexture) {
		for (int i = 0; i < 6; i++)
		{
			info = tgaFromFolder(skyboxString.c_str(), insideSkyBox, cubeSide(i), skyboxFolder);

			if (info->status != TGA_OK) {
				fprintf(stderr, "error loading texture image: %d\n", info->status);

				return;
			}
			if (info->width != info->height) {
				fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
					info->width, info->height);
				return;
			}

			mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
			glGenTextures(1, &skyboxSideTextures[i]);

			//glPixelStorei(GL_PACK_ALIGNMENT, 1);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glBindTexture(GL_TEXTURE_2D, skyboxSideTextures[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

			// Upload the texture bitmap. 
			w = info->width;
			h = info->height;

			reportGLError("before uploading texture");
			format = (mode == 4) ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
				GL_UNSIGNED_BYTE, info->imageData);
			reportGLError("after uploading texture");

			tgaDestroy(info);
		}
	}
	else {
		info = tgaLoad(singleCubeTga.c_str());

		if (info->status != TGA_OK) {
			fprintf(stderr, "error loading texture image: %d\n", info->status);

			return;
		}
		if (info->width != info->height) {
			fprintf(stderr, "Image size %d x %d is not rectangular, giving up.\n",
				info->width, info->height);
			return;
		}

		mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
		glGenTextures(1, &skyboxSingleTexture);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, skyboxSingleTexture);
		//TODO WHERE IS GL_CLAMP_TO_BORDER????
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

		// Upload the texture bitmap. 
		w = info->width;
		h = info->height;

		reportGLError("before uploading texture");
		format = (mode == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
			GL_UNSIGNED_BYTE, info->imageData);
		reportGLError("after uploading texture");

		tgaDestroy(info);
	}
#pragma endregion 

#pragma region planet
	info = tgaLoad((sphereFolder + planetTga).c_str());

	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status);

		return;
	}

	mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
	glGenTextures(1, &planetTexture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, planetTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Upload the texture bitmap. 
	w = info->width;
	h = info->height;

	reportGLError("before uploading texture");
	format = (mode == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
		GL_UNSIGNED_BYTE, info->imageData);
	reportGLError("after uploading texture");

	tgaDestroy(info);
#pragma endregion

#pragma region moon
	info = tgaLoad((sphereFolder + moonTga).c_str());

	if (info->status != TGA_OK) {
		fprintf(stderr, "error loading texture image: %d\n", info->status);

		return;
	}

	mode = info->pixelDepth / 8;  // will be 3 for rgb, 4 for rgba
	glGenTextures(1, &moonTexture);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, moonTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Upload the texture bitmap. 
	w = info->width;
	h = info->height;

	reportGLError("before uploading texture");
	format = (mode == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
		GL_UNSIGNED_BYTE, info->imageData);
	reportGLError("after uploading texture");

	tgaDestroy(info);
#pragma endregion

}

#pragma endregion

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 1);
}


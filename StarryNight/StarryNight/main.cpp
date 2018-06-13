#include "main.h"

using namespace std;

string skybox = "glacier";
string singleTga = "crate.tga";
int wantSkybox = 1;
int wantFullScreen = 0;
int insideSkyBox = 1;

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(0, 0);
	window = glutCreateWindow("Starry Night");
	glutDisplayFunc(&display);
	glutReshapeFunc(&resize);
	glutKeyboardFunc(&keyPressed);
	glutSpecialFunc(&specialKeyPressed);
	init(640, 480);
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
		fprintf(stderr, "OpenGL Error: %s %s\n", msg, errString);
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
	switch (key) {

	case GLUT_KEY_UP:     /* <cursor up> */
		advanceByKey += 0.1f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:     /* <cursor down> */
		advanceByKey -= 0.1f;
		glutPostRedisplay();
		break;
	}
}

void keyPressed(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutDestroyWindow(window);
		exit(0);
		break;
	case 'a':
		animating = animating ? 0 : 1;
		glutPostRedisplay();
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
	case GLUT_LEFT_BUTTON:    /* spin scene around */
		if (state == GLUT_DOWN) {
			moving = 1;
			begin_x = x;
			begin_y = y;

		}
		else if (state == GLUT_UP) {
			moving = 0;
		}
		break;

	default:
		break;
	}

	glutPostRedisplay();
}


void mouseMotion(int x, int y) {

	if (moving) { /* mouse button is pressed */

				  /* calculate new modelview matrix values */
		angle_y = angle_y + (x - begin_x);
		angle_x = angle_x + (y - begin_y);
		if (angle_x > 360.0) angle_x -= 360.0;
		else if (angle_x < -360.0) angle_x += 360.0;
		if (angle_y > 360.0) angle_y -= 360.0;
		else if (angle_y < -360.0) angle_y += 360.0;

		begin_x = x;
		begin_y = y;
		glutPostRedisplay();
	}
}
#pragma endregion

#pragma region draw
void drawCube()
{
	int textureCount = 0;
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	if (wantSkybox) glBindTexture(GL_TEXTURE_2D, texture[textureCount++]);
	else glBindTexture(GL_TEXTURE_2D, singleTexture);

	glBegin(GL_QUADS);
	// front face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);

	if (wantSkybox) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[textureCount++]);
		glBegin(GL_QUADS);
	}

	// back face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);

	if (wantSkybox) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[textureCount++]);
		glBegin(GL_QUADS);
	}

	// top face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f);

	if (wantSkybox) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[textureCount++]);
		glBegin(GL_QUADS);
	}

	// bottom face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);

	if (wantSkybox) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[textureCount++]);
		glBegin(GL_QUADS);
	}

	// right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	if (wantSkybox) {
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[textureCount++]);
		glBegin(GL_QUADS);
	}

	// left face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
#pragma endregion

#pragma region display
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	gluLookAt(-sinf(RAD(angle_y)), sinf(RAD(angle_x)), cosf(RAD(angle_y)),
		0., 0., 0.,
		0., 1., 0.);


	glTranslatef(0, 0, -advanceByKey);

	glPushMatrix();
	drawCube();
	glPopMatrix();


	glutSwapBuffers();
}
#pragma endregion

#pragma region init
void init(int width, int height)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	resize(width, height);

	GLsizei w, h;
	tgaInfo *info = 0;
	int mode;

	if (wantSkybox) {
		for (int i = 0; i < 6; i++)
		{
			info = tgaFromFolder(skybox.c_str(), insideSkyBox, cubeSide(i));

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
			glGenTextures(1, &texture[i]);

			//glPixelStorei(GL_PACK_ALIGNMENT, 1);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

			// Upload the texture bitmap. 
			w = info->width;
			h = info->height;

			reportGLError("before uploading texture");
			GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
				GL_UNSIGNED_BYTE, info->imageData);
			reportGLError("after uploading texture");

			tgaDestroy(info);
		}
	}
	else {
		info = tgaLoad(singleTga.c_str());

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
		glGenTextures(1, &singleTexture);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, singleTexture);
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
		GLint format = (mode == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format,
			GL_UNSIGNED_BYTE, info->imageData);
		reportGLError("after uploading texture");

		tgaDestroy(info);
	}
}

#pragma endregion

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(15, timer, 1);
}



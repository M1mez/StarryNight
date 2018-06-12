#include "ofApp.h"

#ifndef M_PI
#define M_PI 3.141592653
#endif
#define RAD(x) (((x)*M_PI)/180.)

enum {LEFT, WHEEL, RIGHT};

#pragma region ShootingStar
int shootingStarX;
int shootingStarY;
int shootingStarRadius = 50;
bool shootingStarVisible = false;
bool shootingStarDirectionSet = false;

void ResetShootingStar() {
	shootingStarX = 0;
	shootingStarY = 0;
	int shootingStarRadius = 50;
	shootingStarVisible = false;
	shootingStarDirectionSet = false;
}
#pragma endregion

//--------------------------------------------------------------
void ofApp::setup() {
	SkyDome.setRadius(100);
}

void resize(int width, int height)
{

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	if (shootingStarVisible) {
		ofDrawSphere(shootingStarX, shootingStarY, shootingStarRadius);
	}

}

void drawSphereTime(int xPos, int yPos, int time = 5) {
	ofDrawSphere(xPos, yPos, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	shootingStarX = x;
	shootingStarY = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	switch (button)
	{
	case LEFT: {
		shootingStarX = x;
		shootingStarY = y;
		shootingStarVisible = true;
		break;
	}
	case WHEEL: {

		cout << "WHEEL!" << endl;
		break;
	}
	case RIGHT: {

		cout << "RIGHT!" << endl;
		break;
	}
	default: break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	shootingStarVisible = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}


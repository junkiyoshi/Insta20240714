#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 7);
	this->mesh = ico_sphere.getMesh();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clearColors();
	this->noise_param = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.035), 0, 1, 0.0005, 0.02);
	this->noise_param = 0.0015;

	ofColor color;
	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		auto noise_value = ofMap(ofNoise(
			this->mesh.getVertex(i).x * this->noise_param,
			this->mesh.getVertex(i).y * this->noise_param,
			this->mesh.getVertex(i).z * this->noise_param,
			ofGetFrameNum() * 0.015), 0, 1, 0, 10);
		int int_noise_value = (int)noise_value;

		int hue = ofMap(noise_value, 0, 10, 0, 512);
		hue = hue % 256;

		noise_value = noise_value - int_noise_value;
		auto alpha = 0.f;
		if (abs(noise_value - 0.5) > 0.30) {

			if (abs(noise_value - 0.5) > 0.4) {

				alpha = 255;
			}
			else {

				alpha = ofMap(abs(noise_value - 0.5), 0.30, 0.4, 0, 255);
			}
		}
		color = ofColor(0, alpha);
		this->mesh.addColor(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(-27);

	this->mesh.drawFaces();

	this->cam.end();

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
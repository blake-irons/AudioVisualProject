#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	bg_image.load("sun.jpg");
	
	//icosphere
	icoRad = ofGetWidth() / 10;
	icoSphere.setRadius(icoRad);

	ofSetVerticalSync(true);
	soundStream.printDeviceList();

	int bufferSize = 256;

	left.assign(bufferSize, 0.0);
	right.assign(bufferSize, 0.0);
	

	smoothedVol = 0.0;
	scaledVol = 0.0;

	ofSoundStreamSettings settings;

	// 
	auto devices = soundStream.getMatchingDevices("default");
	if (!devices.empty()) {
		settings.setInDevice(devices[0]);
	}

	settings.setInListener(this);
	settings.sampleRate = 44100;
	settings.numOutputChannels = 0;
	settings.numInputChannels = 2;
	settings.bufferSize = bufferSize;
	soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
	//scale the vol up to a 0-1 range 
	scaledVol = ofMap(smoothedVol, 0.0, 0.17, 0.0, 1.0, true);
}

//--------------------------------------------------------------
void ofApp::draw(){
	float spinX = sin(ofGetElapsedTimef()*.35f);
	float spinY = cos(ofGetElapsedTimef()*.075f);
	float spinZ = sin(ofGetElapsedTimef()*.35f);

	//Background
	bg_image.draw(0, 0, ofGetWidth(), ofGetHeight());
	
ofPushStyle();
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2, 0);

	//Set up icosphere
	icoSphere.setRadius(scaledVol*30 + icoRad);
	icoSphere.setPosition(0, 0, 0);
	icoSphere.rotateDeg(spinX * scaledVol * 2.0f, 1.0, 0.0, 0.0);
	icoSphere.rotateDeg(spinY * scaledVol * 2.0f, 0, 1.0, 0.0);

	ofSetColor(24, 49, 240);


	//"star" particles are manually drawn. Particle class would be more ideal
	//Moving in 3D Orbit
	ofDrawSphere(spinX*(ofGetWidth()-20)/2 , -spinY*(ofGetHeight()-5.0)/2, spinZ * 10,scaledVol*12+10);
	ofDrawSphere(0.6*spinX*(ofGetWidth() - 5) / 3, 0.3*spinY*(ofGetHeight() - 5.0) / 3, spinZ * 14, scaledVol * 12 + 15);
	ofDrawSphere(-0.8*spinX*(ofGetWidth() - 5) / 2, 0.5*spinY*(ofGetHeight() - 5.0) / 3, spinZ * 20, scaledVol * 12 + 12);

	ofDrawSphere(.6*spinX*(ofGetWidth() - 20) / 2, -0.5*spinY * (ofGetHeight() - 5.0) / 2, spinZ * 12, scaledVol * 12 + 8);
	ofDrawSphere(-spinX*(ofGetWidth() - 5) / 2, 0.3*-spinY*(ofGetHeight() - 5.0) / 3, spinZ * 15, scaledVol * 12 + 11);
	ofDrawSphere(spinX*(ofGetWidth() - 5) / 3, -0.7*spinY*(ofGetHeight() - 5.0) / 2, spinZ * 5, scaledVol * 12 + 12);
	
	ofDrawSphere(-.6*spinX*(ofGetWidth() - 20) / 2, -0.5*spinY * (ofGetHeight() -40) / 2, spinZ * 9, scaledVol * 12 +12);
	ofDrawSphere(-spinX * (ofGetWidth() - 10) / 2, 0.3*spinY * (ofGetHeight() - 10) / 3, spinZ * 15, scaledVol * 12 + 13);
	ofDrawSphere(-0.2*spinX*(ofGetWidth() - 5) / 3, 0.9*spinY*(ofGetHeight() - 10) / 2, spinZ * 5, scaledVol * 12 + 10);

	//Draw IcoSphere
	ofSetColor(0, 0, 0);
	icoSphere.setScale(1.01f);
	ofSetLineWidth(3);
	icoSphere.drawWireframe();
	icoSphere.setScale(1.f);
	icoSphere.setResolution(1);

	//Instructions for user
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Scaled average vol (0-100): " + ofToString(scaledVol * 100.0, 0), -ofGetWidth()/2, ofGetHeight()/2-25);
	ofDrawBitmapString("Press w to increase icosphere radius, Press s to decrease", -ofGetWidth() / 2, ofGetHeight() / 2 - 15);
	ofDrawBitmapString("Press the escape key to exit", -ofGetWidth() / 2, ofGetHeight() / 2 - 5);
	
	ofPopMatrix();
ofPopStyle();
}

//Audio processing
void ofApp::audioIn(ofSoundBuffer & input) {

	float curVol = 0.0;

	// samples are "interleaved"
	int numCounted = 0;

	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume	
	for (size_t i = 0; i < input.getNumFrames(); i++) {
		left[i] = input[i * 2] * 0.5;
		right[i] = input[i * 2 + 1] * 0.5;

		curVol += left[i] * left[i];
		curVol += right[i] * right[i];
		numCounted += 2;
	}

	//this is how we get the mean of rms :) 
	curVol /= (float)numCounted;

	// this is how we get the root of rms :) 
	curVol = sqrt(curVol);

	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'w') {
		icoRad += 5;
	}
	if (key == 's') {
		icoRad -= 5;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

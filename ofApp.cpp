#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	beat.load("C:\\Temp\\beat.wav");

	durationInSeconds = beat.length / beat.internalFreq;
	ofSetBackgroundColor(0, 0, 0);
	// ofSetBackgroundAuto(false);

	// startTime = ofGetElapsedTimeMillis();

	fftSmooth = new float[8192];
	for (int i = 0; i < 8192; i++)
		fftSmooth[i] = 0;

	bands = 64;

	beat.setLoop(true);
	beat.setVolume(0.2);
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSoundUpdate();

	float * value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] *= 0.3f;
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	// ofSetColor(255);

	//for (int i = 0; i < bands; i++) {

	//	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, -(fftSmooth[i] * 150));
	//	// ofCircle(ofGetWidth() / 2, ofGetHeight() / 2, -(fftSmooth[i] * 150));
	//}

	float timer = ofGetElapsedTimeMillis() - startTime;

	ofDrawBitmapString("bands: " + ofToString(bands), 0, 10);
	ofDrawBitmapString("timer: " + ofToString(timer), 0, 20);

	for (int i = 0; i < bands; i++) {
		// ofSetColor(rand() % 256, rand() % 256, rand() % 256);
		ofDrawBitmapString("fftSmooth: " + ofToString(fftSmooth[i]), 0, 30);
		ofCircle(ofGetWidth() / 2, ofGetHeight() / 2, -(fftSmooth[i] * 150));
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		beat.play();
		startTime = ofGetElapsedTimeMillis();
		break;
	case '2':
		beat.stop();
		break;
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

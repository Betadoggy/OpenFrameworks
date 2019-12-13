#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "PlanetClass.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
	ofFmodSoundPlayer beat;
	ofxPanel gui;

	ofParameterGroup planetGroups;
	PlanetClass solar, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune;

	vector<int> px, py;

	float * fftSmooth;

	// 파일 이름 위치
	string fname;

	// 윈도우 창 중앙 좌표
	int ww, wh;

	int bands;

	bool flag;
};

#ifndef __PlanetClass__
#define __PlanetClass__

#include "ofMain.h"

class PlanetClass {
public:
	void setup();
	void update();
	void draw();

	ofParameterGroup planetGroup;
	ofParameter<float> rotateSpeed;
	ofParameter<float> posX;
	ofParameter<float> posY;
	ofParameter<float> size;

	ofParameter<int> red;
	ofParameter<int> green;
	ofParameter<int> blue;

	float rotation = 0.0;
};

#endif __PlanetClass__
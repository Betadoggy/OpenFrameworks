#include "PlanetClass.h"

void PlanetClass::setup() {
	planetGroup.add(rotateSpeed.set("speed", 0.0, 0.0, 9.0));
	planetGroup.add(posX.set("distance", 0, 0, 600));
	// planetGroup.add(posY.set("Y", 0, 0, 600));
	planetGroup.add(size.set("size", 100, 1, 100));

	//planetGroup.add(red.set("red", 255, 0, 255));
	//planetGroup.add(green.set("green", 255, 0, 255));
	//planetGroup.add(blue.set("blue", 255, 0.0, 255));
}

void PlanetClass::update() {
	rotation = ofGetElapsedTimef()*rotateSpeed*5;
}

void PlanetClass::draw() {
	ofSetColor(red, green, blue);
	ofRotate(rotation);
	ofCircle(posX, posY, size);
}

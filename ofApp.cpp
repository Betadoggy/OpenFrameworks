#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	// 파일 이름 위치
	fname = "beat.wav";

	beat.load(fname);

	flag = false;

	ofBackground(0);

	// 윈도우 중앙 좌표
	ww = ofGetWindowWidth(); 
	wh = ofGetWindowHeight();

	for (int i = 0; i < 40; i++) {
		px.push_back(rand() % ww);
		py.push_back(rand() % wh);
	}

	// 대역폭 계산
	fftSmooth = new float[8192];
	for (int i = 0; i < 8192; i++)
		fftSmooth[i] = 0;

	bands = 9;

	// 소리 설정
	beat.setLoop(true);
	beat.setVolume(0.2);

	// 행성 //
	solar.setup();
	solar.posX.set(ww / 2);
	solar.posY.set(wh / 2);
	solar.red.set(248);
	solar.green.set(226);
	solar.blue.set(125);
	// planetGroups.add(solar.planetGroup);

	mercury.setup();
	planetGroups.add(mercury.planetGroup);
	mercury.planetGroup.setName("mercury");
	mercury.rotateSpeed.set(4.8);
	mercury.posX.set(85);
	mercury.posY.set(85);
	mercury.size.set(5);
	mercury.red.set(183);
	mercury.green.set(179);
	mercury.blue.set(180);

	venus.setup();
	planetGroups.add(venus.planetGroup);
	venus.planetGroup.setName("venus");
	venus.rotateSpeed.set(3.5);
	venus.posX.set(100);
	venus.posY.set(100);
	venus.size.set(10);
	venus.red.set(220);
	venus.green.set(102);
	venus.blue.set(41);

	earth.setup();
	planetGroups.add(earth.planetGroup);
	earth.planetGroup.setName("earth");
	earth.rotateSpeed.set(3);
	earth.posX.set(130);
	earth.posY.set(130);

	earth.size.set(10);
	earth.red.set(69);
	earth.green.set(74);
	earth.blue.set(162);

	mars.setup();
	planetGroups.add(mars.planetGroup);
	mars.planetGroup.setName("mars");
	mars.rotateSpeed.set(2.4);
	mars.posX.set(145);
	mars.posY.set(145);
	mars.size.set(8);
	mars.red.set(247);
	mars.green.set(178);
	mars.blue.set(100);

	jupiter.setup();
	planetGroups.add(jupiter.planetGroup);
	jupiter.planetGroup.setName("jupiter");
	jupiter.rotateSpeed.set(1.3);
	jupiter.posX.set(200);
	jupiter.posY.set(200);

	jupiter.size.set(40);
	jupiter.red.set(162);
	jupiter.green.set(76);
	jupiter.blue.set(44);

	saturn.setup(); // sat
	planetGroups.add(saturn.planetGroup);
	saturn.planetGroup.setName("saturn");
	saturn.rotateSpeed.set(0.97);
	saturn.posX.set(245);
	saturn.posY.set(245);
	saturn.size.set(35);
	saturn.red.set(159);
	saturn.green.set(156);
	saturn.blue.set(117);

	uranus.setup(); // uranus
	planetGroups.add(uranus.planetGroup);
	uranus.planetGroup.setName("uranus");
	uranus.rotateSpeed.set(0.68);
	uranus.posX.set(280);
	uranus.posY.set(280);
	uranus.size.set(25);
	uranus.red.set(194);
	uranus.green.set(233);
	uranus.blue.set(236);

	neptune.setup(); // neptune
	planetGroups.add(neptune.planetGroup);
	neptune.planetGroup.setName("neptune");
	neptune.rotateSpeed.set(0.54);
	neptune.posX.set(310);
	neptune.posY.set(310);
	neptune.size.set(26);
	neptune.red.set(53);
	neptune.green.set(72);
	neptune.blue.set(187);

	// Gui setting
	gui.setup(planetGroups);
}

//--------------------------------------------------------------
void ofApp::update(){


	ofSoundUpdate();

	solar.update();
	mercury.update();
	venus.update();
	earth.update();
	mars.update();
	jupiter.update();
	saturn.update();
	uranus.update();
	neptune.update();

	// 고속 푸리에 변환 (Fast Fourier Transform)
	float * value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++) {
		fftSmooth[i] *= 0.96f;
		if (fftSmooth[i] < value[i]) {
			fftSmooth[i] = value[i];
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	// gui 그리기
	gui.draw();

	ofDrawBitmapString(fname, 1700, 20);

	ofDrawBitmapString("Press '1' to start music", 1700, 1050);
	ofDrawBitmapString("Press '2' to stop music", 1700, 1070);

	// 투명도 설정
	ofEnableAlphaBlending();
	for (int i = 0; i < 40; i++) {
		ofSetColor(255, 255, 255, fftSmooth[0] * 1200 + 30);
		ofDrawCircle(px[i], py[i], 1);
	}

	if (flag) {
		solar.size.set(fftSmooth[0] * 200 + 100);
		mercury.size.set(fftSmooth[1] * 500 + 5);
		venus.size.set(fftSmooth[2] * 500*2 + 10);
		earth.size.set(fftSmooth[3] * 500*2 + 10);
		mars.size.set(fftSmooth[4] * 500 * 1.3 + 8);
		jupiter.size.set(fftSmooth[5] * 500*8 + 40);
		saturn.size.set(fftSmooth[6] * 500*7 + 35);
		uranus.size.set(fftSmooth[7] * 500*5 + 25);
		neptune.size.set(fftSmooth[8] * 500*5 + 26);
	}
	else {

		mercury.posX.set(85);
		mercury.size.set(5);

		venus.posX.set(100);
		venus.size.set(10);

		earth.posX.set(130);
		earth.size.set(10);

		mars.posX.set(145);
		mars.size.set(8);

		jupiter.posX.set(200);
		jupiter.size.set(40);

		saturn.posX.set(245);
		saturn.size.set(35);

		uranus.posX.set(280);
		uranus.size.set(25);
		
		neptune.posX.set(310);
		neptune.size.set(26);
	}

	// 행성 그리기
	ofNoFill();

	solar.draw();

	ofTranslate(solar.posX, solar.posY);

	neptune.draw();
	ofDrawBitmapString("neptune", neptune.posX, neptune.posY + neptune.size);

	// ofTranslate(solar.posX, solar.posY);
	uranus.draw();
	ofDrawBitmapString("uranus", uranus.posX, uranus.posY + uranus.size);

	//ofTranslate(solar.posX, solar.posY);
	saturn.draw();
	ofDrawBitmapString("saturn", saturn.posX, saturn.posY + saturn.size);

	// ofTranslate(solar.posX, solar.posY);
	jupiter.draw();
	ofDrawBitmapString("jupiter", jupiter.posX, jupiter.posY + jupiter.size);

	//ofTranslate(solar.posX, solar.posY);
	mars.draw();
	ofDrawBitmapString("mars", mars.posX, mars.posY + mars.size);

	// ofTranslate(solar.posX, solar.posY);
	earth.draw();
	ofDrawBitmapString("earth", earth.posX, earth.posY + earth.size);

	// ofTranslate(solar.posX, solar.posY);
	venus.draw();
	ofDrawBitmapString("venus", venus.posX, venus.posY + venus.size);

	// ofTranslate(solar.posX, solar.posY);
	mercury.draw();
	ofDrawBitmapString("mercury", mercury.posX, mercury.posY + mercury.size);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case '1':
		beat.play();
		flag = true;
		break;
	case '2':
		beat.stop();
		flag = false;
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
	solar.posX.set(x);
	solar.posY.set(y);
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

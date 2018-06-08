
//
//  UI.cpp
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "UI.h"

UI::UI(){
    lowerTeeth.load("UI/lowerTeeth.png");
    upperTeeth.load("UI/upperTeeth.png");
	
	// close animation
	for (int i=0; i<N_CLOSE_IMGS; i++){
		string imgNum = ofToString(i);
		closeAnimation[i].load("UI/close_" + imgNum + ".png");
	}
	
	closeFrameDelay = 1.f / 24.f;
}

void UI::update(){

}

void UI::draw(){
	
	ofVec2f wS = ofVec2f(ofGetWidth(), ofGetHeight());
	float scaleFactor = wS.x/upperTeeth.getWidth();

	ofVec2f uP = ofVec2f(0, -50);
	ofVec2f uS = ofVec2f(wS.x, upperTeeth.getHeight() * scaleFactor);
	ofVec2f lP = ofVec2f(0, wS.y - lowerTeeth.getHeight() + 200);
	ofVec2f lS = ofVec2f(wS.x, lowerTeeth.getHeight() * scaleFactor);
	
	if (closeIndex < 0 || closeIndex >= N_CLOSE_IMGS){
		upperTeeth.draw(uP, uS.x, uS.y);
		lowerTeeth.draw(lP, lS.x, lS.y);
	}
	else {
		float t = ofGetElapsedTimef();
		if (t - closeFrameDelay >= tLastCloseFrame){
			tLastCloseFrame = t;
			if (++closeIndex >= N_CLOSE_IMGS){
				closeIndex = -1;
			}
		}
		if (closeIndex >= 0){
			auto& img = closeAnimation[closeIndex];
			img.draw(0,0, wS.x,img.getHeight() * scaleFactor);
		}
	}
}
			

/*
 void UI::loseDraw(int index){
 
 if (index >= MOUTHCLOSEIMAGES) {
 //reset
 index = 0;
 }
 
 closeAnimation[index].draw(0,0, ofGetWidth(),ofGetHeight());
 
 }
 */

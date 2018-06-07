
//
//  Background.cpp
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "Background.h"

Background::Background(){
    string index;
    for(int i =0; i< N_BG_IMGS; i++){
        index = ofToString(i);
        bgAnimation[i].load("background/background" + index + ".png");
    }
	lastFrameChange = ofGetElapsedTimef();
	frameDelay 		= 0.14f;	// ~ 7 fps
}

void Background::draw(){
    bgAnimation[imageIndex].draw(0,0,ofGetWidth(),ofGetHeight());
}

void Background::update(){
	float t = ofGetElapsedTimef();
    if (t - frameDelay >= lastFrameChange){
        imageIndex = (imageIndex + 1) % N_BG_IMGS;
		lastFrameChange = t;
    }
}

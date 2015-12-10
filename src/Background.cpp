
//
//  Background.cpp
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "Background.h"

#define MAXIMAGES 24

ofImage bgAnimation[MAXIMAGES];

Background::Background(){
    string index;
    for(int i =0; i< MAXIMAGES; i++){
        index = ofToString(i);
        bgAnimation[i].loadImage("background/background" + index + ".png");
    }
}

void Background::draw(){
    bgAnimation[imageIndex].draw(0,0,ofGetScreenWidth(),ofGetScreenHeight());
}

void Background::update(){
    if (ofGetFrameNum() % 7 == 0){
        imageIndex = (imageIndex + 1) % MAXIMAGES;
    }
    //cout << imageIndex << endl;
    
}
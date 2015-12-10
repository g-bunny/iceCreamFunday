
//
//  UI.cpp
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "UI.h"

UI::UI(){
    lowerTeeth.loadImage("UI/lowerTeeth.png");
    upperTeeth.loadImage("UI/upperTeeth.png");
    
    scaleFactor = ofGetWindowWidth()/upperTeeth.getWidth();
}

void UI::update(){
    
}

void UI::draw(){
    upperTeeth.draw(0,-50,ofGetWindowWidth(), upperTeeth.getHeight() * scaleFactor);
    lowerTeeth.draw(0, ofGetWindowHeight() - lowerTeeth.getHeight() + 200, ofGetWindowWidth(), lowerTeeth.getHeight() * scaleFactor);
}
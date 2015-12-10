//
//  Tongue.h
//  tongueGame_tyler
//
//  Created by Tyler on 12/9/15.
//
//

#pragma once
#include "ofMain.h"
#include "ofxKinect.h"

class Tongue{
public:
    
    Tongue();
    void update(float _posX, float _posY);
    void draw();
    
    ofVec2f pos;
    ofVec2f prevPos; //last frame
    
    bool isLicking = false;
    bool isMovingDown = false;
    
    
};

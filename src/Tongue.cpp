//
//  Tongue.cpp
//  tongueGame_tyler
//
//  Created by Tyler on 12/9/15.
//
//

#include "Tongue.h"

Tongue::Tongue(){
	
	pos = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
	prevPos = pos;
	lastHighestYPos = pos.y;
	
}

void Tongue::update(float _posX, float _posY){
	
	pos.x = ofLerp(pos.x,_posX,0.50);
	pos.y = ofLerp(pos.y,_posY,0.30);
	
	if (pos.y < lastHighestYPos){
		lastHighestYPos = pos.y;
	}
	
	//CHECK FOR LICKING
	// licking is any movement from low->high while not moving much left-right
	
	if (pos.y < prevPos.y){
		if ((pos.x > prevPos.x - 10) && (pos.x < prevPos.x + 10)){
			isLicking = true;
			
		} else {
			isLicking = false;
		}
		isMovingDown = false;
		
	} else {
		isLicking = false;
		
		if (pos.y > prevPos.y + 15){
			isMovingDown = true;
		}
	}
	
	prevPos = pos;
	
}

void Tongue::draw(){
	
	
}

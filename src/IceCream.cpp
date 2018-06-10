#include "IceCream.h"

IceCream::IceCream(){
    
    // LOAD IMAGES & ANIMATIONS
	
	// ice cream cone base
	for(int i =0; i< N_ICECREAM_IMAGES; i++){
		string file = "ice_cream_cone/ice_cream_cone_" + ofToString(i, 2, '0') + ".png";
        iceCreamAnimation[i].load(file);
	}
	
	// melt drip
	for(int i =0; i< N_MELT_IMAGES; i++){
		string file = "ice_cream_melt/ice_cream_melt_" + ofToString(i, 2, '0') + ".png";
		meltAnimation[i].load(file);
    }
	
	// soft serve refill
    for(int i =0; i< N_REFILL_IMAGES; i++){
		string file = "ice_cream_refill/ice_cream_refill_" + ofToString(i, 2, '0') + ".png";
		refillAnimation[i].load(file);
    }
	
	// chocolate
	// pour
    for(int i =0; i< N_CHOCOPOUR_IMAGES; i++){
		string file = "toppings/choco_pour_" + ofToString(i, 2, '0') + ".png";
		chocoPourAnimation[i].load(file);
    }
	// lick
	for (int i = 0; i < N_CHOCOLICK_IMAGES; i++){
		string file = "toppings/choco_lick_" + ofToString(i, 2, '0') + ".png";
		chocoLickAnimation[i].load(file);
	}
	
	// sprinkles
    for (int i = 0; i < N_SPRINKLE_SPRITES; i++){
        sprinkles[i].load("toppings/sprinkle_" + ofToString(i, 2, '0') + ".png");
        sprinkles[i].resize(sprinkles[i].getWidth() * SPRINKLE_SCALE, sprinkles[i].getHeight() * SPRINKLE_SCALE);
    }
	
	// level clear / win anim
    for(int i =0; i < N_WIN_IMAGES; i++){
        winAnimation[i].load("special_fx/wink_" + ofToString(i, 2, '0') + ".png");
    }
	
	// empty cone image
    coneImg.load("cone.png");
	// cone front only
	coneFrontImg.load("cone_front.png");
	
	
	// POSITIONING
	
	size.x = iceCreamAnimation[0].getWidth() * CONE_SCALE;
    size.y = iceCreamAnimation[0].getHeight() * CONE_SCALE;
	
    origPos.x = ofGetWidth() * 0.5f - size.x * 0.5f;
    origPos.y = ofGetHeight() - size.y;
	
	pos = origPos;
	
	vel = ofVec2f(0.f);	// stationary at start
	
	frameBounds = ofRectangle(0,0, ofGetWidth(), ofGetHeight());
	
	
	// COLLIDERS
	// positions relative to cone pos
	
	ofRectangle c0 = ofRectangle(150.f, 50.f, 150.f, 100.f);
	ofRectangle c1 = ofRectangle(101.f, 150.f, 250.f, 80.f);
	ofRectangle c2 = ofRectangle(57.f, 230.f, 350.f, 80.f);
	ofRectangle c3 = ofRectangle(38.f, 310.f, 400.f, 70.f);
	
	colliders.emplace_back(c0, true);
	colliders.emplace_back(c1, true);
	colliders.emplace_back(c2, true);
	colliders.emplace_back(c3, true);
	
	
    
    //SETUP icLevels boxes
	// TODO: remove - tyler
    lvlX[0] = 150;
    lvlX[1] = 101;
    lvlX[2] = 57;
    lvlX[3] = 38;
    
    icLevels[0].set(pos.x + lvlX[0], pos.y + 50, 150, 100);
    icLevels[1].set(pos.x + lvlX[1], pos.y + 150, 250, 80);
    icLevels[2].set(pos.x + lvlX[2], pos.y + 230, 350, 80);
    icLevels[3].set(pos.x + lvlX[3], pos.y + 310, 400, 70);
	
	
	// AUDIO
    
    winSound.load("sounds/win.wav");
    winSound.setVolume(0.85f);
    winSound.setMultiPlay(false);
    
    loseSound.load("sounds/lose.wav");
    loseSound.setVolume(0.85f);
    loseSound.setMultiPlay(false);
	
	
	// SETUP
	
	bMelting = false;
	meltStartedTime = 0.f;
	meltDuration = -1.f;
	
	bDripDeath = false;
}

void IceCream::draw(){
	
	// draw base cone
	iceCreamAnimation[lickIndex].draw(pos, size.x, size.y);
	
//    coneFrontImg.draw(pos.x, pos.y, size.x, size.y);
	
	// draw melt animation
    meltAnimation[meltIndex].draw(pos, size.x, size.y);
	
}

void IceCream::drawColliders(){	// for debug
	
	ofPushStyle();
	ofSetColor(0,200,100);
	ofNoFill();
	ofDrawRectangle(pos, size.x, size.y);	// whole cone
	ofPushMatrix();
	ofTranslate(pos);			// colliders relative to cone
	for (auto& col : colliders){
		ofDrawRectangle(col.first);
	}
	ofPopMatrix();
	ofPopStyle();
}

void IceCream::update(){
	
	// move
	pos += vel;
	
	// bounce off bounds
	if ( pos.x > frameBounds.getRight() - size.x ) {
		pos.x = frameBounds.getRight() - size.x;
		vel.x *= -1;
	} else if ( pos.x < frameBounds.getLeft() ) {
		pos.x = frameBounds.getLeft();
		vel.x *= -1;
	}
	if ( pos.y > frameBounds.getBottom() - size.y ) {
		pos.y = frameBounds.getBottom() - size.y;
		vel.y *= -1;
	} else if ( pos.y < frameBounds.getTop() ) {
		pos.y = frameBounds.getTop();
		vel.y *= -1;
	}
	
	// increment melt
	if (bMelting){
		float t = ofGetElapsedTimef();
		int meltIndex =
		ofMap(t, meltStartedTime, meltStartedTime+meltDuration, 0, N_MELT_IMAGES, true);
		if (meltIndex >= N_MELT_IMAGES){
			meltIndex = N_MELT_IMAGES-1;
			bDripDeath = true;
		}
	} else {
		meltIndex = 0;
	}
	
	// game over signal
	
	if (bDripDeath){
		resetWholeGame();	// TODO: move to ofApp
	}
	
	
//    if (ofGetFrameNum() % meltRate == 0){
//        meltIndex = (meltIndex + 1) % N_MELT_IMAGES;
//    }

    //update collider positions
	// TODO: remove
	// tyler - shouldn't be needed, colliders are relative to pos
    if (lickState <1){
        icLevels[0].setX(pos.x + lvlX[0]);
        icLevels[1].setX(pos.x + lvlX[1]);
        icLevels[2].setX(pos.x + lvlX[2]);
        icLevels[3].setX(pos.x + lvlX[3]);
        lickIndex = 0;
    } else if (lickState >=1 && lickState <3 ){
        icLevels[0].setX(-10000);
        icLevels[1].setX(pos.x + lvlX[1]);
        icLevels[2].setX(pos.x + lvlX[2]);
        icLevels[3].setX(pos.x + lvlX[3]);
        if (lickState == 1){
            if (lickIndex <29){
                lickIndex +=1;
            }

        } else if (lickState ==2){
            if (lickIndex <38){
                lickIndex +=1;
            }
        }
    } else if (lickState >= 3 && lickState < 6){
        icLevels[0].setX(-10000);
        icLevels[1].setX(-10000);
        icLevels[2].setX(pos.x + lvlX[2]);
        icLevels[3].setX(pos.x + lvlX[3]);
        if (lickState == 3){
            if (lickIndex <43){
                lickIndex +=1;
            }
            
        } else if (lickState ==4){
            if (lickIndex <47){
                lickIndex +=1;
            }
        }
        else if (lickState == 5){
            if (lickIndex <51){
                lickIndex +=1;
            }
            
        }
    } else if (lickState >=6 && lickState < 10){
        icLevels[0].setX(-10000);
        icLevels[1].setX(-10000);
        icLevels[2].setX(-10000);
        icLevels[3].setX(pos.x + lvlX[3]);
        if (lickState ==6){
            if (lickIndex <56){
                lickIndex +=1;
            }
        }  else if (lickState ==7){
            if (lickIndex <60){
                lickIndex +=1;
            }
        }  else if (lickState ==8){
            if (lickIndex <64){
                lickIndex +=1;
            }
        }  else if (lickState ==9){
            if (lickIndex <69){
                lickIndex +=1;
            }
        }
        if (lickIndex <56){
            lickIndex +=1;
        }
    } else if (lickState >= 10){
        icLevels[0].setX(-10000);
        icLevels[1].setX(-10000);
        icLevels[2].setX(-10000);
        icLevels[3].setX(-10000);
        if (lickIndex <74){
            lickIndex +=1;
        }
        gameLevel ++;
        lickState = 0;
        progressLevel;
        reset();
    }
    
    cout<<"melt? "<<meltIndex<<endl;
    if(meltIndex == N_MELT_IMAGES - 1){
        bDripDeath = true;
    }
}


void IceCream::move(){
    pos.x += moveIncrement;
    if (pos.x > ofGetWidth() - size.x || pos.x < 0){
        moveIncrement *= -1;
    }
}

bool IceCream::checkCollision(ofVec2f pos){
//    for (int i=0; i<4; i++){
//        //check for collision
//        if ((checkPos.x > icLevels[i].getMinX()) &&
//            (checkPos.x < icLevels[i].getMaxX()) &&
//            (checkPos.y > icLevels[i].getMinY()) &&
//            (checkPos.y < icLevels[i].getMaxY())){
//
//            return true;
//        }
//    }
	for (auto& collider : colliders){
		if (collider.second && collider.first.inside(pos)){
			return true;
		}
	}
	return false;
}

void IceCream::level1(){
//    moveIncrement = 2;
    meltRate = 1000;
    draw();
}
void IceCream::level2(){
//    moveIncrement = 5;
    meltRate = 15;
    move();
    draw();
    drawSprinkles();
}
void IceCream::level3(){
    drawChoco();
}
void IceCream::level4(){
    
    meltRate = 10;
    move();

    draw();
    cout<<"lick state: "<<lickState<<endl;
    if (lickState ==0){
        chocoLickAnimation[0].draw(pos.x, pos.y, ofGetWidth(), ofGetHeight());
    }
    if (lickState == 1){
        chocoLickAnimation[1].draw(pos.x, pos.y + 10, ofGetWidth(), ofGetHeight());
    }
    if (lickState == 2){
        chocoLickAnimation[2].draw(pos.x, pos.y + 30, ofGetWidth(), ofGetHeight());
    }
//    if (lickState ==10){
//        win();
//    }
}

//void IceCream::level8(){
//    if (ofGetFrameNum()% 5== 0 && winkIndex < WINKIMAGES -1){
//        winkIndex += 1;
//    }
//    winkAnimation[winkIndex].draw(pos.x, pos.y);
//    if(winkIndex == WINKIMAGES -1){
//        gameLevel += 1;
//    }
//}

void IceCream::reset(){
    if (progressLevel){
        lickState = 0;
        progressLevel = false;
    }
    meltIndex = 0;
    pos.x = origPos.x;
    pos.y = origPos.y;
    flowIndex = 0;
    lickState = 0;
}

void IceCream::resetWholeGame(){
    reset();
    gameLevel = 0;
    winkIndex = 0;
    chocoIndex = 0;
}

void IceCream::flow(){
    coneFrontImg.draw(pos.x - coneAlignment, pos.y, ofGetWidth(), ofGetHeight());

    if (ofGetFrameNum() % flowSpeed == 0 && flowing == true){
        flowIndex = flowIndex + 1;
    }
    refillAnimation[flowIndex].draw(pos.x - flowAlignment,pos.y,ofGetWidth(),ofGetHeight());
    if (flowIndex >= N_REFILL_IMAGES ){
        flowing = false;
        gameLevel +=1;
    }
    cout << "flow index " << flowIndex << endl;
    lickState = 0;
}

void IceCream::win(){
    if(ofGetFrameNum() % flowSpeed == 0 && winkIndex < N_WIN_IMAGES - 1){
        winkIndex = winkIndex + 1;
    }
    if(winkIndex == 6){
        winSound.play();
    }
//    if(winkIndex == WINKIMAGES - 1){
//        winkIndex = 0;
//    }
    cout<<"wink index: " << winkIndex<<endl;
    winAnimation[winkIndex].draw(pos.x, pos.y, ofGetWidth(), ofGetHeight());
    if (winkIndex >= N_WIN_IMAGES -1){
        resetWholeGame();
    }
}

void IceCream::brainFreeze(){
    if (gotLick){
        currentLickFrame = ofGetFrameNum();
        //cout<<"licked frame: " << savedLickFrame<<endl;
    }
    if (currentLickFrame - savedLickFrame < speedLimit){
        brainFrozen = true;
    } else {
        brainFrozen = false;
    }
    savedLickFrame = currentLickFrame;
}

void IceCream::drawSprinkles(){
    if (lickState ==0){
        sprinkles[0].draw(pos.x + lvlX[0]+ 20, pos.y + 50 + 20);
    }
    if (lickState <= 2){
        sprinkles[1].draw(pos.x + lvlX[1] + 80, pos.y + 150 + 30);
        sprinkles[0].draw(pos.x + lvlX[1] + 180, pos.y + 150 + 50);
    }
    if (lickState <= 5){
        sprinkles[2].draw(pos.x + lvlX[2] + 130, pos.y + 230 + 50);
        sprinkles[3].draw(pos.x + lvlX[2] + 30, pos.y + 230 + 50);
        sprinkles[1].draw(pos.x + lvlX[2] + 230, pos.y + 230 + 50);
    }
    if (lickState <=8){
        sprinkles[3].draw(pos.x + lvlX[3] + 300, pos.y + 310 + 60);
        sprinkles[1].draw(pos.x + lvlX[3] + 100, pos.y + 310 + 50);
        sprinkles[2].draw(pos.x + lvlX[3] + 200, pos.y + 310 + 40);
        sprinkles[0].draw(pos.x + lvlX[3] + 360, pos.y + 310 + 30);
    }
}

void IceCream::drawChoco(){
    if(ofGetFrameNum() % chocoSpeed == 0){
        chocoIndex = chocoIndex + 1;
    }
    iceCreamAnimation[1].draw(pos.x, pos.y, ofGetWidth(), ofGetHeight());
    chocoPourAnimation[chocoIndex].draw(pos.x- coneAlignment, pos.y, ofGetWidth(), ofGetHeight());
    if(chocoIndex == N_CHOCOPOUR_IMAGES){
        chocoPourAnimation[N_CHOCOPOUR_IMAGES - 1].draw(pos.x- coneAlignment, pos.y, ofGetWidth(), ofGetHeight());
        gameLevel +=1;
        reset();
    }
}

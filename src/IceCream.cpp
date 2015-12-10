
//
//  IceCream.cpp
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "IceCream.h"



IceCream::IceCream(){
    
    //load animations
    string index;
    for(int i =0; i< MAXIMAGES; i++){
        index = ofToString(i + 10);
        lickAnimation[i].loadImage("iceCream/iceCream000" + index + ".png");
        meltAnimation[i].loadImage("iceCreamMelt/iceCreamMelt000" + index + "_bottom.png");
    }
    string flowIndex;
    for(int i =0; i< FLOWIMAGES; i++){
        flowIndex = ofToString(i);
        flowAnimation[i].loadImage("iceCreamFlow/iceCream_start00" + flowIndex + ".png");
    }
    
    //load cone
    //coneFull.loadImage("iceCreamCone.png");
    coneFront.loadImage("iceCreamConeFront.png");
    
    
    scaleFactor = 0.5;
    
    height = lickAnimation[0].getHeight() * scaleFactor;
    width = lickAnimation[0].getWidth() * scaleFactor;
    
    origPos.x = -width * 0.5 + ofGetWidth()/2;
    origPos.y = ofGetHeight() - height ;
    pos.x = origPos.x;
    pos.y = origPos.y;
    cPos = ofVec2f(pos.x + width*0.5, pos.y + height*0.5); //easy center pos of image
    
    
    //SETUP icLevels boxes
    lvlX[0] = 150;
    lvlX[1] = 101;
    lvlX[2] = 57;
    lvlX[3] = 38;
    
    icLevels[0].set(pos.x + lvlX[0], pos.y + 50, 150, 100);
    icLevels[1].set(pos.x + lvlX[1], pos.y + 150, 250, 80);
    icLevels[2].set(pos.x + lvlX[2], pos.y + 230, 350, 80);
    icLevels[3].set(pos.x + lvlX[3], pos.y + 310, 400, 70);
    
}

void IceCream::draw(){
    lickAnimation[lickIndex].draw(pos.x, pos.y, width, height);
    coneFront.draw(pos.x - coneAlignment, pos.y, width, height);
    meltAnimation[meltIndex].draw(pos.x, pos.y, width, height);
    
    ofPushStyle();
    ofSetColor(255,0,0);
    ofNoFill();
    // **** collision detection rectangles ****
    ofRect(pos.x, pos.y, width, height);
    for (int i=0; i<4; i++){
        ofRect(icLevels[i].getTopLeft(), icLevels[i].getWidth(), icLevels[i].getHeight());
    }
    ofPopStyle();
    if (dripDeath){
        resetWholeGame();
    }
}

void IceCream::update(){
    if (ofGetFrameNum() % meltRate == 0){
        meltIndex = (meltIndex + 1) % MAXIMAGES;
    }

    //update collider positions
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
    if(meltIndex == MAXIMAGES - 1){
        dripDeath = true;
    }
}

void IceCream::move(){
    pos.x += moveIncrement;
    cPos.x = pos.x + width*0.5;
    if (pos.x > ofGetWidth() - width || pos.x < 0){
        moveIncrement *= -1;
    }
}

bool IceCream::collision(ofVec2f checkPos){
    for (int i=0; i<4; i++){
        //check for collision
        if ((checkPos.x > icLevels[i].getMinX()) &&
            (checkPos.x < icLevels[i].getMaxX()) &&
            (checkPos.y > icLevels[i].getMinY()) &&
            (checkPos.y < icLevels[i].getMaxY())){
            
            return true;
        }
    }
}

void IceCream::level1(){
//    moveIncrement = 2;
    meltRate = 1000;
    draw();
}
void IceCream::level3(){
//    moveIncrement = 5;
    meltRate = 15;
    draw();
    move();
}
void IceCream::level5(){
//    moveIncrement = 6;
    meltRate = 10;
    draw();
    move();
    if (gotLick){
        brainFreeze();
    }
    cout<<"brainfrozen? " << brainFrozen << endl;
}
void IceCream::level7(){
//    moveIncrement = 7;
    meltRate = 5;
    draw();
    move();
    if (gotLick){
        brainFreeze();
    }
    cout<<"brainfrozen? " << brainFrozen << endl;
}

void IceCream::reset(){
    if (progressLevel){
        lickState = 0;
        progressLevel = false;
    }
    meltIndex = 0;
    pos.x = origPos.x;
    pos.y = origPos.y;
    flowIndex = 0;
}

void IceCream::resetWholeGame(){
    reset();
    gameLevel = 0;
}

void IceCream::flow(){
    if (ofGetFrameNum() % flowSpeed == 0){
        flowIndex = flowIndex + 1;
    }
    flowAnimation[flowIndex].draw(pos.x,pos.y,width,height);
    coneFull.draw(pos.x, pos.y);
    if (flowIndex == FLOWIMAGES){
        flowing = false;
        gameLevel +=1;
    }
    cout << "flow index " << flowIndex << endl;
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
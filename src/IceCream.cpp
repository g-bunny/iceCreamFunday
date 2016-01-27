
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
        flowIndex = ofToString(i + 10);
        flowAnimation[i].loadImage("iceCreamFlow/iceCream_startNew000" + flowIndex + ".png");
    }
    string tempChocoIndex;
    for(int i =0; i< CHOCOIMAGES; i++){
        tempChocoIndex = ofToString(i);
        chocoAnimation[i].loadImage("toppings/iceCreamChoco00" + tempChocoIndex + ".png");
        chocoAnimation[i].resize(1908, 1431);
        //chocoAnimation[i].crop(446,0,1017,1431);
        chocoAnimation[i].crop(486, 0, 1057, 1431);
    }
    string tempSprindex;
    for (int i = 0; i < NUMOFSPRINKLES; i++){
        tempSprindex = ofToString(i + 1);
        sprinkle[i].loadImage("toppings/sprinkle_" + tempSprindex + ".png");
        sprinkle[i].resize(sprinkle[i].width * 0.6, sprinkle[i].height * 0.6);
    }
    string tempChocoMeltIndex;
    for (int i = 0; i < CHOCOMELT; i++){
        tempChocoMeltIndex = ofToString(i);
        chocoMeltAnimation[i].loadImage("toppings/chocoMelt00" + tempChocoMeltIndex + ".png");
        chocoMeltAnimation[i].resize(1908, 1431);
        chocoMeltAnimation[i].crop(486, 0, 1057, 1431);
    }
    string tempWinkIndex;
    for(int i =0; i < WINKIMAGES; i++){
        tempWinkIndex = ofToString(i);
        winkAnimation[i].loadImage("specialEffects/wink1_000" + tempWinkIndex + ".png");
    }
    
    coneFront.loadImage("iceCreamConeFront.png");
    coneFull.loadImage("iceCreamCone.png");

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
//    ofRect(pos.x, pos.y, width, height);
//    for (int i=0; i<4; i++){
//        ofRect(icLevels[i].getTopLeft(), icLevels[i].getWidth(), icLevels[i].getHeight());
//    }
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
void IceCream::level2(){
//    moveIncrement = 5;
    meltRate = 15;
    draw();
    move();
    drawSprinkles();
}
void IceCream::level3(){
    drawChoco();
}
void IceCream::level4(){
    meltRate = 10;
    draw();
    move();
    cout<<"lick state: "<<lickState<<endl;
    if (lickState ==0){
        chocoMeltAnimation[0].draw(pos.x, pos.y, width, height);
    }
    if (lickState == 1){
        chocoMeltAnimation[1].draw(pos.x, pos.y + 10, width, height);
    }
    if (lickState == 2){
        chocoMeltAnimation[2].draw(pos.x, pos.y + 30, width, height);
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
}

void IceCream::flow(){
    coneFull.draw(pos.x - coneAlignment, pos.y, width, height);

    if (ofGetFrameNum() % flowSpeed == 0){
        flowIndex = flowIndex + 1;
    }
    flowAnimation[flowIndex].draw(pos.x - flowAlignment,pos.y,width,height);
    if (flowIndex == FLOWIMAGES ){
        flowing = false;

            gameLevel +=1;
    }
    cout << "flow index " << flowIndex << endl;
    lickState = 0;
}

void IceCream::win(){
    if(ofGetFrameNum() % flowSpeed == 0 && winkIndex < WINKIMAGES - 1){
        winkIndex = winkIndex + 1;
    }
//    if(winkIndex == WINKIMAGES - 1){
//        winkIndex = 0;
//    }
    cout<<"wink index: " << winkIndex<<endl;
    winkAnimation[winkIndex].draw(pos.x, pos.y, width, height);
    if (winkIndex >= WINKIMAGES -1){
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
        sprinkle[0].draw(pos.x + lvlX[0]+ 20, pos.y + 50 + 20);
    }
    if (lickState <= 2){
        sprinkle[1].draw(pos.x + lvlX[1] + 80, pos.y + 150 + 30);
        sprinkle[0].draw(pos.x + lvlX[1] + 180, pos.y + 150 + 50);
    }
    if (lickState <= 5){
        sprinkle[2].draw(pos.x + lvlX[2] + 130, pos.y + 230 + 50);
        sprinkle[3].draw(pos.x + lvlX[2] + 30, pos.y + 230 + 50);
        sprinkle[1].draw(pos.x + lvlX[2] + 230, pos.y + 230 + 50);
    }
    if (lickState <=8){
        sprinkle[3].draw(pos.x + lvlX[3] + 300, pos.y + 310 + 60);
        sprinkle[1].draw(pos.x + lvlX[3] + 100, pos.y + 310 + 50);
        sprinkle[2].draw(pos.x + lvlX[3] + 200, pos.y + 310 + 40);
        sprinkle[0].draw(pos.x + lvlX[3] + 360, pos.y + 310 + 30);
    }
}

void IceCream::drawChoco(){
    if(ofGetFrameNum() % chocoSpeed == 0){
        chocoIndex = chocoIndex + 1;
    }
    lickAnimation[1].draw(pos.x, pos.y, width, height);
    chocoAnimation[chocoIndex].draw(pos.x, pos.y, width, height);
    if(chocoIndex == CHOCOIMAGES){
        chocoAnimation[CHOCOIMAGES - 1].draw(pos.x, pos.y, width, height);
        gameLevel +=1;
        reset();
    }
}
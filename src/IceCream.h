//
//  IceCream.h
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "ofMain.h"

#define MAXIMAGES 75
#define FLOWIMAGES 34


class IceCream{
public:
    IceCream();
    void draw();
    void update();
    void melt();
    void move();
    void sprinkles();
    void flow();
    bool collision(ofVec2f checkPos);
    
    void level1();
    void level3();
    void level5();
    void level7();
    
    void brainFreeze();
    //resetting level data/ positioning ice cream in middle
    void reset();
    //when lose, resetting the whole game to level 0
    void resetWholeGame();
    
    bool brainFrozen = false;
    bool gotLick = false;
    bool flowing = true;
    int meltIndex;
    int lickIndex;
    int flowIndex = 0;
    
    ofImage lickAnimation[MAXIMAGES];
    ofImage meltAnimation[MAXIMAGES];
    ofImage flowAnimation[FLOWIMAGES];
    ofImage coneFront;
    ofImage coneFull;
    
    
    float width, height;
    float scaleFactor; //converts from image to screen rect
    
    //ice cream position
    ofVec2f origPos;
    ofVec2f pos;
    ofVec2f cPos; //easy center
    
    float moveIncrement = 5;
    
    //sprinkles position
    float sprinkPosX;
    float sprinkPosY;
    
    //string
    
    //ice cream colliders, 0-3
    ofRectangle icLevels[4];
    int lvlX[4]; // x offset
    
    int lickState = 0; // 0-10 (# of licks)
    
    //keyframes of icecream disappearance: 29, 38, 43, 47, 51, 56, 60, 64, 69, 77
    
    bool progressLevel = false;
    
    int gameLevel = 0;
    
    int speedLimit = 200;
    int savedLickFrame;
    int currentLickFrame;
    
    int meltRate = 15;
    
    int coneAlignment = 3;
    int flowSpeed = 6;
    
    bool dripDeath = false;
};
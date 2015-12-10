//
//  IceCream.h
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "ofMain.h"

#define MAXIMAGES 75


class IceCream{
public:
    IceCream();
    void draw();
    void update();
    void melt();
    void move();
    void sprinkles();
    bool collision(ofVec2f checkPos);
    
    void level1();
    void level2();
    void level3();
    
    void brainFreeze();
    
    bool brainFrozen = false;
    bool gotLick = false;
    int imageIndex;
    
    ofImage lickAnimation[MAXIMAGES];
    ofImage meltAnimation[MAXIMAGES];
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
    
    void reset();
    int gameLevel = 1;
    
    int speedLimit = 200;
    int savedLickFrame;
    int currentLickFrame;
    
};
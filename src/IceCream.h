//
//  IceCream.h
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "ofMain.h"

static const int N_ICECREAM_IMAGES  = 75;
static const int N_MELT_IMAGES = 75;
static const int N_REFILL_IMAGES = 14;	// REFILL
static const int N_CHOCOPOUR_IMAGES = 22;
static const int N_CHOCOLICK_IMAGES = 3;
static const int N_WIN_IMAGES = 17;

static const int N_SPRINKLE_SPRITES = 4; // sprinkle sprites
static const float SPRINKLE_SCALE = 0.6f;

static const float CONE_SCALE = 0.5f;

class IceCream {
public:
	
    IceCream();
	void update();
    void draw();
	
	bool checkCollision(ofVec2f pos);
	void drawColliders();	// debug
	
	void setFrameBounds(ofRectangle bounds);
	
	void resetMeltTimer(float secs);
	
	// position
	ofVec2f origPos;
	ofVec2f pos;
	ofVec2f size;
	ofVec2f vel;	// movement direction, speed
	ofRectangle frameBounds;
	float scaleFactor; // converts from image to screen rect
	
	// colliders
	vector<pair<ofRectangle, bool>> colliders;	// collider, on/off
	
	// melt timing
	float meltStartedTime;
	float meltDuration;
	bool bMelting;
	
	bool bDripDeath;
	
	
	// images
	ofImage iceCreamAnimation[N_ICECREAM_IMAGES];
	ofImage meltAnimation[N_MELT_IMAGES];
	
	ofImage refillAnimation[N_REFILL_IMAGES];	// soft serve flow
	ofImage chocoPourAnimation[N_CHOCOPOUR_IMAGES];	// chocolate pour
	ofImage chocoLickAnimation[N_CHOCOLICK_IMAGES];
	
	ofImage winAnimation[N_WIN_IMAGES];		// win level star
	
	ofImage sprinkles[N_SPRINKLE_SPRITES];
	ofVec2f sprinklesPos[N_SPRINKLE_SPRITES];
	
	ofImage coneImg;
	ofImage coneFrontImg;
	
	
    void melt();
    void move();
    void drawSprinkles();
    void drawChoco();
    void flow();
	
    //gameLevel 1 = level1
    void level1();
    //gameLevel 3 = level2
    void level2();
    //gameLevel 6 = level3
    void level3();
    //gameLevel 7 = level4
    void level4();
    
    void level8();
    
    void win();
    
    void brainFreeze();
    //resetting level data/ positioning ice cream in middle
    void reset();
    //when lose, resetting the whole game to level 0
    void resetWholeGame();
    //void win();
    
   // bool won = false;
    bool brainFrozen = false;
    bool gotLick = false;
    bool flowing = true;
    int meltIndex = 0;
    int lickIndex = 0;
    int flowIndex = 0;
    int winkIndex = 0;
    
    int chocoIndex = 0;
    int chocoSpeed = 9;
    

    

	
    float moveIncrement = 5;
    
    //sprinkles position

    
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
    //////flowAlignment needs to be fudged around with
    int flowAlignment = 30;
    int flowSpeed = 10;
    
//    bool dripDeath = false;
    bool won = false;
    
    ofSoundPlayer winSound;
    ofSoundPlayer loseSound;
};

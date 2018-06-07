//
//  Background.h
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "ofMain.h"

#define N_BG_IMGS 24

class Background{
public:
    Background();
    void draw();
    void update();
	void setFrameRate(float fps) {
		fps 		= ofClamp(fps, 0.1f, 60.f);
		frameDelay 	= 1.f / fps;
	}
    
    int imageIndex;
	
	ofImage bgAnimation[N_BG_IMGS];
	
	float lastFrameChange;
	float frameDelay;
};

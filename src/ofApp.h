#pragma once

#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"


#include "ofMain.h"
#include "Background.h"
#include "IceCream.h"
#include "UI.h"
#include "Tongue.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    Background bg;
    IceCream iceCream;
    UI teeth;
    
    Tongue tongue;
    //bool gotLick = false;
    
    ofxKinect kinect;
    
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage; 		// grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; 	// the far thresholded image
    
    ofxCvContourFinder contourFinder;
    
    int icLevelNum = 0;
    int winDuration = 120;
    
//    bool drawKinect = false;
	
    ofSoundPlayer lickSound;
    ofSoundPlayer music;
	
	ofxPanel gui;
	ofParameter<int> kinectNearThresh, kinectFarThresh;
	ofParameter<bool> bDrawKinect;
	ofParameter<float> lickVolume, musicVolume;
	ofParameter<float> bgFps;
	
	bool bHasKinect, bDrawGui;
    
};

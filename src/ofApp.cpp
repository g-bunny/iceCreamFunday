#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   // ofSetFullscreen(true);
    this->bg = new Background();
    this->iceCream = new IceCream();
    this->teeth = new UI();
    
    tongue = Tongue();
    
    //KINECT SETUP
    
    if (USE_KINECT){
        kinect.setRegistration(true);
        kinect.init();
        kinect.open();
        
        colorImg.allocate(kinect.width, kinect.height);
        grayImage.allocate(kinect.width, kinect.height);
        grayThreshNear.allocate(kinect.width, kinect.height);
        grayThreshFar.allocate(kinect.width, kinect.height);
        
        kinectNearThresh= 255;
        kinectFarThresh = 250;
    }
    lick.loadSound("sounds/slurp2.wav");
    lick.setVolume(0.85f);
    lick.setMultiPlay(false);

    music.loadSound("sounds/ICE CREAM LICK (Original Mix) - Final Mix 1 - Siyoung 2015 (24 Bit MSTR).wav");
    music.setVolume(0.7f);
    music.setLoop(true);
    ofSetFrameRate(60);
    
        music.play();
    

}

//--------------------------------------------------------------
void ofApp::update(){

    
    bg->update();
    iceCream->update();

    ofVec2f tonguePos = ofVec2f(ofGetMouseX(), ofGetMouseY());
    if (USE_KINECT){
        kinect.update();
        
        //tonguePos = kinect->tongueTip pos
        
        if(kinect.isFrameNew()) {

            grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(kinectNearThresh, true);
            grayThreshFar.threshold(kinectFarThresh);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
            
            // update the cv images
            grayImage.flagImageChanged();
            
            contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
            contourFinder.findContours(grayImage, 400, 600, 1, false);
        }
        
    }
    
    // update tongue coordinates
    tongue.update(tonguePos.x,tonguePos.y);
    
    // check if tongue is giving a lick ;)
    if (tongue.isLicking){
        
        // if hasn't gotten ice cream yet on this lick
        if (iceCream->gotLick == false){
            
            /* check if tongue is touching ice cream */
            if (iceCream->collision(tongue.pos)){
                cout << "licked ice cream: " << ++(iceCream->lickState) << endl;
                iceCream->gotLick = true;
                lick.play();
            }
            else {
                iceCream->gotLick = false;
            }
            
        }
        
    } else if (tongue.isMovingDown){
        
        iceCream->gotLick = false;
        
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (iceCream->gameLevel == 0 ||iceCream->gameLevel == 2||iceCream->gameLevel == 4 || iceCream->gameLevel ==6){
        iceCream->flowing = true;
        iceCream->dripDeath = false;
    }
    if (iceCream->gameLevel >= 8){
        iceCream->gameLevel = 0;
    }
    bg->draw();

    if (iceCream->gameLevel == 0){
        if (iceCream->flowing){
        iceCream->flow();
        }
    }
    if (iceCream->gameLevel ==1){
        //stationary and no toppings
        iceCream->level1();
    } else if (iceCream->gameLevel ==2){
        //ice cream flow anmation
        if (iceCream->flowing){
            iceCream->flow();
        }
    } else if (iceCream->gameLevel == 3){
        //moving and sprinkles
        iceCream->level2();
    } else if (iceCream->gameLevel == 4){
        //ice cream flow animation
        if (iceCream->flowing){
            iceCream->flow();
        }
    } else if (iceCream->gameLevel == 5){
        //choco flow animation
        iceCream->level3();
    } else if (iceCream->gameLevel == 6){
        //moving and choco
        iceCream->level4();
    }
    teeth->draw();
    
    if (drawKinect){
        grayImage.draw(10, 320, 400, 300);
        contourFinder.draw(10, 320, 400, 300);
    }
    cout<<"game level: " <<iceCream->gameLevel<<endl;
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key){
            
        case ('1'):
            icLevelNum = 0;
            break;
        case ('2'):
            icLevelNum = 1;
            break;
        case ('3'):
            icLevelNum = 2;
            break;
        case ('4'):
            icLevelNum = 3;
            break;
            
        case (OF_KEY_UP):
            cout << "lvlX[" << icLevelNum << "] is " << ++(iceCream->lvlX[icLevelNum]) << endl;
            break;
        
        case (OF_KEY_DOWN):
            cout << "lvlX[" << icLevelNum << "] is " << --(iceCream->lvlX[icLevelNum]) << endl;
            break;
            
        case ('k'):
            if (USE_KINECT){
                drawKinect = !drawKinect;
                cout << "draw kinect: " << drawKinect << endl;
            }
            break;
            
        // KINECT THRESHOLDING
        case ('='):
            kinectNearThresh++;
            if (kinectNearThresh > 255){
                kinectNearThresh = 255;
            }
            cout << "kinectNearThresh: " << kinectNearThresh << endl;
            break;
        case ('-'):
            kinectNearThresh--;
            if (kinectNearThresh < 0){
                kinectNearThresh = 0;
            }
            cout << "kinectNearThresh: " << kinectNearThresh << endl;
            break;
        case ('0'):
            kinectFarThresh++;
            if (kinectFarThresh > 255){
                kinectFarThresh = 255;
            }
            cout << "kinectFarThresh: " << kinectFarThresh << endl;
            break;
        case ('9'):
            kinectFarThresh--;
            if (kinectFarThresh < 0){
                kinectFarThresh = 0;
            }
            cout << "kinectFarThresh: " << kinectFarThresh << endl;
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//
//  UI.h
//  tongueGame
//
//  Created by Miri Park on 12/8/15.
//
//

#include "ofMain.h"

class UI{
public:
    UI();
    void draw();
    void update();
    
    ofImage lowerTeeth;
    ofImage upperTeeth;
    
    float scaleFactor;
};
#pragma once

#ifndef triangle_hpp
#define triangle_hpp

#include <stdio.h>
#include "ofMain.h"

#endif /* triangle_hpp */

class Triangle{
    
public:
    
    Triangle();
    void setup(ofPoint pos1, ofPoint pos2, ofPoint pos3);
    void update();
    void draw();
    
    ofPoint position1, position2, position3;
    ofPoint velocity;
    
    ofPoint origin1, origin2, origin3;
    ofPoint random1, random2, random3;

    
};

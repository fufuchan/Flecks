#include "triangle.hpp"

Triangle::Triangle(){
    velocity.set(0.01,0.01);
    
}
//--------------------------------------------------------------
void Triangle::setup(ofPoint pos1, ofPoint pos2, ofPoint pos3){
    
    // Positions of triangle vertices
    position1 = pos1;
    position2 = pos2;
    position3 = pos3;
    
    origin1 = pos1;
    origin2 = pos2;
    origin3 = pos3;
    
    random1.set (ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
    random2.set (ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
    random3.set (ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10));
}

//--------------------------------------------------------------
void Triangle::update(){
    
    // Add movement to each triangle
    position1 += velocity;
    position2 += velocity;
    position3 += velocity;

}

//--------------------------------------------------------------
void Triangle::draw(){
    
    ofDrawTriangle(position1, position2, position3);
}

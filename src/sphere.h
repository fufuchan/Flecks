//
//  sphere.h
//  3DTest
//
//  Created by Freya Berkhout on 16/04/2018.
//
# pragma once
#ifndef sphere_h
#define sphere_h
#endif /* sphere_h */

#include "ofMain.h"
#include "ofApp.h"
#include "triangle.hpp"

class Sphere{
    
    public:
    
    Sphere();
    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    vector <ofPoint> vertices;
    vector <Triangle> triangles;
    
    vector <ofColor> colors0;
    vector <ofColor> colors1;
    vector <ofColor> colors2;

    ofMesh mesh;
    int nTri;       //The number of triangles
    int nVert;      //The number of the vertices equals nTri * 3
    int move;

    ofPoint center;
    
    float getAnalogValue(float analogPin0, float analogPin1, float analogPin2);
    float incoming0, incoming1, incoming2;
    float stretch, lerp, bounce, scatter;
    float offset;
    float pulse, pulse2;
    float sinStep, sinPulse;
    
    
    
    
};

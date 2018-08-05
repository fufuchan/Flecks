#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "sphere.h"


class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();
    
    Sphere Sphere;

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);

	ofImage				bgImage;
	ofTrueTypeFont		font;
    ofTrueTypeFont      smallFont;
	ofArduino	ard;
	bool		bSetupArduino;			// flag variable for setting up arduino once
    
    float analog0, analog1, analog2;
    deque <float> ardInputBuffer;
    int maxBufferSize;
    float bufferSum;
    float avg;
    
private:
    
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	void updateArduino();
    
    string buttonState;
    string potValue0;
    string potValue1;
    string potValue2;
    
    ofPoint pos;
    ofPoint vel;
    
    ofPoint test;


};


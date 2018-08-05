#include "ofApp.h"
#include "sphere.h"

     ////////////////// Freya Berkhout: Flecks \\\\\\\\\\\\\\\\\\\
    ////// Initial sketch inspiration from Denis Perevalov's \\\\\\
   ///// Mastering openFrameworks: Creative Coding Demystified.\\\\\
  ////// Flecks allows individuals to interact with flex sensors\\\\\
 ////////  that shape and affect a 3D sphere made of triangles. \\\\\\
///////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

//--------------------------------------------------------------
void ofApp::setup(){

    Sphere.setup();
    
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    
    // Read analog pin values.
    potValue0 = "analog pin 0:";
    potValue1 = "analog pin 1:";
    potValue2 = "analog pin 2:";
    test.set(100, 100);

    // Arduino serial port to listen to.
	ard.connect("cu.usbmodem1451", 57600);
	
	// listen for EInitialized notification. this indicates that the Arduino is ready to receive commands and it is safe to call setupArduino().
	ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
	bSetupArduino	= false;	// flag so we setup Arduino when its ready.
    
    maxBufferSize = 10;

}

//--------------------------------------------------------------
void ofApp::update(){

	updateArduino();
    
    Sphere.update();
    
    Sphere.getAnalogValue(analog0, analog1, analog2);

    // Buffer test to smooth values.
    bufferSum = 0;
    ardInputBuffer.push_back(analog0);
    
    if (ardInputBuffer.size() > maxBufferSize) ardInputBuffer.pop_back();
    
    for (int i = 0; i < ardInputBuffer.size(); i++){
        float temp = ardInputBuffer[i];
        bufferSum += temp;
    }
    
    avg = bufferSum / ardInputBuffer.size();
    
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
	
	// Remove listener.
	ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // Send commands to the Arduino.
    bSetupArduino = true;
    
    // Print firmware name and version to the console.
    ofLogNotice() << ard.getFirmwareName(); 
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();

    // Set pin A0 - A2 to analog input.
    ard.sendAnalogPinReporting(0, ARD_ANALOG);
    ard.sendAnalogPinReporting(1, ARD_ANALOG);
    ard.sendAnalogPinReporting(2, ARD_ANALOG);

	
    // Listen for changes on the analog pins.
    ofAddListener(ard.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino(){

	// Update the Arduino, get any data or messages.
	ard.update();
	
	// Do not send anything until the arduino has been set up.
	if (bSetupArduino) {
        // Fade the led connected to pin D11
		ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
	}

}

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
}

// analog pin event handler, called whenever an analog pin value has changed

//--------------------------------------------------------------
void ofApp::analogPinChanged(const int & pinNum) {
    // Use the analog inputs. Print the pin number and value to the screen each time it changes
    potValue0 = "analog pin: " + ofToString(0) + " = " + ofToString(ard.getAnalog(0));
    potValue1 = "analog pin: " + ofToString(1) + " = " + ofToString(ard.getAnalog(1));
    potValue2 = "analog pin: " + ofToString(2) + " = " + ofToString(ard.getAnalog(2));

    analog0 = ard.getAnalog(0);
    analog1 = ard.getAnalog(1);
    analog2 = ard.getAnalog(2);

}


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    Sphere.draw();
    ofPopMatrix();
    
//    ofPoint origin(100,100);
//    
//    float testStretch = ofMap(analog0, 880, 1000, 1, 1.5, true);
//    float testM = ofMap(mouseX, 0 , ofGetWidth(), 0, 20, true);
//    test += testM;
//    }
//    cout<< testStretch << endl;
//    ofSetColor(255);
//    ofDrawRectangle(test, 300, 300);
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    switch (key) {
        case OF_KEY_RIGHT:
            // rotate servo head to 180 degrees
            ard.sendServo(9, 180, false);
            ard.sendDigital(18, ARD_HIGH);  // pin 20 if using StandardFirmata from Arduino 0022 or older
            break;
        case OF_KEY_LEFT:
            // rotate servo head to 0 degrees
            ard.sendServo(9, 0, false);
            ard.sendDigital(18, ARD_LOW);  // pin 20 if using StandardFirmata from Arduino 0022 or older
            break;
        default:
            break;
    }
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    // turn on the onboard LED when the application window is clicked
	ard.sendDigital(13, ARD_HIGH);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    // turn off the onboard LED when the application window is clicked
	ard.sendDigital(13, ARD_LOW);
}



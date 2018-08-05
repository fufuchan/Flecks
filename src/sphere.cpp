//  Created by Freya Berkhout on 16/04/2018.
//
#include "ofApp.h"
#include "sphere.h"

//--------------------------------------------------------------
Sphere::Sphere(){

}

//--------------------------------------------------------------
void Sphere::setup(){
    
    // Sphere system variables
    nTri = 4000;
    nVert= nTri * 4;
    float Rad = 280;
    float rad = 20;
    sinStep = 0;
    sinPulse = 0;
    offset = 0.01;
    
    for (int i = 0; i < nTri; i++){
        Triangle t;
        triangles.push_back(t);
    }

    vertices.resize (nVert);
    for (int i = 0; i < nTri; i++) { //Generate the center of the triangle as a random point on the sphere,                                     Take the random point from cube [-1,1]x[-1,1]x[-1,1]
        center.set(ofRandom (-1, 1), ofRandom (-1, 1), ofRandom (-1, 1)); //Normalize vector's length to 1
        center.normalize(); // Centre the circle
        center *= Rad ; // Radius length
        for (int j = 0; j < 3; j++) {
            vertices[i * 3 + j] = center + ofPoint (ofRandom (-rad, rad),
                                                    ofRandom (-rad, rad),
                                                    ofRandom (-rad, rad));
        }
    }
    // Find position for each triangle point
    for (int i = 0; i < nTri; i++){
        ofPoint tempPos1 = vertices[i * 3];
        ofPoint tempPos2 = vertices[i * 3 + 1];
        ofPoint tempPos3 = vertices[i * 3 + 2];
        triangles[i].setup(tempPos1, tempPos2, tempPos3);
        
    }
    
    //Fill the array of triangles' colours
    colors0.resize (nTri);
    colors1.resize (nTri);
    colors2.resize (nTri);

    
    for (int i = 0; i < nTri; i++) {
        // Colour options
        colors0[i] = ofColor (ofRandom (30, 250), ofRandom(50), ofRandom(40), ofRandom(100, 200));
        colors1[i] = ofColor (ofRandom (100, 240), ofRandom(40, 120), ofRandom(20), ofRandom(100, 200));
        colors2[i] = ofColor (ofRandom (5), ofRandom(150), ofRandom(80), ofRandom(100, 200));
    }

}

//--------------------------------------------------------------
void Sphere::update(){
    
    
//    float incomingStep0 = ofMap(incoming0, 90, 55, 0, 0.1, true);
//    float incomingStep1 = ofMap(incoming1, 90, 55, 0, 0.1, true);
//    float incomingStep2 = ofMap(incoming2, 90, 55, 0, 0.1, true);

    
// BASE SPHERE w/ PULSING
    if (incoming0 <= 880 || incoming1 <= 810 || incoming2 <= 790){
    for (int i = 0; i < triangles.size(); i++){
//        float move = ofMap((offset), -1, 1, -0.1, 0.1);
        pulse = ofMap(sin(sinStep), -1, 1, -1, 1);
        triangles[i].position1 += pulse;
        triangles[i].position2 += pulse;
        triangles[i].position3 += pulse;
        }
    }
// OLD PULSING
//    if (incoming0 <= 880 || incoming1 <= 810 || incoming2 <= 790){
//        for (int i = 0; i < triangles.size(); i++){
//            float move = ofMap(sin(sinPulse + (i * 2) / 200), -1, 1, -5, 5);
//            pulse = ofMap(sin(move / 100), -1, 1, -1, 1);
//            triangles[i].position1 += pulse;
//            triangles[i].position2 += pulse;
//            triangles[i].position3 += pulse;
//        }
//    }
    
 //STRETCH USE THIS

    stretch = ofMap((incoming0), 890, 1000, 0, 10, true);

        for (int i = 0; i < triangles.size(); i ++){
            triangles[i].position1 += stretch;// (stretch + triangles[i].random1);


            if (triangles[i].position1.x > triangles[i].origin1.x + 120 || triangles[i].position1.x < triangles[i].origin1.x -120 ||triangles[i].position1.y > triangles[i].origin1.y + 120 || triangles[i].position1.y < triangles[i].origin1.y -120);{// || triangles[i].position1.z > triangles[i].origin1.z + 120 || triangles[i].position1.z < triangles[i].origin1.z -120){
                triangles[i].position1 = triangles[i].origin1 + 120;

            }
                if (stretch <= 0){
                    triangles[i].position1 -= 1;


                    if (triangles[i].position1.x < triangles[i].origin1.x || triangles[i].position1.x > triangles[i].origin1.x|| triangles[i].position1.y < triangles[i].origin1.y || triangles[i].position1.y > triangles[i].origin1.y || triangles[i].position1.z < triangles[i].origin1.z ||  triangles[i].position1.z > triangles[i].origin1.z){
                        triangles[i].position1 = triangles[i].origin1;

                    }
                }
            }
    
//    cout << stretch << endl;
//    cout << "incoming0 = " << incoming0 << endl;
    
    // OLD STRETCH
    
//        if (incoming0 >= 885){
//            stretch = ofMap(sin(sinStep), -1, 1, -100, 100);
//            for(int i = 0; i < triangles.size(); i ++){
//    //            float pulse = ofMap(sin(sinStep + (i * 2)), -1, 1, -10, 10);
//                triangles[i].position1 += stretch;
//
//
//            }
//        }
    
    // BOUNCE
    
//    bounce = ofMap((incoming1), 810, 950, 0, 120, true);
//
//        for (int i = 0; i < triangles.size(); i ++){
//            float time = ofGetElapsedTimef();    //Get time in seconds
//            float angle = time; //Compute angle.
//            triangles[i].position1 += bounce + angle;
//            triangles[i].position2 += bounce + angle;
//            triangles[i].position3 += bounce + angle;
//
//            if (triangles[i].position1.x > triangles[i].origin1.x + 120 && triangles[i].position2.x > triangles[i].origin2.x + 120 && triangles[i].position3.x > triangles[i].origin3.x + 120){
//                triangles[i].position1 = triangles[i].origin1 + 120;
//                triangles[i].position2 = triangles[i].origin2 + 120;
//                triangles[i].position3 = triangles[i].origin3 + 120;
//
//            }
//                if (stretch <= 0){
//                    triangles[i].position1 -= 5;
//                    triangles[i].position2 -= 5;
//                    triangles[i].position3 -= 5;
//
//                    if (triangles[i].position1.x < triangles[i].origin1.x || triangles[i].position1.x > triangles[i].origin1.x|| triangles[i].position1.y < triangles[i].origin1.y || triangles[i].position1.y > triangles[i].origin1.y){
//                        triangles[i].position1 = triangles[i].origin1;
//                        triangles[i].position2 = triangles[i].origin2;
//                        triangles[i].position3 = triangles[i].origin3;
//
//            }
//        }
//    }
//    cout << bounce << endl;
//    cout << "incoming1 = " << incoming1 << endl;



//  OLD BOUNCE
//
//    if (incoming1 >= 810){
//        for(int i = 0; i < triangles.size(); i ++){
//            float bounce = ofMap(sin(sinStep), -1, 1, -5, 5);
//
//            triangles[i].position1 += bounce;
//            triangles[i].position2 += bounce;
//            triangles[i].position3 += bounce;
//        }
//    }
    
// SCATTER USE THIS
    
        for (int i = 0; i < triangles.size(); i ++){
//        float random = ofRandom(incoming2);
        float pulse2 = ofMap(sin(nVert * (i * 5)), -1, 1, -1, 1);
        scatter = ofMap((incoming2 * pulse2), 790, 900, -200, 200, true);

        triangles[i].position1 += scatter;
        triangles[i].position2 += scatter;
        triangles[i].position3 += scatter;

            if (triangles[i].position1.x > triangles[i].origin1.x + 120 && triangles[i].position2.x > triangles[i].origin2.x + 120 && triangles[i].position3.x > triangles[i].origin3.x + 120){
                triangles[i].position1 = triangles[i].origin1 + 120;
                triangles[i].position2 = triangles[i].origin2 + 120;
                triangles[i].position3 = triangles[i].origin3 + 120;

            }
                if (stretch <= 0){
                    triangles[i].position1 -= 5;
                    triangles[i].position2 -= 5;
                    triangles[i].position3 -= 5;


                        if (triangles[i].position1.x < triangles[i].origin1.x && triangles[i].position1.y < triangles[i].origin1.y && triangles[i].position2.x < triangles[i].origin2.x && triangles[i].position2.y < triangles[i].origin2.y && triangles[i].position3.x < triangles[i].origin3.x && triangles[i].position3.y < triangles[i].origin3.y){
                            triangles[i].position1 = triangles[i].origin1;
                            triangles[i].position2 = triangles[i].origin2;
                            triangles[i].position3 = triangles[i].origin3;

            }
        }
    }
//    cout << scatter << endl;
//    cout << "incoming2 = " << incoming2 << endl;

//
// OLD SCATTER
//    bounce = ofMap((incoming1), 810, 950, 0, 50, true);
//
//    if (incoming1 >= 820){
//        for(int i = 0; i < triangles.size(); i ++){
//            float pulse2 = ofMap(sin(nVert + (i * 0.05)), -1, 1, -1, 1);
//            float pulse = ofMap(sin(sinStep + (i * 2)), -1, 1, -1, 1);
//            triangles[i].position1 += pulse2;
//            triangles[i].position2 += pulse2;
//            triangles[i].position3 += pulse2;
//        }
//    }


//    sinStep += incoming1;
//    cout << "incomingStep = " << incomingStep << endl;

    
    for (int i = 0; i < triangles.size(); i++){
        triangles[i].update();

    }
}

//--------------------------------------------------------------
void Sphere::draw(){
    
    ofEnableDepthTest();    //Enable z-buffering
    
// Orange Gradient Option
//  ofBackgroundGradient (ofColor (209, 92, 15), ofColor (31, 13, 1));
    
// Blue Gradient Option
    ofBackgroundGradient (ofColor (9, 0, 176), ofColor (3, 0, 51));
    
    ofPushMatrix();    //Store the coordinate system
    ofTranslate (ofGetWidth() / 2, ofGetHeight() / 2, 0); //Move the coordinate center to screen's center

    float time = ofGetElapsedTimef();    //Get time in seconds
    float angle = time; //Compute angle.
    
    ofRotate(angle, angle, angle, 0);    //Rotate the coordinate system along y-axis
    for (int i = 0; i < nTri; i++) {
        
        triangles[i].draw();
//        ofSetColor(colors0[i]);
                ofSetColor(colors1[i]);
//                ofSetColor(colors2[i]);

        
}

    ofPopMatrix(); //Restore the coordinate system


}
//--------------------------------------------------------------
float Sphere::getAnalogValue(float analogPin0, float analogPin1, float analogPin2){
    
    // Get values for each flex sensor
    incoming0 = analogPin0;
    incoming1 = analogPin1;
    incoming2 = analogPin2;
}

//--------------------------------------------------------------
void Sphere::keyPressed(int key){
    

}

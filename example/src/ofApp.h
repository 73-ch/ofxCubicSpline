#pragma once

#include "ofMain.h"
#include "ofxCubicSpline.h"

using namespace glm;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void windowResized(int w, int h);
private:
    
    ofxCubicSpline spline;
    vector<vec2> key_points;
    ofVboMesh mesh;
    
    bool point_mode;
};

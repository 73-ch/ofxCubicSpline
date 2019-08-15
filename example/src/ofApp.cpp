#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    for (int i = 0; i < 30; i++) {
        key_points.push_back(vec2(ofGetWidth() / 20 * i, ofRandom(ofGetHeight())));
    }
    
    spline.setData(key_points);
    
    mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (ofGetFrameNum() % 90 == 0) {
        key_points.clear();
        mesh.clear();
        if (point_mode) {
            for (int i = 0; i < 30; i++) {
                key_points.push_back(vec2(ofGetWidth() / 20 * i, ofRandom(ofGetHeight())));
            }
        } else {
            key_points.push_back(vec2(0, ofRandom(ofGetHeight())));
            key_points.push_back(vec2(ofGetWidth(), ofRandom(ofGetHeight())));
            
            
            for (int i = 0; i < 30; i++) {
                key_points.push_back(vec2(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())));
            }
        }
        
        spline.setData(key_points);
        
        for (int i = 0; i < ofGetWidth(); i++) {
            mesh.addVertex(vec3(i,spline.at(i), 0.));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAlphaBlending();
    
    ofSetColor(100, 10, 200);
    for (auto k : key_points) {
        ofDrawCircle(k, 10);
    }
    
    ofSetColor(255);
    
    mesh.draw(OF_MESH_POINTS);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'q') {
        mesh.setMode(OF_PRIMITIVE_POINTS);
    } else if (key == 'w') {
        mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    } else if (key == 'e') {
        point_mode = !point_mode;
    }
}

void ofApp::windowResized(int w, int h) {
    
}


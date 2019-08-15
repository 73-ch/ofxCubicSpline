#pragma once

#include "ofMain.h"

using namespace glm;

class ofxCubicSpline {
    vector<vec3> points;
    vector<float> ks;
    
    bool enable = false;
    
    void getNaturalKs();
    void solve(vector<vector<float>> m);
    
public:
    void setData(const vector<float> xs, const vector<float> ys);
    void setData(const vector<vec2> input);
    
    float at(const float x) const;
};

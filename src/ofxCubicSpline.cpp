#include "ofxCubicSpline.h"

void ofxCubicSpline::setData(const vector<float> xs, const vector<float> ys) {
    
    if (xs.size() != ys.size()) {
        cout << "input ys length is not same as xs length." << endl;
        return;
    }
    
    points.clear();
    
    for (int i = 0; i < xs.size(); i++) {
        points.push_back(vec3(xs[i], ys[i], 0.0));
    }
    
    getNaturalKs();
}

void ofxCubicSpline::setData(const vector<vec2> input) {
    auto start = std::chrono::system_clock::now();
    points.clear();
    
    for (auto i : input) {
        points.push_back(vec3(i.x, i.y, 0.0));
    }
    
    getNaturalKs();
}

float ofxCubicSpline::at(const float x) const  {
    int i = 1;
    while (points[i].x < x) i++;
    
    auto b = points[i - 1], c = points[i];
    
    const float t = (x - b.x) / (c.x - b.x);
    return (1.0 - t) * b.y + t * c.y + t * (1.0 - t) * ((b.z * (c.x - b.x) - (c.y - b.y)) * (1.0 - t) + (-c.z * (c.x - b.x) + (c.y - b.y)) * t);
}

void ofxCubicSpline::getNaturalKs() {
    sort(points.begin(), points.end(), [&](vec3 x, vec3 y){return x.x < y.x;});
    
    const int n = points.size() - 1;
    vector<vector<float>> m(n+1,vector<float>(n+2,0));
    
    vec2 a, b, c;
    
    for (int i = 1; i < n; i++) {
        a = points[i-1];
        b = points[i];
        c = points[i + 1];
        
        m[i][i - 1] = 1.0 / (b.x - a.x);
        m[i][i] = 2.0 * (1 / (b.x - a.x) + 1.0 / (c.x - b.x));
        m[i][i + 1] = 1.0 / (c.x - b.x);
        m[i][n + 1] = 3.0 * ((b.y - a.y) / ((b.x - a.x) * (b.x - a.x)) + (c.y - b.y) / ((c.x - b.x) * (c.x - b.x)));
    }
    
    auto f = points[0], s = points[1];
    
    m[0][0] = 2 / (s.x - f.x);
    m[0][1] = 1 / (s.x - f.x);
    m[0][n + 1] = (3 * (s.y - f.y)) / ((s.x - f.x) * (s.x - f.x));
    
    auto bl = points[n - 1], l = points[n];
    
    m[n][n - 1] = 1.0 / (l.x - bl.x);
    m[n][n] = 2.0 / (l.x - bl.x);
    m[n][n + 1] = (3.0 * (l.y - bl.y)) / ((l.x - bl.x) * (l.x - bl.x));
    
    solve(m);
}

void ofxCubicSpline::solve(vector<vector<float>> m) {
    const int p = m.size();
    for (int k = 0; k < p; k++) {
        int i_max = 0;
        float vali = -INFINITY;
        for (int i = k; i < p; i++)
            if (m[i][k] > vali) {
                i_max = i;
                vali = m[i][k];
            }
        swap(m[k], m[i_max]);
        
        for (int i = k + 1; i < p; i++) {
            for (int j = k + 1; j < p + 1; j++) {
                m[i][j] = m[i][j] - m[k][j] * (m[i][k] / m[k][k]);
            }
            m[i][k] = 0.0;
        }
    }
    
    for (int i = p - 1; i >= 0; i--) {
        const float v = m[i][p] / m[i][i];
        points[i].z = v;
        for (int j = i - 1; j >= 0; j--) {
            m[j][p] -= m[j][i] * v;
            m[j][i] = 0;
        }
    }
}


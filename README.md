# ofxCubicSpline

This is [Ivan Kuckir's cubic spline implementation](http://blog.ivank.net/interpolation-with-cubic-splines.html) for openFrameworks and this is also inspired by [cubic-spline - npm](https://www.npmjs.com/package/cubic-spline).



![example](https://github.com/73-ch/ofxCubicSpline/wiki/images/example.gif)



## How to use

```c++
ofxCubicSpline cubic;
vector<glm::vec2> points; // key points
points.push_back(glm::vec2(0,225));
points.push_back(glm::vec2(223,15));
// :  some points
// :
-----------------

// setup
cubic.setData(points);

// get Y at arbitrary X
float y = cubic.at(float x);

```


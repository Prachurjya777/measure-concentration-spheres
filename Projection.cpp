#include "Projection.h"
#include <cmath>

static const int WIDTH  = 1400;
static const int HEIGHT = 600;
static const int LEFT_W = WIDTH/3;
static const int MID_W  = WIDTH/3;

static float t = 0.f;               
static const float tilt = 0.25f;      

sf::Vector2f diskToScreen(float x,float y)
{
    float s = LEFT_W*0.4f;
    return {LEFT_W/2 + x*s, HEIGHT/2 - y*s};
}

sf::Vector2f ballToScreen(float x,float y,float z)
{
    float a = t;
    float x1 =  x*cos(a) - z*sin(a);
    float z1 =  x*sin(a) + z*cos(a);
    float y1 =  y;

    
    float y2 =  y1*cos(tilt) - z1*sin(tilt);
    float z2 =  y1*sin(tilt) + z1*cos(tilt);

    float xr = x1;
    float yr = y2;
    float zr = z2;

    const float D = 2.5f;        
    float inv = 1.0f / (D - zr);

    float X = xr * inv;
    float Y = yr * inv;

    float s = MID_W * 0.9f;

    return {
        LEFT_W + MID_W/2 + X * s,
        HEIGHT/2 - Y * s
    };
}

sf::Vector2f graphToScreen(int i,float r)
{
    return {LEFT_W + MID_W + 20 + i*0.08f,
            HEIGHT - 40 - r*(HEIGHT-80)};
}

void advanceCamera(float dt)
{
    t += 0.4f * dt;  
}

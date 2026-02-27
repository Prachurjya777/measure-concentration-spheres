#include "Sampler.h"
#include <random>
#include <cmath>

static std::mt19937 rng(std::random_device{}());
static std::uniform_real_distribution<float> U(0.f,1.f);
static float rand01(){ return U(rng); }
static const float PI=3.14159265358979323846f;

void sampleDisk(std::vector<P2>& disk){
    float u=rand01(),t=2*PI*rand01(),r=sqrt(u);
    disk.push_back({r*cos(t),r*sin(t),r});
}

void sampleBall(std::vector<P3>& ball){
    float u=rand01(),t=2*PI*rand01(),p=acos(2*rand01()-1),r=pow(u,1.f/3.f);
    ball.push_back({r*sin(p)*cos(t),r*sin(p)*sin(t),r*cos(p),r});
}

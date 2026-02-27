#pragma once
#include <vector>

struct Sample2D
{
    float x;
    float y;
    float radius;
};

struct Sample3D
{
    float x;
    float y;
    float z;
    float radius;
};

void sampleDisk(std::vector<Sample2D>& samples);
void sampleBall(std::vector<Sample3D>& samples);
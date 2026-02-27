#pragma once
#include <vector>

struct P2{ float x,y,r; };
struct P3{ float x,y,z,r; };

void sampleDisk(std::vector<P2>& disk);
void sampleBall(std::vector<P3>& ball);

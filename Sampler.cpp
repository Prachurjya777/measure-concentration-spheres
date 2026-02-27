#include "Sampler.h"
#include <random>
#include <cmath>

namespace
{
    // Random engine
    std::mt19937 rng(std::random_device{}());

    // Uniform distribution in [0,1)
    std::uniform_real_distribution<float> uniform01(0.0f, 1.0f);

    inline float rand01()
    {
        return uniform01(rng);
    }

    constexpr float PI = 3.14159265358979323846f;
}

void sampleDisk(std::vector<Sample2D>& samples)
{
    const float u = rand01();                 
    const float theta = 2.0f * PI * rand01();
    const float r = std::sqrt(u);             

    samples.push_back({
        r * std::cos(theta),
        r * std::sin(theta),
        r
    });
}

void sampleBall(std::vector<Sample3D>& samples)
{
    const float u = rand01();
    const float theta = 2.0f * PI * rand01();
    const float phi = std::acos(2.0f * rand01() - 1.0f);
    const float r = std::cbrt(u);            

    const float sinPhi = std::sin(phi);

    samples.push_back({
        r * sinPhi * std::cos(theta),
        r * sinPhi * std::sin(theta),
        r * std::cos(phi),
        r
    });
}
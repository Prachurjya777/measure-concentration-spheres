#include "Projection.h"
#include <cmath>

namespace
{
    constexpr int WIDTH  = 1400;
    constexpr int HEIGHT = 600;
    constexpr int LEFT_W = WIDTH / 3;
    constexpr int MID_W  = WIDTH / 3;

    float angle = 0.f;
    constexpr float tilt = 0.25f;
}

sf::Vector2f diskToScreen(float x, float y)
{
    float scale = LEFT_W * 0.4f;
    return {
        LEFT_W / 2.f + x * scale,
        HEIGHT / 2.f - y * scale
    };
}

sf::Vector2f ballToScreen(float x, float y, float z)
{
    float c = std::cos(angle);
    float s = std::sin(angle);

    float x1 = x * c - z * s;
    float z1 = x * s + z * c;
    float y1 = y;

    float ct = std::cos(tilt);
    float st = std::sin(tilt);

    float y2 = y1 * ct - z1 * st;
    float z2 = y1 * st + z1 * ct;

    const float D = 2.5f;
    float inv = 1.f / (D - z2);

    float X = x1 * inv;
    float Y = y2 * inv;

    float scale = MID_W * 0.9f;

    return {
        LEFT_W + MID_W / 2.f + X * scale,
        HEIGHT / 2.f - Y * scale
    };
}

sf::Vector2f graphToScreen(int index, float radius)
{
    return {
        LEFT_W + MID_W + 20.f + index * 0.08f,
        HEIGHT - 40.f - radius * (HEIGHT - 80.f)
    };
}

void advanceCamera(float dt)
{
    angle += 0.4f * dt;
}
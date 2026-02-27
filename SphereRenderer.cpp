#include "SphereRenderer.h"
#include "Projection.h"
#include <cmath>

namespace
{
    constexpr float PI = 3.14159265358979323846f;

    void drawArc(sf::RenderWindow& window, const sf::VertexArray& arc)
    {
        window.draw(arc);
        sf::Transform T;
        T.translate(0.7f, 0.7f);
        window.draw(arc, T);
    }
}

void drawSphere(sf::RenderWindow& window)
{
    sf::VertexArray outline(sf::LineStrip, 200);

    for (int i = 0; i < 200; ++i)
    {
        float t = 2.f * PI * i / 199.f;
        outline[i].position = ballToScreen(std::cos(t), std::sin(t), 0.f);
        outline[i].color = sf::Color::White;
    }

    window.draw(outline);

    sf::Transform T;
    T.translate(0.7f, 0.7f);
    window.draw(outline, T);
}

void drawLatitudes(sf::RenderWindow& window)
{
    const int LAT = 7;
    const int LON = 10;

    for (int i = 1; i < LAT; ++i)
    {
        float v = PI * i / LAT;
        float z = std::cos(v);
        float r = std::sin(v);

        sf::VertexArray arc(sf::LineStrip, 160);

        for (int k = 0; k < 160; ++k)
        {
            float u = 2.f * PI * k / 159.f;
            float x = r * std::cos(u);
            float y = r * std::sin(u);

            arc[k].position = ballToScreen(x, y, z);
            arc[k].color = sf::Color::White;
        }

        drawArc(window, arc);
    }

    for (int j = 0; j < LON; ++j)
    {
        float u = 2.f * PI * j / LON;

        sf::VertexArray arc(sf::LineStrip, 160);

        for (int k = 0; k < 160; ++k)
        {
            float v = PI * k / 159.f;
            float x = std::sin(v) * std::cos(u);
            float y = std::sin(v) * std::sin(u);
            float z = std::cos(v);

            arc[k].position = ballToScreen(x, y, z);
            arc[k].color = sf::Color::White;
        }

        drawArc(window, arc);
    }
}
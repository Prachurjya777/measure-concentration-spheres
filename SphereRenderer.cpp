#include "SphereRenderer.h"
#include "Projection.h"
#include <cmath>

static const float PI = 3.14159265358979323846f;

static void drawArc(sf::RenderWindow& window, sf::VertexArray& arc)
{
    // draw twice for thickness
    for(int pass=0; pass<2; pass++)
    {
        sf::Transform T;
        if(pass==1) T.translate(0.7f, 0.7f);

        for(unsigned i=0;i<arc.getVertexCount();i++)
            arc[i].color = sf::Color::White;

        window.draw(arc, T);
    }
}

static void drawLatitudesLayer(sf::RenderWindow& window)
{
    for(int i=1;i<=6;i++)
    {
        float z = -1 + 2.f*i/7.f;
        float r = sqrt(1 - z*z);

        sf::VertexArray arc(sf::LineStrip,150);
        for(int k=0;k<150;k++)
        {
            float t = 2*PI*k/149;
            float x = r*cos(t);
            float y = r*sin(t);

            arc[k].position = ballToScreen(x,y,z);
        }
        drawArc(window, arc);
    }
}

static void drawLongitudesLayer(sf::RenderWindow& window)
{
    for(int i=0;i<10;i++)
    {
        float phi = 2*PI*i/10.f;

        sf::VertexArray arc(sf::LineStrip,150);
        for(int k=0;k<150;k++)
        {
            float theta = PI*k/149;
            float x = sin(theta)*cos(phi);
            float y = sin(theta)*sin(phi);
            float z = cos(theta);

            arc[k].position = ballToScreen(x,y,z);
        }
        drawArc(window, arc);
    }
}

void drawSphere(sf::RenderWindow& window)
{
    sf::VertexArray outline(sf::LineStrip,200);
    for(int i=0;i<200;i++)
    {
        float t = 2*PI*i/199;
        float x = cos(t);
        float y = sin(t);
        float z = 0;

        outline[i].position = ballToScreen(x,y,z);
        outline[i].color = sf::Color::White;
    }

    // thickness
    window.draw(outline);
    sf::Transform T;
    T.translate(0.7f,0.7f);
    window.draw(outline,T);
}

void drawLatitudes(sf::RenderWindow& window)
{
    drawLatitudesLayer(window);
    drawLongitudesLayer(window);
}

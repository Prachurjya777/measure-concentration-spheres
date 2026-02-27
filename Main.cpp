#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Sampler.h"
#include "Projection.h"
#include "SphereRenderer.h"

std::vector<P2> disk;
std::vector<P3> ball;
sf::Clock frameClock;


bool running = false;
int index = 0;
const int MAX = 6000;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400,600),"Concentration of Measure");

    sf::Font font;
    font.loadFromFile("arial.ttf");

    // ---- Start button ----
    sf::RectangleShape button({120,40});
    button.setPosition(10,10);
    button.setFillColor(sf::Color::Transparent);
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::White);

    sf::Text text("START",font,18);
    text.setPosition(30,18);
    text.setFillColor(sf::Color::White);

    // ---- Labels ----
    sf::Text label2D("2-Ball", font, 20);
    label2D.setFillColor(sf::Color::White);
    label2D.setPosition(1400/6 - 20, 520);


    sf::Text label3D("3-Ball", font, 20);
    label3D.setFillColor(sf::Color::White);
    label3D.setPosition(1400/2 - 20, 520);

    sf::Text labelY("Distance from center", font, 20);
    labelY.setFillColor(sf::Color::White);
    labelY.setRotation(-90);
    labelY.setPosition(1400 - 160, 420);

    sf::Clock clock;
    float accumulator = 0.f;
    float simTime = 0.f;

    while(window.isOpen())
    {
        sf::Event e;
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed) window.close();

            if(e.type == sf::Event::MouseButtonPressed)
            {
                if(button.getGlobalBounds().contains(e.mouseButton.x,e.mouseButton.y))
                {
                    disk.clear();
                    ball.clear();
                    index = 0;
                    running = true;
                    simTime = 0.f;
                    accumulator = 0.f;
                    clock.restart();
                }
            }
        }

        if(running && index < MAX)
        {
            float dt = clock.restart().asSeconds();
            simTime += dt;

            float ramp = 1.f / (1.f + exp(-1.2f * (simTime - 2.f)));
            float rate = 600.f * ramp + 30.f;

            accumulator += dt * rate;

            while(accumulator >= 1.f && index < MAX)
            {
                if(index % 2 == 0) sampleDisk(disk);
                else              sampleBall(ball);
                index++;
                accumulator -= 1.f;
            }
        }


        window.clear(sf::Color::Black);

        sf::CircleShape diskShape(1400/3 * 0.4f);
        diskShape.setPosition(1400/6 - diskShape.getRadius(), 300 - diskShape.getRadius());
        diskShape.setFillColor(sf::Color::Transparent);
        diskShape.setOutlineThickness(2);
        diskShape.setOutlineColor(sf::Color::White);
        window.draw(diskShape);

        for(auto &p : disk)
        {
            sf::CircleShape d(2);
            d.setFillColor(sf::Color(220, 60, 60));
            d.setPosition(diskToScreen(p.x,p.y));
            window.draw(d);
        }

        drawSphere(window);
        drawLatitudes(window);

        for(auto &p : ball)
        {
            sf::CircleShape d(2);
            d.setFillColor(sf::Color(90, 60, 220));
            d.setPosition(ballToScreen(p.x,p.y,p.z));
            window.draw(d);
        }

        for(int i=0;i<disk.size();i++)
        {
            sf::CircleShape d(2);
            d.setFillColor(sf::Color(220, 60, 60));
            d.setPosition(graphToScreen(i,disk[i].r));
            window.draw(d);
        }

        for(int i=0;i<ball.size();i++)
        {
            sf::CircleShape d(2);
            d.setFillColor(sf::Color(sf::Color(90, 60, 220)));
            d.setPosition(graphToScreen(i,ball[i].r));
            window.draw(d);
        }

        window.draw(button);
        window.draw(text);

        window.draw(label2D);
        window.draw(label3D);
        window.draw(labelY);

        float dtFrame = frameClock.restart().asSeconds();
        advanceCamera(dtFrame);

        window.display();
    }
}

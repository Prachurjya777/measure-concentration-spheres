#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

#include "Sampler.h"
#include "Projection.h"
#include "SphereRenderer.h"

namespace
{
    constexpr int WINDOW_WIDTH  = 1400;
    constexpr int WINDOW_HEIGHT = 600;
    constexpr int MAX_SAMPLES   = 6000;
}

int main()
{
    std::vector<Sample2D> diskSamples;
    std::vector<Sample3D> ballSamples;

    bool running = false;
    int sampleIndex = 0;

    sf::RenderWindow window(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Concentration of Measure"
    );

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
        return -1;

    sf::RectangleShape button({120.f, 40.f});
    button.setPosition(10.f, 10.f);
    button.setFillColor(sf::Color::Transparent);
    button.setOutlineThickness(2.f);
    button.setOutlineColor(sf::Color::White);

    sf::Text buttonText("START", font, 18);
    buttonText.setPosition(30.f, 18.f);
    buttonText.setFillColor(sf::Color::White);

    sf::Text label2D("2-Ball", font, 20);
    label2D.setFillColor(sf::Color::White);
    label2D.setPosition(WINDOW_WIDTH / 6.f - 20.f, 520.f);

    sf::Text label3D("3-Ball", font, 20);
    label3D.setFillColor(sf::Color::White);
    label3D.setPosition(WINDOW_WIDTH / 2.f - 20.f, 520.f);

    sf::Text labelY("Distance from center", font, 20);
    labelY.setFillColor(sf::Color::White);
    labelY.setRotation(-90.f);
    labelY.setPosition(WINDOW_WIDTH - 160.f, 420.f);

    sf::Clock simClock;
    sf::Clock frameClock;

    float accumulator = 0.f;
    float simTime = 0.f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (button.getGlobalBounds().contains(
                        static_cast<float>(event.mouseButton.x),
                        static_cast<float>(event.mouseButton.y)))
                {
                    diskSamples.clear();
                    ballSamples.clear();
                    sampleIndex = 0;
                    running = true;
                    simTime = 0.f;
                    accumulator = 0.f;
                    simClock.restart();
                }
            }
        }

        if (running && sampleIndex < MAX_SAMPLES)
        {
            float dt = simClock.restart().asSeconds();
            simTime += dt;

            float ramp = 1.f / (1.f + std::exp(-1.2f * (simTime - 2.f)));
            float rate = 600.f * ramp + 30.f;

            accumulator += dt * rate;

            while (accumulator >= 1.f && sampleIndex < MAX_SAMPLES)
            {
                if (sampleIndex % 2 == 0)
                    sampleDisk(diskSamples);
                else
                    sampleBall(ballSamples);

                sampleIndex++;
                accumulator -= 1.f;
            }
        }

        window.clear(sf::Color::Black);

        sf::CircleShape diskShape(WINDOW_WIDTH / 3.f * 0.4f);
        diskShape.setPosition(
            WINDOW_WIDTH / 6.f - diskShape.getRadius(),
            300.f - diskShape.getRadius()
        );
        diskShape.setFillColor(sf::Color::Transparent);
        diskShape.setOutlineThickness(2.f);
        diskShape.setOutlineColor(sf::Color::White);
        window.draw(diskShape);

        for (const auto& p : diskSamples)
        {
            sf::CircleShape d(2.f);
            d.setFillColor(sf::Color(220, 60, 60));
            d.setPosition(diskToScreen(p.x, p.y));
            window.draw(d);
        }

        drawSphere(window);
        drawLatitudes(window);

        for (const auto& p : ballSamples)
        {
            sf::CircleShape d(2.f);
            d.setFillColor(sf::Color(90, 60, 220));
            d.setPosition(ballToScreen(p.x, p.y, p.z));
            window.draw(d);
        }

        for (std::size_t i = 0; i < diskSamples.size(); ++i)
        {
            sf::CircleShape d(2.f);
            d.setFillColor(sf::Color(220, 60, 60));
            d.setPosition(graphToScreen(static_cast<int>(i), diskSamples[i].radius));
            window.draw(d);
        }

        for (std::size_t i = 0; i < ballSamples.size(); ++i)
        {
            sf::CircleShape d(2.f);
            d.setFillColor(sf::Color(90, 60, 220));
            d.setPosition(graphToScreen(static_cast<int>(i), ballSamples[i].radius));
            window.draw(d);
        }

        window.draw(button);
        window.draw(buttonText);
        window.draw(label2D);
        window.draw(label3D);
        window.draw(labelY);

        float dtFrame = frameClock.restart().asSeconds();
        advanceCamera(dtFrame);

        window.display();
    }

    return 0;
}
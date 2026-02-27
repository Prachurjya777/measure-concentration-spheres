#pragma once
#include <SFML/Graphics.hpp>

sf::Vector2f diskToScreen(float x,float y);
sf::Vector2f ballToScreen(float x,float y,float z);
sf::Vector2f graphToScreen(int i,float r);

void advanceCamera(float dt);


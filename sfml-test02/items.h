#pragma once
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;

void shapes_create(int count);
sf::Shape *shapes_add(sf::Shape *shape);
void shapes_update(float delta_time);
void shapes_render(sf::RenderWindow &target_window);
void shapes_HandleEvent(sf::Event event);
void shapes_free();

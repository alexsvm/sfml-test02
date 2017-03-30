#pragma once
#include <list>
#include <SFML/Graphics.hpp>
using namespace std;

list<sf::Shape> shapes;

void shapes_update();
void shapes_render();
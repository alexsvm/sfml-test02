#include "items.h"


list<sf::Shape*> shapes;

void shapes_create(int count) {
	sf::CircleShape *c;
	for (; count > 0; count--) {
		c = new sf::CircleShape(100);
		c->setOutlineColor(sf::Color::Green);
		c->setFillColor(sf::Color::Transparent);
		c->setOutlineThickness(3);
		c->setPosition(rand() % 600, rand() % 600);
		shapes.push_back(c);
	}
}

sf::Shape *shapes_add(sf::Shape *shape) {
	shapes.push_back(shape);
	return shape;
}

void shapes_update(float delta_time) {

}

void shapes_render(sf::RenderWindow &target_window) {
	list<sf::Shape*>::iterator it = shapes.begin();
	for (; it != shapes.end(); ++it)
		target_window.draw(**it);;
}

void shapes_HandleEvent(sf::Event event) {

}

void shapes_free() {
	shapes.clear();
}

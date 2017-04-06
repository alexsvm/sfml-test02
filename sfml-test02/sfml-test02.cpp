//#include <SFML/Graphics.hpp>
//#include "main.h"
#include "sfGUI.h"
#include "items.h"

int main() {
	float _mx, _my;

	srand(time(nullptr));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow render_window(sf::VideoMode(800, 800), "Hello world!", sf::Style::Default, settings); // Create SFML's window.

	sfGUI sfgui;

	render_window.resetGLStates();
	
	shapes_init();
	//
#define TCR 200
	sf::Color color;
	sf::CircleShape test_circle = sf::CircleShape(TCR, 16);
	color.r = 0;
	color.g = 255;
	color.b = 0;
	color.a = 200;
	test_circle.setFillColor(color);

	color.r = 255;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	test_circle.setOutlineColor(color);
	test_circle.setOutlineThickness(3);
	test_circle.setOrigin(TCR, TCR);
	test_circle.setPosition(1000, 500);

	//
	settings = render_window.getSettings();
	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;

	// Main loop
	sf::Event event;
	sf::Clock clock;
	float sec;

	while (render_window.isOpen()) {
		while (render_window.pollEvent(event)) { // Event processing.
			//
			sfgui.HandleEvent(event);
			shapes_HandleEvent(event, render_window);
			//
			if (event.type == sf::Event::Closed) { // If window is about to be closed, leave program.
				return 0;
			}
			//
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				render_window.setView(sf::View(visibleArea));
				
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Up) {
					sf::View view = render_window.getView();
					view.move(0, -50);
					render_window.setView(view);
				}
				if (event.key.code == sf::Keyboard::Right) {
					sf::View view = render_window.getView();
					view.move(50, 0);
					render_window.setView(view);
				}
				if (event.key.code == sf::Keyboard::Down) {
					sf::View view = render_window.getView();
					view.move(0, 50);
					render_window.setView(view);
				}
				if (event.key.code == sf::Keyboard::Left) {
					sf::View view = render_window.getView();
					view.move(-50, 0);
					render_window.setView(view);
				}
			} // KeyPressed
			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					_mx = event.mouseButton.x;
					_my = event.mouseButton.y;
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					;
				}
			} // <= MouseButtonPressed
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					;
				}
			} // <=MouseButtonReleased
			if (event.type == sf::Event::MouseMoved) {
				if (!shapes_selected() && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
					sf::Vector2i mc = sf::Mouse::getPosition();
					sf::View view = render_window.getView();
					view.move(_mx - event.mouseMove.x, _my - event.mouseMove.y);
					render_window.setView(view);
					_mx = event.mouseMove.x;
					_my = event.mouseMove.y;
				}
			} // <=MouseMoved
		}

		// Update app state
		sec = clock.restart().asSeconds();
		sfgui.Update(sec); // Update SFGUI with elapsed seconds since last call.
		shapes_update(sec);

		// Rendering.
		render_window.clear();
		render_window.draw(test_circle);
		shapes_render(render_window);
		sfgui.Render(render_window);

		render_window.display();
	}

	shapes_free();

	return 0;
}
//#include <SFML/Graphics.hpp>
//#include "main.h"
#include "sfGUI.h"
#include "items.h"
#include "ColorConsole.h"

#define minimum_frame_per_seconds 30

int main() {
	float _mx, _my;

	srand(time(nullptr));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow render_window(sf::VideoMode(800, 800), "Hello world!", sf::Style::Default, settings); // Create SFML's window.

	sfGUI sfgui;

	render_window.resetGLStates();
	
	shapes_init();

	settings = render_window.getSettings();
	std::cout << "depth bits:" << settings.depthBits << std::endl;
	std::cout << "stencil bits:" << settings.stencilBits << std::endl;
	std::cout << "antialiasing level:" << settings.antialiasingLevel << std::endl;
	std::cout << "version:" << settings.majorVersion << "." << settings.minorVersion << std::endl;
	std::cout << cyan << "cyan " << magenta << "magenta " << yellow << "yellow " << grey << "grey "<< endl;
	std::cout << light_cyan << "light_cyan " << light_magenta << "light_magenta " << light_yellow << "light_yellow " << white << "white"<< endl;
	std::cout << light_red << " red " << on_blue << " on blue " << grey << on_black << "back in black " << endl;

	// ============================ Main loop ======================================
	sf::Event event;
	sf::Clock clock;
	sf::Time timeSinceLastUpdate;
	sf::Time timePerFrame = sf::seconds(1.f / minimum_frame_per_seconds);
	
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
		} // <= Event processing

		timeSinceLastUpdate = clock.restart();
		while (timeSinceLastUpdate > timePerFrame) {
			timeSinceLastUpdate -= timePerFrame;
			sfgui.Update(timeSinceLastUpdate);
			shapes_update(timeSinceLastUpdate);
		}
		sfgui.Update(timeSinceLastUpdate);
		shapes_update(timeSinceLastUpdate);

		// Rendering.
		render_window.clear();

		shapes_render(render_window);
		sfgui.Render(render_window);

		render_window.display();
	}

	shapes_free();

	return 0;
}
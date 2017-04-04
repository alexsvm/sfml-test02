#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include "sfGUI.h"
#include "items.h"

int main() {
	
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow render_window(sf::VideoMode(800, 600), "Hello world!", sf::Style::Close, settings); // Create SFML's window.
	sfGUI sfgui;

	render_window.resetGLStates();
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	sf::CircleShape shape(50);
	shape.setFillColor(sf::Color(150, 50, 250));
	// set a 10-pixel wide orange outline
	shape.setOutlineThickness(10);
	shape.setOutlineColor(sf::Color(250, 150, 100));
	shape.setPosition(400, 400);
	/////////////////////////////////////////////////////////////////////////////////////////////

	shapes_create(10);
	
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
			shapes_HandleEvent(event);
			//
			if (event.type == sf::Event::Closed) { // If window is about to be closed, leave program.
				return 0;
			}
			//
		}

		// Update app state
		sec = clock.restart().asSeconds();
		sfgui.Update(sec); // Update SFGUI with elapsed seconds since last call.
		shapes_update(sec);

		// Rendering.
		render_window.clear();

		render_window.draw(shape);
		shapes_render(render_window);
		sfgui.Render(render_window);

		render_window.display();
	}

	shapes_free();

	return 0;
}
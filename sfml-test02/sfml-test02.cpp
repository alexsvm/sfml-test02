#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include "sfGUI.h";

int main() {
	
	sf::RenderWindow render_window(sf::VideoMode(800, 600), "Hello world!", sf::Style::Close); // Create SFML's window.
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


	// Main loop!
	sf::Event event;
	sf::Clock clock;

	while (render_window.isOpen()) {
		while (render_window.pollEvent(event)) { // Event processing.

			sfgui.HandleEvent(event);

			if (event.type == sf::Event::Closed) { // If window is about to be closed, leave program.
				return 0;
			}
		}

		sfgui.Update(clock.restart().asSeconds()); // Update SFGUI with elapsed seconds since last call.


		// Rendering.
		render_window.clear();

		render_window.draw(shape);

		sfgui.Render(render_window);

		render_window.display();
	}

	return 0;
}
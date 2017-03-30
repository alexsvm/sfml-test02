#pragma once
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

class sfGUI {
public:
	sfGUI(const sfGUI&) = delete;
	sfGUI& operator=(const sfGUI&) = delete;
	sfGUI() {
		label = sfg::Label::Create("Hello world!");
		sfg::Label::Ptr _label = label;
		
		button = sfg::Button::Create("Greet SFGUI!");
		button->GetSignal(sfg::Widget::OnLeftClick).Connect([_label] { _label->SetText("Hello SFGUI, pleased to meet you!"); });

		box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.0f);
		box->Pack(label);
		box->Pack(button, false);

		window = sfg::Window::Create();
		window->SetTitle("Hello world!"); 
		window->SetStyle(sfg::Window::TOPLEVEL); //|| sfg::Window::SHADOW || sfg::Window::TITLEBAR || sfg::Window::BACKGROUND

		window->Add(box);

		desktop.Add(window);

	};
	void HandleEvent(sf::Event event) {
		desktop.HandleEvent(event);
	}
	void Update(float delta_time) {
		desktop.Update(delta_time);
	}
	void Render(sf::RenderWindow &target_window) {
		_sfgui.Display(target_window);
	}
private:
	sfg::SFGUI _sfgui;

	sfg::Button::Ptr button;
	sfg::Label::Ptr label;
	sfg::Box::Ptr box;

	sfg::Window::Ptr window;
	sfg::Desktop desktop;
};

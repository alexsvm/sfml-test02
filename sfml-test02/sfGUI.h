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

		//std::string str = ;
		label2 = sfg::Label::Create("Click count = " + std::to_string(click_count));
		//sfg::Label::Ptr _label = label;
		
		button = sfg::Button::Create("Greet SFGUI!");
		button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::button_OnClick, this));
		button2 = sfg::Button::Create("ClickMe!");
		button2->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::button2_OnClick, this));
			//Connect([_label] { _label->SetText("Hello SFGUI, pleased to meet you!"); });

		box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.0f);
		box->Pack(label);
		box->Pack(button, false);
		box->Pack(label2);
		box->Pack(button2, false);

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
	int click_count = 0;
	sfg::SFGUI _sfgui;

	sfg::Button::Ptr button;
	sfg::Button::Ptr button2;
	sfg::Label::Ptr label;
	sfg::Label::Ptr label2;
	sfg::Box::Ptr box;

	sfg::Window::Ptr window;
	sfg::Desktop desktop;

	void button_OnClick() {
		label->SetText("Hello SFGUI, pleased to meet you!");
	}
	void button2_OnClick() {
		++click_count;
		//std::string str = ;
		label2->SetText("Click count = " + std::to_string(click_count));
	}
};

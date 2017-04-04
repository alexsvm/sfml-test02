#pragma once
#include <SFGUI\SFGUI.hpp>
#include <SFGUI\Widgets.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "items.h"

class sfGUI {
public:
	sfGUI(const sfGUI&) = delete;
	sfGUI& operator=(const sfGUI&) = delete;
	sfGUI() {

		label = sfg::Label::Create("Hello world!");
		label2 = sfg::Label::Create("Click count = " + std::to_string(click_count));
		
		button = sfg::Button::Create("Greet SFGUI!");
		button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::button_OnClick, this));
		button2 = sfg::Button::Create("ClickMe!");
		button2->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::button2_OnClick, this));
		btnCreateCircleShape = sfg::Button::Create("Create");
		btnCreateCircleShape->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::btnCreateCircleShape_OnClick, this));
		entry_n = sfg::Entry::Create();
		entry_n->SetMaximumLength(3);
		entry_r = sfg::Entry::Create();
		entry_r->SetMaximumLength(4);
		//lambda - Connect([_label] { _label->SetText("Hello SFGUI, pleased to meet you!"); });

		box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.0f);
		box->Pack(label);
		box->Pack(button, false);
		
		//auto separator = sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL); // Create a separator.
		box->Pack(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL), false, true); // Add separator to box and set not to expand.
		box->Pack(label2);
		box->Pack(button2, false);
		
		box->Pack(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL), false, true); // Add separator to box and set not to expand.
		box->Pack(sfg::Label::Create("Create circle shape:"));
		sfg::Box::Ptr box2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.0f);
		box2->Pack(sfg::Label::Create("Sides:"));
		box2->Pack(entry_n);
		box->Pack(box2);
		box2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.0f);
		box2->Pack(sfg::Label::Create("Radius:"));
		box2->Pack(entry_r);
		box->Pack(box2);
		box->Pack(btnCreateCircleShape, false);

		window = sfg::Window::Create();
		window->SetTitle("Hello world!"); 
		window->SetStyle(0b00001011); //|| sfg::Window::TOPLEVEL sfg::Window::SHADOW || sfg::Window::TITLEBAR || sfg::Window::BACKGROUND
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
	sfg::Button::Ptr btnCreateCircleShape;
	sfg::Label::Ptr label;
	sfg::Label::Ptr label2;
	sfg::Box::Ptr box;
	sfg::Entry::Ptr entry_n;
	sfg::Entry::Ptr entry_r;
	sfg::Window::Ptr window;
	sfg::Desktop desktop;

	void button_OnClick() {
		label->SetText("Hello SFGUI, pleased to meet you!");
	}

	void button2_OnClick() {
		++click_count;
		label2->SetText("Click count = " + std::to_string(click_count));
	}

	void btnCreateCircleShape_OnClick() {
		size_t n = stoi(std::string(entry_n->GetText()));
		float r = stof(std::string(entry_r->GetText()));
		sf::CircleShape *c;
		c = new sf::CircleShape(r, n);
		c->setOutlineColor(sf::Color::Green);
		c->setFillColor(sf::Color::Transparent);
		c->setOutlineThickness(3);
		c->setPosition(rand() % 600, rand() % 600);
		shapes_add(c);
	}
};

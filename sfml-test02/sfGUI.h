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

		//label = sfg::Label::Create("Hello world!");
		//label2 = sfg::Label::Create("Click count = " + std::to_string(click_count));
		//lambda - Connect([_label] { _label->SetText("Hello SFGUI, pleased to meet you!"); })

		//button = sfg::Button::Create("Greet SFGUI!");
		//button->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::button_OnClick, this));
		//button2 = sfg::Button::Create("ClickMe!");
		//button2->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::button2_OnClick, this));
		btnClear = sfg::Button::Create("Clear shape list");
		btnClear->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::btnClear_OnClick, this));

		btnCreateCircleShape = sfg::Button::Create("Create shape");
		btnCreateCircleShape->GetSignal(sfg::Widget::OnLeftClick).Connect(std::bind(&sfGUI::btnCreateCircleShape_OnClick, this));
		
		speedbtn_n = sfg::SpinButton::Create(3.f, 99.f, 1.f); // Create the SpinButton itself.
		speedbtn_n->SetRequisition(sf::Vector2f(80.f, 0.f)); // Just like an Entry, you need to specify a minimum width for the SpinButton.
		speedbtn_n->SetDigits(0);// Set the number of digits to display after the decimal point.
		speedbtn_n->GetSignal(sfg::SpinButton::OnValueChanged).Connect(std::bind(&sfGUI::speedbtn_n_OnValueChange, this));

		speedbtn_r = sfg::SpinButton::Create(10.f, 400.f, 10.f); // Create the SpinButton itself.
		speedbtn_r->SetText("100");
		speedbtn_r->SetRequisition(sf::Vector2f(80.f, 0.f)); // Just like an Entry, you need to specify a minimum width for the SpinButton.
		speedbtn_r->SetDigits(0);// Set the number of digits to display after the decimal point.
		speedbtn_r->GetSignal(sfg::SpinButton::OnValueChanged).Connect(std::bind(&sfGUI::speedbtn_r_OnValueChange, this));

		box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.0f);
		//box->Pack(sfg::Label::Create("Hello world!"));
		//box->Pack(button, false);
		
		//auto separator = sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL); // Create a separator.
		//box->Pack(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL), false, true); // Add separator to box and set not to expand.
		//box->Pack(sfg::Label::Create("Click count = " + std::to_string(click_count)));
		//box->Pack(button2, false);
		
		//box->Pack(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL), false, true); // Add separator to box and set not to expand.
		box->Pack(sfg::Label::Create("Create circle shape:"));
		sfg::Box::Ptr box2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.0f);
		box2->Pack(sfg::Label::Create("Sides count:"));
		box2->Pack(speedbtn_n);
		box->Pack(box2);
		box2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 10.0f);
		box2->Pack(sfg::Label::Create("Radius:"));
		box2->Pack(speedbtn_r);
		box->Pack(box2);
		box->Pack(btnCreateCircleShape, false);
		box->Pack(sfg::Separator::Create(sfg::Separator::Orientation::HORIZONTAL), false, true);
		box->Pack(btnClear, false);

		window = sfg::Window::Create();
		window->SetTitle("Hello world!"); 
		window->SetStyle(0b000011011); //|| sfg::Window::TOPLEVEL sfg::Window::SHADOW || sfg::Window::TITLEBAR || sfg::Window::BACKGROUND sfg::Window::Style::CLOSE
		window->Add(box);

		window->GetSignal(sfg::Window::OnCloseButton).Connect([this] { window_OnHideWindowClick(); }); // _ LOOK HERE!!!! binding!!!!
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
	sfg::Button::Ptr btnClear;
	sfg::Box::Ptr box;
	sfg::SpinButton::Ptr speedbtn_n;
	sfg::SpinButton::Ptr speedbtn_r;
	sfg::Window::Ptr window;
	sfg::Desktop desktop;

	void btnClear_OnClick() {
		shapes_free();
	}

	void window_OnHideWindowClick() {
		window->Show(!window->IsLocallyVisible());
	}

	void speedbtn_n_OnValueChange() {
		//const auto& adjustment = speedbtn_n->GetAdjustment();
		//auto range = adjustment->GetUpper() - adjustment->GetLower();
		//auto inverse_fraction = 1.f - (speedbtn_n->GetValue() - adjustment->GetLower()) / range;
	}

	void speedbtn_r_OnValueChange() {
		//const auto& adjustment = speedbtn_n->GetAdjustment();
		//auto range = adjustment->GetUpper() - adjustment->GetLower();
		//auto inverse_fraction = 1.f - (speedbtn_n->GetValue() - adjustment->GetLower()) / range;
	}

	void button2_OnClick() {

	}

	void btnCreateRect_OnClick() {

	}

	void btnCreateCircleShape_OnClick() {
		size_t n = stoi(std::string(speedbtn_n->GetText()));
		float r = stof(std::string(speedbtn_r->GetText()));
		sf::Color color;
		sf::CircleShape *c;
		c = new sf::CircleShape(r, n);

			color.r = rand() % 255;
			color.g = rand() % 255;
			color.b = rand() % 255;
			color.a = rand() % 255;
		c->setFillColor(color);

			color.r = rand() % 128 + 127;
			color.g = rand() % 128 + 127;
			color.b = rand() % 128 + 127;
			color.a = rand() % 128 + 127;
		c->setOutlineColor(color);

		c->setOutlineThickness(rand() % 10 + 1);
		c->setPosition(rand() % 600, rand() % 600);
		c->setRotation(rand() % 360);
		shapes_add(c);
	}
};

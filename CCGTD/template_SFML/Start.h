#pragma once
#include "Menu.h"
#include "DeckBuilding.h"

struct Start : public Menu{
	sf::Text title;
	sf::Text start;
	Start() : Menu(){
		start.setString("Click anywhere to start");
		start.setFont(font); 
		auto size = start.getLocalBounds();
		start.setPosition(500 - size.width / 2, 400);
		start.setColor(sf::Color::Black);

		title.setString("CCGTD");
		title.setFont(font);
		title.setCharacterSize(80);
		size = title.getLocalBounds();
		title.setPosition(500 - size.width / 2, 150);
		title.setColor(sf::Color::Black);

	}
	void draw(sf::RenderWindow& target){
		target.draw(start);
		target.draw(title);
	}

	Menu* update(sf::Event& event){
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
			return new DeckBuilding;
		}
		else return this;
	}
};
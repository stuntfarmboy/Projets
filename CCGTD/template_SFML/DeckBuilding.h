#pragma once
#include "Menu.h"
#include "Play.h"

struct DeckBuilding : public Menu{
	sf::Text title;
	sf::Text newGame;
	DeckBuilding() : Menu(){
		newGame.setString("To be implement... (click to continue)");
		newGame.setFont(font);
		auto size = newGame.getLocalBounds();
		newGame.setPosition(500 - size.width / 2, 400);
		newGame.setColor(sf::Color::Black);

	}
	~DeckBuilding(){
	}
	void draw(sf::RenderWindow& target){
		target.draw(newGame);
		target.draw(title);
	}

	Menu* update(sf::Event& event){
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
			if (newGame.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
				std::list<int> list;
				//parse choice..
				Deck deck(list);
				return new Play(deck);
			}
			else return this;
		}
		else return this;
	}
};
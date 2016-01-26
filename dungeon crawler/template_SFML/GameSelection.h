#pragma once
#include "Menu.h"
#include "CharacterSelection.h"

struct GameSelection : public Menu{
	sf::Text title;
	sf::Text newGame;
	sf::Text loadGame;
	std::ifstream iSave;
	GameSelection() : Menu(){
		newGame.setString("New game");
		newGame.setFont(font);
		auto size = newGame.getLocalBounds();
		newGame.setPosition(500 - size.width / 2, 400);
		newGame.setColor(sf::Color::Black);

		loadGame.setString("Continue");
		loadGame.setFont(font);
		size = loadGame.getLocalBounds();
		loadGame.setPosition(500 - size.width / 2, 460);
		if (iSave.is_open())
			loadGame.setColor(sf::Color::Black);
		else
			loadGame.setColor(sf::Color(0, 0, 0, 125));

		title.setString("Cave Crawler");
		title.setFont(font);
		title.setCharacterSize(80);
		size = title.getLocalBounds();
		title.setPosition(500 - size.width / 2, 50);
		title.setColor(sf::Color::Black);

		iSave.open("save.txt");
	}
	~GameSelection(){
		iSave.close();
	}
	void draw(sf::RenderWindow& target){
		target.draw(newGame);
		target.draw(loadGame);
		target.draw(title);
	}

	Menu* update(sf::Event& event){
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
			if (newGame.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				return new CharacterSelection;
			else if (iSave.is_open() && loadGame.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				return new Play(iSave);
			else return this;
		}
		else return this;
	}
};
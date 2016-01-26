#pragma once
#include "Menu.h"
#include "Play.h"

struct CharacterSelection : public Menu{
	sf::Text start;
	sf::Text classes[4];
	sf::Text desc[4];
	int activeDesc, character;
	sf::RectangleShape sex[2];
	sf::Texture t_sex;
	CharacterSelection() : Menu(){
		start.setString("Start");
		start.setCharacterSize(100);
		start.setFont(font);
		start.setPosition(780, 475);
		start.setColor(sf::Color::Black);

		t_sex.loadFromFile("sex.png");
		sex[0].setTexture(&t_sex);
		sex[0].setTextureRect(sf::IntRect(0, 0, 30, 30));
		sex[0].setPosition(170, 120);
		sex[0].setSize(sf::Vector2f(30, 30));
		sex[0].setOutlineThickness(3);
		sex[0].setOutlineColor(sf::Color::Black);

		sex[1].setTexture(&t_sex);
		sex[1].setTextureRect(sf::IntRect(30, 0, 30, 30));
		sex[1].setPosition(270, 120);
		sex[1].setSize(sf::Vector2f(30, 30));
		sex[1].setOutlineThickness(1);
		sex[1].setOutlineColor(sf::Color::Black);

		std::ifstream file;
		file.open("classes.txt");
		char buffer[256];

		for (int i = 0; i < 4; ++i){
			file.getline(buffer, 256);
			classes[i].setString(buffer);
			classes[i].setFont(font);
			classes[i].setCharacterSize(45);
			classes[i].setPosition(110, 180 + 80 * i);
			classes[i].setColor(sf::Color::Black);
			file.getline(buffer, 256);
			desc[i].setString(buffer);
			desc[i].setFont(font);
			desc[i].setPosition(550, 120);
			desc[i].setColor(sf::Color::Black);
		}

		file.close();

		classes[0].setStyle(sf::Text::Bold);
		activeDesc = 0;
		character = 0;
	}
	~CharacterSelection(){}

	void draw(sf::RenderWindow& target){
		target.draw(start);
		target.draw(sex[0]);
		target.draw(sex[1]);
		for (int i = 0; i < 4; ++i){
			target.draw(classes[i]);
		}
		target.draw(desc[activeDesc]);
	}
	Menu* update(sf::Event& event){
		if (start.getString() == "Loading...") 
			return new Play(character);
		else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
			if (start.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
				start.setString("Loading...");
				start.setPosition(sf::Vector2f(550, 475));
			}
			else if (sex[0].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && character % 10 != 0){
				sex[0].setOutlineThickness(3);
				sex[1].setOutlineThickness(1);
				--character;
			}
			else if (sex[1].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && character % 10 != 1){
				sex[0].setOutlineThickness(1);
				sex[1].setOutlineThickness(3);
				++character;
			}
			else for (int i = 0; i < 4; ++i){
				if (classes[i].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) && character / 10 != i){
					classes[activeDesc].setStyle(sf::Text::Regular);
					classes[i].setStyle(sf::Text::Bold);
					activeDesc = i;
					character = 10 * i + character % 10;
				}
			}
		}
		return this;
	}
};

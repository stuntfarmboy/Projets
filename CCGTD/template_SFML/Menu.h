#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

struct Menu{
	sf::Font font;
	Menu(){
		font.loadFromFile("arial.ttf");
	}
	virtual ~Menu(){}
	virtual void draw(sf::RenderWindow& target) = 0;
	virtual Menu* update(sf::Event& event) = 0;
};
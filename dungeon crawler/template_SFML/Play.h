#pragma once
#include "Menu.h"
#include "Map.h"

struct Play : public Menu{
	std::ofstream oSave;
	sf::RectangleShape invBG;
	sf::RectangleShape inventory[4][2];
	sf::RectangleShape head, body, handL, handR, misc1, misc2;
	sf::Texture equip;
	sf::Text hp, lvl, strengh, dex, intel, info;
	Map map;
	Play(std::ifstream& save) : Menu(){
		setVisual();
		//TODO read iSave
	}
	Play(int& character) : Menu(){
		setVisual();
	}
	~Play(){
		//TODO edit oSave
	}
	void draw(sf::RenderWindow& target){
		//target.setView(target.getDefaultView());
		target.draw(invBG);
		for (int x = 0; x < 4; ++x){
			for (int y = 0; y < 2; ++y){
				target.draw(inventory[x][y]);
			}
		}
		target.draw(head);
		target.draw(body);
		target.draw(handL);
		target.draw(handR);
		target.draw(misc1);
		target.draw(misc2);

		map.draw(target);
	}
	Menu* update(sf::Event& event){
		map.update(event);
		return this;
	}
private:
	void setVisual(){
		invBG.setPosition(sf::Vector2f(600, 0));
		invBG.setFillColor(sf::Color(80,80,80));
		invBG.setSize(sf::Vector2f(400,600));

		for (int x = 0; x < 4; ++x){
			for (int y = 0; y < 2; ++y){
				inventory[x][y].setFillColor(sf::Color(195, 195, 195));
				inventory[x][y].setOutlineThickness(4);
				inventory[x][y].setOutlineColor(sf::Color::Black);
				inventory[x][y].setSize(sf::Vector2f(85, 85));
				inventory[x][y].setPosition(sf::Vector2f(612 + 97 * x, 406 + 97 * y));
			}
		}

		equip.loadFromFile("equip.png");
		head.setTexture(&equip);
		head.setTextureRect(sf::IntRect(0, 0, 85, 85));
		head.setPosition(757.5, 10);
		head.setSize(sf::Vector2f(85, 85));
		head.setOutlineThickness(4);
		head.setOutlineColor(sf::Color::Black);

		body.setTexture(&equip);
		body.setTextureRect(sf::IntRect(85, 0, 85, 85));
		body.setPosition(757.5, 120);
		body.setSize(sf::Vector2f(85, 85));
		body.setOutlineThickness(4);
		body.setOutlineColor(sf::Color::Black);

		handL.setTexture(&equip);
		handL.setTextureRect(sf::IntRect(170, 0, 85, 85));
		handL.setPosition(647.5, 120);
		handL.setSize(sf::Vector2f(85, 85));
		handL.setOutlineThickness(4);
		handL.setOutlineColor(sf::Color::Black);

		handR.setTexture(&equip);
		handR.setTextureRect(sf::IntRect(255, 0, 85, 85));
		handR.setPosition(867.5, 120);
		handR.setSize(sf::Vector2f(85, 85));
		handR.setOutlineThickness(4);
		handR.setOutlineColor(sf::Color::Black);

		misc1.setTexture(&equip);
		misc1.setTextureRect(sf::IntRect(340, 0, 85, 85));
		misc1.setPosition(702.5, 230);
		misc1.setSize(sf::Vector2f(85, 85));
		misc1.setOutlineThickness(4);
		misc1.setOutlineColor(sf::Color::Black);

		misc2.setTexture(&equip);
		misc2.setTextureRect(sf::IntRect(340, 0, 85, 85));
		misc2.setPosition(812.5, 230);
		misc2.setSize(sf::Vector2f(85, 85));
		misc2.setOutlineThickness(4);
		misc2.setOutlineColor(sf::Color::Black);
	}
};
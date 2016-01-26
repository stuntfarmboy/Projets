#pragma once
#include "Menu.h"
#include "Deck.h"

struct Play : public Menu{
	Map map;
	Play(Deck deck) : Menu(){
		setVisual();
	}
	~Play(){
		//TODO edit oSave
	}
	void draw(sf::RenderWindow& target){
		map.draw(target);
	}
	Menu* update(sf::Event& event){
		return this;
	}
private:
	void setVisual(){
		
	}
};
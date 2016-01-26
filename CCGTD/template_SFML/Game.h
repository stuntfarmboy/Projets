#pragma once
#include "Start.h"

struct Game{
	static void play(){
		sf::RenderWindow window(sf::VideoMode(1000, 600), "CCGTD", sf::Style::Close);
		Menu* menu = new Start;
		Menu* newMenu = nullptr;
		while (window.isOpen()){
			sf::Event event;
			while (window.pollEvent(event)){
				if (event.type == sf::Event::Closed){
					window.close();
					break;
				}
				newMenu = menu->update(event);
				if (newMenu != menu){
					delete menu;
					menu = newMenu;
					break;
				}
			}
			window.clear(sf::Color::White);
			menu->draw(window);
			window.display();
		}
		delete menu;
	}
};
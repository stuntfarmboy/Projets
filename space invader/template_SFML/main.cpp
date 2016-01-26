#include <SFML/Graphics.hpp>
#include <list>
#include <stack>
#include <iostream>
#define MAP_WIDTH 11
#define MAP_HEIGHT 20
#define WINDOW_WIDTH 380.f
#define WINDOW_HEIGHT 640.f

sf::Vector2f square(WINDOW_WIDTH / MAP_WIDTH, WINDOW_HEIGHT / MAP_HEIGHT);
bool* map;

#include "Vessel.h"

int main(){
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SpaceInvaders", sf::Style::Close);
	Player player(sf::Vector2f(5 * square.x, 18 * square.y));
	window.setKeyRepeatEnabled(false);

	Flock flock;

	sf::Clock chronoFlock, chronoBullet, chronoFlockBullet;
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::KeyPressed){
				switch (event.key.code){
				case(sf::Keyboard::A) :
					if (player.pos().x > 1 * square.x)
						player.move(sf::Vector2f(-square.x,0));
					break;
				case(sf::Keyboard::D) :
					if (player.pos().x < 10 * square.x)
						player.move(sf::Vector2f(square.x,0));
					break;
				case(sf::Keyboard::Space) :
					player.fire();
					chronoBullet.restart();
					break;
				}
			}
		}
		window.clear(sf::Color::Black);
		if (chronoFlock.getElapsedTime().asMilliseconds() > 500){
			flock.move();
			chronoFlock.restart();
		}
		if (chronoFlockBullet.getElapsedTime().asMilliseconds() > 2000){
			flock.fire();
			chronoFlockBullet.restart();
		}
		if (chronoBullet.getElapsedTime().asMilliseconds() > 40){
			player.update();
			flock.update();
			chronoBullet.restart();
		}
		player.draw(window);
		flock.draw(window);
		window.display();
	}

	return 0;
}
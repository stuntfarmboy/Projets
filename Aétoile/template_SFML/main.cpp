#include <SFML/Graphics.hpp>
#include <list>
#include <stack>
#include <iostream>
#include <random>
#define MAP_WIDTH 52
#define MAP_HEIGHT 28
#define WINDOW_WIDTH 1300.f
#define WINDOW_HEIGHT 750.f

sf::Vector2f square(WINDOW_WIDTH / MAP_WIDTH, WINDOW_HEIGHT * 0.75 / MAP_HEIGHT);
bool* map;

#include "pathfinder.h"

int main(){
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Projet", sf::Style::Close);
	//window.setKeyRepeatEnabled(false);

	sf::RectangleShape bakgroundMenu(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT * 0.25));
	bakgroundMenu.setFillColor(sf::Color::Black);
	bakgroundMenu.setPosition(0, WINDOW_HEIGHT * 0.75);

	std::list<sf::RectangleShape> obstacles;

	//map = new bool[MAP_HEIGHT * MAP_WIDTH];
	//bool walkable;
	//for (short y = 0; y < MAP_HEIGHT; ++y){
	//	for (short x = 0; x < MAP_WIDTH; ++x){
	//		if ((y == 1) && (x != 5)){
	//			walkable = false;
	//			sf::RectangleShape obstacle(square);
	//			obstacle.setPosition(x * square.x, y * square.y);
	//			obstacles.push_back(obstacle);
	//		}
	//		else
	//			walkable = true;
	//		//walkable = (bool)(rand() % 10 % 5);//changer rand
	//		//if (!walkable){
	//		//	sf::RectangleShape obstacle(square);
	//		//	obstacle.setPosition(x * square.x, y * square.y);
	//		//	obstacles.push_back(obstacle);
	//		//}
	//		map[MAP_WIDTH * y + x] = walkable;
	//	}
	//}
	map = new bool[MAP_HEIGHT * MAP_WIDTH]{
		true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true,
		false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false,
		true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false,
		true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false,
		true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false,
		true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true,
		false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false,
		true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true,
		false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false,
		true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false,
		true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false,
		true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false,
		true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true,
		false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false,
		true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true,
		false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false,
		true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false,
		true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false,
		true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false,
		true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true,
		false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false,
		true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true, true, true, true, false, true, true, true, false, true, false, true, true, true,
		false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false, false, false, true, false, true, false, true, true, true, false, false, true, false,
		true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false, true, false, true, true, true, false, false, false, true, true, false, true, false,
		true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false, true, false, false, false, true, false, true, false, false, true, false, true, false,
		true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false, true, false, true, false, true, true, true, false, true, true, false, true, false,
		true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true, true, true, true, true, false, false, false, false, false, true, false, true, true,
		false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false, false, false, false, true, true, true, true, true, true, true, true, true, false
	};
	for (short y = 0; y < MAP_HEIGHT; ++y){
		for (short x = 0; x < MAP_WIDTH; ++x){
			if (!map[MAP_WIDTH * y + x]){
				sf::RectangleShape obstacle(square);
				obstacle.setPosition(x * square.x, y * square.y);
				obstacles.push_back(obstacle);
			}
		}
	}
	int ppx = 0;
	int ppy = 0;
	sf::RectangleShape player(square);
	player.setPosition(square.x * ppx, square.y * ppy);
	player.setFillColor(sf::Color(228, 185, 142));



	int xf, yf;
	//do{
	//	xf = rand() % MAP_WIDTH;//changer rand
	//	yf = rand() % MAP_HEIGHT;//changer rand
	//} while (!map[MAP_WIDTH * yf + xf] || (xf == 1 && yf == 1));
	xf = 24;
	yf = 13;

	sf::RectangleShape obstacle(square);
	obstacle.setPosition(xf * square.x, yf * square.y);
	obstacle.setFillColor(sf::Color::Red);
	obstacles.push_back(obstacle);

	aStar pathfinder(new Node(0, 0, nullptr));

	std::stack<Node*> pathStack = pathfinder.findPath(xf, yf);
	std::cout << xf << "," << yf << std::endl;

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
			if (event.type == sf::Event::KeyPressed){
				switch (event.key.code){
				case(sf::Keyboard::W) :
					if (map[(MAP_WIDTH * (ppy - 1) + ppx)] && ppy != 0){
						player.move(0, -square.y);
						--ppy;
					}
					break;
				case(sf::Keyboard::A) :
					if (map[(MAP_WIDTH * ppy + (ppx - 1))] && ppx != 0){
						player.move(-square.x, 0);
						--ppx;
					}
					break;
				case(sf::Keyboard::S) :
					if (map[(MAP_WIDTH * (ppy + 1) + ppx)] && ppy != MAP_HEIGHT - 1){
						player.move(0, square.y);
						++ppy;
					}
					break;
				case(sf::Keyboard::D) :
					if (map[(MAP_WIDTH * ppy + (ppx + 1))] && ppx != MAP_WIDTH - 1){
						player.move(square.x, 0);
						++ppx;
					}
					break;
				case(sf::Keyboard::Space) :
					if (!pathStack.empty()){
						Node* path = pathStack.top();
						pathStack.pop();
						std::cout << path->x << "," << path->y << std::endl;
						player.setPosition(square.x * path->x, square.y * path->y);
						delete path;
					}
					break;
				}
			}
		}
		window.clear(sf::Color::Green);
		window.draw(bakgroundMenu);
		for (auto it : obstacles){
			window.draw(it);
		}
		window.draw(player);
		window.display();
	}

	return 0;
}
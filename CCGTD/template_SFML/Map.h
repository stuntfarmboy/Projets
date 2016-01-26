#pragma once
#include <SFML/Graphics.hpp>
#include <queue>
#define SPAWN 1
#define END 2
#define MEELE 4
#define RANGE 8
#define BLOCKED 16

struct Map{
	struct Path{
		sf::Vector2f pos;
		int state;
		Path* next;
		Path(){};
		Path(sf::Vector2f pos, int state, Path* next){
			this->pos = pos;
			this->state = state;
			this->next = next;
		}
	};
	Path* path;
	std::queue<sf::RectangleShape> enemies;
	Map(){
		path = new Path[24];
		path[23] = Path(sf::Vector2f(200, 150), END, nullptr);
		path[22] = Path(sf::Vector2f(250, 150), 0, &(path[23]));
		path[21] = Path(sf::Vector2f(300, 150), 0, &(path[22]));
		path[20] = Path(sf::Vector2f(350, 150), RANGE, &(path[21]));
		path[19] = Path(sf::Vector2f(350, 100), RANGE, &(path[20]));
		path[18] = Path(sf::Vector2f(400, 100), RANGE, &(path[19]));
		path[17] = Path(sf::Vector2f(450, 100), MEELE, &(path[18]));
		path[16] = Path(sf::Vector2f(500, 100), MEELE, &(path[17]));
		path[15] = Path(sf::Vector2f(550, 100), MEELE, &(path[16]));
		path[14] = Path(sf::Vector2f(600, 100), RANGE, &(path[15]));
		path[13] = Path(sf::Vector2f(650, 100), RANGE, &(path[14]));
		path[12] = Path(sf::Vector2f(700, 100), 0, &(path[13]));
		path[11] = Path(sf::Vector2f(750, 100), 0, &(path[12]));
		path[10] = Path(sf::Vector2f(800, 100), SPAWN, &(path[11]));
		path[9] = Path(sf::Vector2f(350, 200), RANGE, &(path[20]));
		path[8] = Path(sf::Vector2f(400, 200), RANGE, &(path[9]));
		path[7] = Path(sf::Vector2f(450, 200), MEELE, &(path[8]));
		path[6] = Path(sf::Vector2f(500, 200), MEELE, &(path[7]));
		path[5] = Path(sf::Vector2f(550, 200), MEELE, &(path[6]));
		path[4] = Path(sf::Vector2f(600, 200), RANGE, &(path[5]));
		path[3] = Path(sf::Vector2f(650, 200), RANGE, &(path[4]));
		path[2] = Path(sf::Vector2f(700, 200), 0, &(path[3]));
		path[1] = Path(sf::Vector2f(750, 200), 0, &(path[2]));
		path[0] = Path(sf::Vector2f(800, 200), SPAWN, &(path[1]));
	}
	void draw(sf::RenderWindow& target){
		sf::RectangleShape rect(sf::Vector2f(50, 50));
		for (int i = 0; i < 24; i++){
			rect.setPosition(path[i].pos);
			switch (path[i].state){
			case(END) :
				rect.setFillColor(sf::Color::Blue);
				break;
			case(SPAWN) :
				rect.setFillColor(sf::Color::Cyan);
				break;
			case(MEELE) :
				rect.setFillColor(sf::Color::Red);
				break;
			case(RANGE) :
				rect.setFillColor(sf::Color::Green);
				break;
			case(BLOCKED) :
				rect.setFillColor(sf::Color::Black);
				break;
			default :
				rect.setFillColor(sf::Color::Yellow);
			}
			target.draw(rect);
		}
	}
};
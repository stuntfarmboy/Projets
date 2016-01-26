#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#define UP 1000
#define DOWN 100
#define LEFT 10
#define RIGHT 1

struct Map{
	sf::View camera;
	sf::RectangleShape map[60][60];
	int areas[12][12];
	Map(){
		srand(time(NULL));

		camera.reset(sf::FloatRect(0, 0, 60, 60));
		camera.setViewport(sf::FloatRect(0, 0, 0.6, 1));

		int paths;
		for (int y = 0; y < 12; ++y){
			for (int x = 0; x < 12; ++x){
				areas[x][y] = 0;
			}
		}
		//TODO revérifier l'algo de gen et de colorigae
		for (int y = 0; y < 12; ++y){
			for (int x = 0; x < 12; ++x){
				if (x == 11){
					if (y == 11){
						paths = 0;
					}
					else{
						do{
							paths = (rand() % 3) * DOWN;
						} while (paths + areas[x][y] == 0);
					}
				}
				else{
					if (y == 11){
						do{
							paths = (rand() % 3) * RIGHT;
						} while (paths + areas[x][y] == 0);
					}
					else{
						do{
							paths = (rand() % 3) * DOWN + (rand() % 3) * RIGHT;
						} while (paths + areas[x][y] == 0);
					}
				}

				areas[x][y] += paths;

				if (x < 11){
					areas[x + 1][y] += (paths % 10) * 10;

				}
				if (y < 11){
					areas[x][y + 1] += (paths % 1000) - (paths % 100) * 10;
				}
			}
		}
		for (int y = 0; y < 12; ++y){
			for (int x = 0; x < 12; ++x){
				for (int _y = 0; _y < 5; ++_y){
					for (int _x = 0; _x < 5; ++_x){
						if (_x == 0 || _y == 0 || _x == 4 || _y == 4){
							if ((_x == 4 && areas[x][y] % 10 == 0) || (_y == 4 && (areas[x][y] % 1000) - (areas[x][y] % 100) == 0) || (_x == 0 && (areas[x][y] % 100) - (areas[x][y] % 10) == 0) || (_y == 0 && (areas[x][y] % 10000) - (areas[x][y] % 1000) == 0)){
								map[_x + 5 * x][_y + 5 * y].setSize(sf::Vector2f(10, 10));
								map[_x + 5 * x][_y + 5 * y].setFillColor(sf::Color(125, 125, 125, 255));
								map[_x + 5 * x][_y + 5 * y].setPosition(sf::Vector2f(50 * x + 10 * _x, 50 * y + 10 * _y));
							}
							else{
								map[_x + 5 * x][_y + 5 * y].setSize(sf::Vector2f(10, 10));
								map[_x + 5 * x][_y + 5 * y].setFillColor(sf::Color(125, 125, 125, 125));
								map[_x + 5 * x][_y + 5 * y].setPosition(sf::Vector2f(50 * x + 10 * _x, 50 * y + 10 * _y));
							}
						}
						else{
							map[_x + 5 * x][_y + 5 * y].setSize(sf::Vector2f(10, 10));
							map[_x + 5 * x][_y + 5 * y].setFillColor(sf::Color(125, 125, 125, 125));
							map[_x + 5 * x][_y + 5 * y].setPosition(sf::Vector2f(50 * x + 10 * _x, 50 * y + 10 * _y));
						}
					}
				}
			}
		}
	}
	void draw(sf::RenderWindow& target){
		//target.setView(camera);
		for (short x = 0; x < 60; ++x){
			for (short y = 0; y < 60; ++y){
				target.draw(map[x][y]);
			}
		}
	}
	void update(sf::Event& event){

	}
};
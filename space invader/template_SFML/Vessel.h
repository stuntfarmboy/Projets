#pragma once
#define INVADERS 12
#define INVADERS_W 4
#define INVADERS_H 3
struct Vessel{
	sf::RectangleShape* bullet;
	sf::RectangleShape vessel;
	Vessel(){}
	Vessel(sf::Vector2f& pos, sf::Color color){
		vessel = sf::RectangleShape(square);
		vessel.setPosition(pos);
		bullet = nullptr;
	}
	~Vessel(){
		if (bullet)
			delete bullet;
	}
	void move(sf::Vector2f& step){
		vessel.move(step);
	}
	void draw(sf::RenderWindow& window){
		window.draw(vessel);
		if (bullet)
			window.draw(*bullet);
	}
	sf::Vector2f pos(){
		return vessel.getPosition();
	}
};
struct Player : public Vessel{
	Player(sf::Vector2f& pos) : Vessel(pos, sf::Color::Green){}
	void fire(){
		if (!bullet){
			bullet = new sf::RectangleShape(vessel);
			bullet->setFillColor(sf::Color::Green);
		}
	}
	void update(){
		if (bullet){
			if (bullet->getPosition().y < square.y){
				delete bullet;
				bullet = nullptr;
				return;
			}
			bullet->move(0, -square.y);
		}
	}
};
struct Invader : public Vessel{
	Invader(sf::Vector2f& pos) : Vessel(pos, sf::Color::White){}
	void fire(){
		if (!bullet){
			bullet = new sf::RectangleShape(vessel);
			bullet->setFillColor(sf::Color::White);
		}
	}
	void update(){
		if (bullet){
			if (bullet->getPosition().y > (MAP_HEIGHT - 1) * square.y){
				delete bullet;
				bullet = nullptr;
				return;
			}
			bullet->move(0, square.y);
		}
	}
};
struct Flock{
	std::list<std::list<Invader*>> invaders;
	short animation;
	sf::Vector2f* animations = new sf::Vector2f[10]{
		sf::Vector2f(-square.x, 0),
			sf::Vector2f(-square.x, 0),
			sf::Vector2f(-square.x, 0),
			sf::Vector2f(-square.x, 0),
			sf::Vector2f(0, square.y),
			sf::Vector2f(square.x, 0),
			sf::Vector2f(square.x, 0),
			sf::Vector2f(square.x, 0),
			sf::Vector2f(square.x, 0),
			sf::Vector2f(0, square.y)
	};
	Flock(){
		for (short w(0); w < INVADERS_W; ++w){
			std::list<Invader*>* column = new std::list < Invader* > ;
			for (short h(INVADERS_H); h > 0; --h){
				column->push_front(new Invader(sf::Vector2f((2 * w + 2) * square.x, (2 * h - 1) * square.y)));
			}
			invaders.push_back(*column);
		}
		animation = 2;
	}
	~Flock(){
		delete[] animations;
		invaders.clear();
	}
	void move(){
		for (auto list : invaders){
			for (auto vessel : list){
				vessel->move(animations[animation]);
			}
		}
		++animation %= 10;
	}
	void update(){
		for (auto list : invaders){
			for (auto vessel : list){
				vessel->update();
			}
		}
	}
	void draw(sf::RenderWindow& window){
		for (auto list : invaders){
			for (auto vessel : list){
				vessel->draw(window);
			}
		}
	}
	void fire(){
		auto list = invaders.begin();
		std::advance(list, rand() % invaders.size());
		(*list).back()->fire();
	}
};
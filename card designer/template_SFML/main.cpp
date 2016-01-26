#include <SFML/Graphics.hpp>
#include <iostream>

sf::Font font;

struct TextBox{
	sf::RectangleShape bg;
	sf::Text text;
	TextBox(int x, int y, sf::String name){
		text.setString(name);
		text.setPosition(x, y);
		text.setFont(font);
		bg.setPosition(x, y);
		bg.setSize(sf::Vector2f(text.getGlobalBounds().width, text.getGlobalBounds().height));
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(600, 370), "SFML works!");

	font.loadFromFile("arial.ttf");
	
	TextBox name(300, 20, sf::String("Card name"));
	TextBox desc(300, 80, sf::String("Card effect"));
	TextBox range(300, 140, sf::String("Card range"));

	sf::Image canvas;
	canvas.loadFromFile("E:\\Prog\\Cards\\TEMPLATES\\templateRanger.png");

	sf::Texture cardText;
	sf::RectangleShape cardRend(sf::Vector2f(270,370));

	std::string str;

	sf::Text _name(name.text.getString(), font, 20); _name.setPosition(sf::Vector2f(15, 4)); _name.setColor(sf::Color::Black);
	sf::Text _desc(desc.text.getString(), font, 20); _desc.setPosition(sf::Vector2f(25, 235)); _desc.setColor(sf::Color::Black);
	sf::Text _range(sf::String("Range:") + range.text.getString(), font, 20); _range.setPosition(sf::Vector2f(25, 320)); _range.setColor(sf::Color::Black);

	bool ctrl = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{

			if (name.bg.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 8 && str.size() != 0){
					str.pop_back();
				}
				else if (event.text.unicode < 128)
				{
					str += static_cast<char>(event.text.unicode);
				}
				name.text.setString(str);
				_name.setString(str);
			}
			else if (desc.bg.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 8 && str.size() != 0){
					str.pop_back();
				}
				else if (event.text.unicode < 128)
				{
					str += static_cast<char>(event.text.unicode);
				}
				desc.text.setString(str);
				_desc.setString(str);
			}
			else if (range.bg.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) && event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 8 && str.size() != 0){
					str.pop_back();
				}
				else if (event.text.unicode < 128)
				{
					str += static_cast<char>(event.text.unicode);
				}
				range.text.setString(str);
				_range.setString(sf::String("Range:") + str);
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::LControl)
				ctrl = true;
			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::LControl)
				ctrl = false;

			if (ctrl && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C)
				str.clear();

			if (ctrl && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S){
				sf::Image win = window.capture();
				sf::Image card;
				card.create(270, 370);			
				card.copy(win, 0, 0, sf::IntRect(0, 0, 270, 370));
				card.saveToFile(sf::String("E:\\Prog\\Cards\\Ranger\\") + name.text.getString() + sf::String(".png"));
			}

			if (event.type == sf::Event::Closed)
				window.close();
		}
		cardText.loadFromImage(canvas);
		cardRend.setTexture(&cardText);

		window.clear();
		window.draw(cardRend);
		window.draw(name.text);
		window.draw(desc.text);
		window.draw(range.text);
		window.draw(_name);
		window.draw(_desc);
		window.draw(_range);
		window.display();
	}

	return 0;
}
#pragma once
#include <SFML/Graphics.hpp>
class Buttons {
private:
	sf::Sprite button;

	struct Position {
		float PosX;
		float PosY;
	};

public:
	void Button(sf::Texture* texture, float pos_x, float pos_y);

	void ChangeButton(sf::Texture* texture);

	void SetOriginCenter();

	Position GetPosition();

	void draw(sf::RenderWindow& window);

	bool isMouseOver(sf::RenderWindow& window);
};


#include "Buttons.h"

void Buttons::Button(sf::Texture* texture, float pos_x, float pos_y) {
	button.setTexture(*texture);
	button.setPosition(pos_x, pos_y);
}

void Buttons::ChangeButton(sf::Texture* texture) {
	button.setTexture(*texture);
}

void Buttons::SetOriginCenter() {
	button.setPosition(button.getPosition().x - button.getGlobalBounds().width / 2, button.getPosition().y - button.getGlobalBounds().height / 2);
}

Buttons::Position Buttons::GetPosition() {
	Position pos = { button.getPosition().x + button.getLocalBounds().width, button.getPosition().y };
	return pos;
}

void Buttons::draw(sf::RenderTarget& window) {
	window.draw(button);
}

bool Buttons::isMouseOver(sf::RenderWindow& window) {
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;

	float btnPosX = button.getPosition().x;
	float btnPosY = button.getPosition().y;

	float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
	float btnxPosHeight = button.getPosition().y + button.getLocalBounds().height;

	if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnxPosHeight && mouseY > btnPosY) {
		return true;
	}
	return false;
}

#pragma once
#include <SFML/Graphics.hpp>
#include "Plot.h"
#include "Buttons.h"
#include "Investments.h"

class TradingMarket {
private:
	std::map<std::string, sf::Texture*> textures;

	Plot plot;

	sf::Clock clock;

	sf::RectangleShape verticalLine1;
	sf::RectangleShape verticalLine2;
	sf::RectangleShape verticalLine3;
	sf::RectangleShape horizontalLine1;

	//Select objects
	sf::RectangleShape selectVrtLine1;
	sf::RectangleShape selectVrtLine2;
	sf::RectangleShape selectPanel;


	//buttons
	int stockSelected = 0;
	Buttons stocksButton;
	Buttons cryptoButton;
	Buttons buyButton;

	sf::Text nameText;
	sf::Text volText;
	sf::Text priceText;
	sf::Color lineColor = sf::Color(135, 135, 135);

	sf::Text invNameText;
	sf::Text originText;
	sf::Text productText;

	//portfolio window
	sf::RectangleShape portfolioPanel;
	sf::Text portfolioText;

	//order panel objects
	sf::RectangleShape orderPanel;
	sf::Text orderText;
	Buttons shortButton;
	Buttons upButton;
	Buttons downButton;
	Buttons sellButton;

	sf::RectangleShape orderPanel1;
	sf::RectangleShape orderPanel2;

	//investments
	Investments crypto[6];
	Investments stocks[1];
	std::vector<sf::RectangleShape> investPanelArray;
	std::vector<sf::Text> TextArray;
	
	enum InvType{
		STOCK,
		CRYPTO,
	};
	InvType selectedTab = STOCK;
	InvType showingTab = STOCK;
public:
	sf::Font font;

	void initTradingMarket(const sf::Font& font);

	void renderTradeMarket(sf::RenderTarget& window);

	void updatePage();

	void mouseCheck(sf::RenderWindow& window);
};


#pragma once
#include <SFML/Graphics.hpp>
#include "Plot.h"
#include "Buttons.h"
#include "Investments.h"

class TradingMarket {
private:
	sf::Font font;

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
	int buyPriceSelected = 11;
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
	sf::RectangleShape portfolioPanel2;
	sf::RectangleShape portfolioline1;
	sf::RectangleShape portfolioline2;
	sf::RectangleShape portfolioline3;
	sf::RectangleShape portfolioline4;

	//order panel objects
	sf::RectangleShape orderPanel;
	sf::Text orderText;
	sf::Text unitsText;
	sf::Text unitsValueText;
	sf::Text costText;
	sf::Text costValueText;

	Buttons shortButton;
	Buttons upButton;
	Buttons downButton;
	Buttons sellButton;

	sf::RectangleShape orderPanel1;
	sf::RectangleShape orderPanel2;

	//investments
	Investments crypto[6];
	Investments stocks[4];
	std::vector<sf::RectangleShape> investPanelArray;
	std::vector<sf::Text> TextArray;
	int buyPrices[22] = {5, 10, 25, 50, 75, 100, 250, 500, 750, 1000, 2500, 5000, 7500, 10000, 25000, 50000, 75000, 100000, 250000, 500000, 750000, 1000000 };
	
	enum InvType{
		STOCK,
		CRYPTO,
	};
	InvType selectedTab = STOCK;
	InvType showingTab = STOCK;

	void updatePage();
public:
	void initTradingMarket(const sf::Font& font);

	void renderTradeMarket(sf::RenderTarget& window);

	void mouseCheck(sf::RenderWindow& window);
};


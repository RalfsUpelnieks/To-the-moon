#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <random>
#include <vector>
#include <numeric>
#include <ctime>

#include "PieChart.h"
#include "Buttons.h"
#include "TradingMarket.h"

class Game {
private:
	sf::RenderWindow *window;

	std::map<std::string, sf::Texture*> textures;

	void initWindow();
	void initTextures();

	void initGUI();
	
	void renderMenu();
	void renderHome();

	//GUI
	Buttons startButton;
	sf::Sprite startBackground;

	Buttons homeButton;
	Buttons tradeButton;
	Buttons newsButton;
	Buttons lifestyleButton;
	Buttons shopButton;
	Buttons financesButton;
	Buttons settingsButton;

	sf::Text pointText;

	
	sf::RectangleShape bar;
	sf::Text timeText;
	sf::Text dateText;

	sf::Text bankAccountText;
	sf::Text moneyText;

	PieChart pChart;
	TradingMarket tradingPage;

	sf::Text totalValueText;
	sf::Text totalValueMoneyText;

	sf::Text newsText;
	sf::Text newsText2;
	sf::Text shopText;
	sf::Text lifestyleText;
	sf::Text settingsText;

	enum Scene
	{
		MENU,
		MENU_SETTINGS,
		HOME,
		TRADE_MARKET,
		NEWS,
		LIFESTYLE,
		SHOP,
		FINANCES,
		SETTINGS
	};
	Scene scene = HOME;
public:
	sf::Font font;
	Game();

	const bool running() const;

	void Events();
	void updateGUI();
	void update();

	void renderGUI();
	void render();
};
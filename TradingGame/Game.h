#pragma once

#include <SFML/Graphics.hpp>
#include "Buttons.h"
#include "PieChart.h"
#include "Plot.h"
#include <ctime>


class Game {
private:
	sf::RenderWindow *window;

	std::map<std::string, sf::Texture*> textures;

	void initWindow();
	void initTextures();

	void initGUI();
	
	void renderMenu();
	void renderHome();
	void renderTradeMarket();

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

	
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	PieChart pChart;
	Plot testPlot;

	sf::Text portfolioText;
	sf::Text totalValueText;
	sf::Text totalValueMoneyText;
	std::vector<float> plotValues;
	std::vector<int> plotVolValues;

	sf::Clock clock;

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

	float getDistribution(float old_price);

};
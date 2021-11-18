#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include <random>
#include <vector>
#include <numeric>

#include "Game.h"
#include "PieChart.h"
#include "Buttons.h"
#include "Plot.h"

void Game::initWindow() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "To the moon", sf::Style::Close | sf::Style::Titlebar, settings);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);

	srand(static_cast <unsigned> (time(0)));
	scene = MENU;
}

void Game::initTextures() {
	textures["Home_button"] = new sf::Texture();
	textures["Home_button"]->loadFromFile("Textures/Home_button.png");
	textures["Home_button_hover"] = new sf::Texture();
	textures["Home_button_hover"]->loadFromFile("Textures/Home_button_hover.png");
	textures["Home_button_selected"] = new sf::Texture();
	textures["Home_button_selected"]->loadFromFile("Textures/Home_button_selected.png");

	textures["Trade_button"] = new sf::Texture();
	textures["Trade_button"]->loadFromFile("Textures/Trade_button.png");
	textures["Trade_button_hover"] = new sf::Texture();
	textures["Trade_button_hover"]->loadFromFile("Textures/Trade_button_hover.png");
	textures["Trade_button_selected"] = new sf::Texture();
	textures["Trade_button_selected"]->loadFromFile("Textures/Trade_button_selected.png");

	textures["News_button"] = new sf::Texture();
	textures["News_button"]->loadFromFile("Textures/News_button.png");
	textures["News_button_hover"] = new sf::Texture();
	textures["News_button_hover"]->loadFromFile("Textures/News_button_hover.png");
	textures["News_button_selected"] = new sf::Texture();
	textures["News_button_selected"]->loadFromFile("Textures/News_button_selected.png");

	textures["Lifestyle_button"] = new sf::Texture();
	textures["Lifestyle_button"]->loadFromFile("Textures/Lifestyle_button.png");
	textures["Lifestyle_button_hover"] = new sf::Texture();
	textures["Lifestyle_button_hover"]->loadFromFile("Textures/Lifestyle_button_hover.png");
	textures["Lifestyle_button_selected"] = new sf::Texture();
	textures["Lifestyle_button_selected"]->loadFromFile("Textures/Lifestyle_button_selected.png");

	textures["Shop_button"] = new sf::Texture();
	textures["Shop_button"]->loadFromFile("Textures/Shop_button.png");
	textures["Shop_button_hover"] = new sf::Texture();
	textures["Shop_button_hover"]->loadFromFile("Textures/Shop_button_hover.png");
	textures["Shop_button_selected"] = new sf::Texture();
	textures["Shop_button_selected"]->loadFromFile("Textures/Shop_button_selected.png");

	textures["Finances_button"] = new sf::Texture();
	textures["Finances_button"]->loadFromFile("Textures/Finances_button.png");
	textures["Finances_button_hover"] = new sf::Texture();
	textures["Finances_button_hover"]->loadFromFile("Textures/Finances_button_hover.png");
	textures["Finances_button_selected"] = new sf::Texture();
	textures["Finances_button_selected"]->loadFromFile("Textures/Finances_button_selected.png");

	textures["Settings_button"] = new sf::Texture();
	textures["Settings_button"]->loadFromFile("Textures/Settings_button.png");
	textures["Settings_button_hover"] = new sf::Texture();
	textures["Settings_button_hover"]->loadFromFile("Textures/Settings_button_hover.png");
	textures["Settings_button_selected"] = new sf::Texture();
	textures["Settings_button_selected"]->loadFromFile("Textures/Settings_button_selected.png");

	textures["MenuBackground"] = new sf::Texture();
	textures["MenuBackground"]->loadFromFile("Textures/StartScreen.png");
	textures["StartButton"] = new sf::Texture();
	textures["StartButton"]->loadFromFile("Textures/StartNewGameButton.png");
}

void Game::initGUI() {
	startButton.Button(textures["StartButton"], 640.f, 480.f);
	startButton.SetOriginCenter();
	homeButton.Button(textures["Home_button"], 0.f, 0.f);
	tradeButton.Button(textures["Trade_button"], homeButton.GetPosition().PosX, homeButton.GetPosition().PosY);
	newsButton.Button(textures["News_button"], tradeButton.GetPosition().PosX, tradeButton.GetPosition().PosY);
	lifestyleButton.Button(textures["Lifestyle_button"], newsButton.GetPosition().PosX, newsButton.GetPosition().PosY);
	shopButton.Button(textures["Shop_button"], lifestyleButton.GetPosition().PosX, lifestyleButton.GetPosition().PosY);
	financesButton.Button(textures["Finances_button"], shopButton.GetPosition().PosX, shopButton.GetPosition().PosY);
	settingsButton.Button(textures["Settings_button"], financesButton.GetPosition().PosX, financesButton.GetPosition().PosY);

	startBackground.setTexture(*textures["MenuBackground"]);
	startBackground.setPosition(0.f, 0.f);

	//Load font
	if (!font.loadFromFile("Fonts/Dosis-Light.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	pointText.setPosition(700.f, 25.f);
	pointText.setFont(font);
	pointText.setCharacterSize(20);
	pointText.setFillColor(sf::Color::White);
	pointText.setString("test");

	portfolioText.setFont(font);
	portfolioText.setCharacterSize(40);
	portfolioText.setFillColor(sf::Color::Black);
	portfolioText.setString("Portfolio");
	portfolioText.setPosition(10, 40);

	totalValueText.setFont(font);
	totalValueText.setCharacterSize(20);
	totalValueText.setFillColor(sf::Color::Black);
	totalValueText.setString("Portfolio total value");
	totalValueText.setPosition(81, 170);
	totalValueMoneyText.setFont(font);
	totalValueMoneyText.setCharacterSize(23);
	totalValueMoneyText.setFillColor(sf::Color::Black);
	totalValueMoneyText.setString("$1.68");
	totalValueMoneyText.setOrigin(totalValueMoneyText.getGlobalBounds().width / 2.f, totalValueMoneyText.getGlobalBounds().height / 2.f);
	totalValueMoneyText.setPosition(150, 202);

	//PieChart
	pChart.initPieChart(font);

	//Plot
	testPlot.initPlot(sf::Vector2f(900, 360), sf::Vector2f(340, 340), 40, font, sf::Color(0, 106, 255));

	for (int i = 0; i < 63; i++) {
		if (i == 0) {
			plotValues.push_back(Game::getDistribution(50));
		}
		else {
			plotValues.push_back(Game::getDistribution(plotValues.back()));
		}

		plotVolValues.push_back(20000 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (40000 - 20000))));
	}
}

Game::Game() { 
	initWindow();
	initTextures();
	initGUI();
}

//Functions
const bool Game::running() const {
	return window->isOpen();
}

void Game::Events() {
	sf::Event Event;
	while (window->pollEvent(Event)) {
		switch (Event.type) {

		case sf::Event::Closed:
			window->close();
		case sf::Event::KeyPressed:
			if (Event.Event::key.code == sf::Keyboard::Escape) {
				window->close();
			}
			break;
		case sf::Event::MouseMoved:

			if (scene == HOME) {
				homeButton.ChangeButton(textures["Home_button_selected"]);
			}
			else if (homeButton.isMouseOver(*window)) {
				homeButton.ChangeButton(textures["Home_button_hover"]);
			}
			else {
				homeButton.ChangeButton(textures["Home_button"]);
			}

			if (scene == TRADE_MARKET) {
				tradeButton.ChangeButton(textures["Trade_button_selected"]);
			}
			else if (tradeButton.isMouseOver(*window)) {
				tradeButton.ChangeButton(textures["Trade_button_hover"]);
			}
			else {
				tradeButton.ChangeButton(textures["Trade_button"]);
			}

			if (scene == NEWS) {
				newsButton.ChangeButton(textures["News_button_selected"]);
			}
			else if (newsButton.isMouseOver(*window)) {
				newsButton.ChangeButton(textures["News_button_hover"]);
			}
			else {
				newsButton.ChangeButton(textures["News_button"]);
			}


			if (scene == LIFESTYLE) {
				lifestyleButton.ChangeButton(textures["Lifestyle_button_selected"]);
			}
			else if (lifestyleButton.isMouseOver(*window)) {
				lifestyleButton.ChangeButton(textures["Lifestyle_button_hover"]);
			}
			else {
				lifestyleButton.ChangeButton(textures["Lifestyle_button"]);
			}


			if (scene == SHOP) {
				shopButton.ChangeButton(textures["Shop_button_selected"]);
			}
			else if (shopButton.isMouseOver(*window)) {
				shopButton.ChangeButton(textures["Shop_button_hover"]);
			}
			else {
				shopButton.ChangeButton(textures["Shop_button"]);
			}


			if (scene == FINANCES) {
				financesButton.ChangeButton(textures["Finances_button_selected"]);
			}
			else if (financesButton.isMouseOver(*window)) {
				financesButton.ChangeButton(textures["Finances_button_hover"]);
			}
			else {
				financesButton.ChangeButton(textures["Finances_button"]);
			}


			if (scene == SETTINGS) {
				settingsButton.ChangeButton(textures["Settings_button_selected"]);
			}
			else if (settingsButton.isMouseOver(*window)) {
				settingsButton.ChangeButton(textures["Settings_button_hover"]);
			}
			else {
				settingsButton.ChangeButton(textures["Settings_button"]);
			}



			break;
		case sf::Event::MouseButtonPressed:
			if (scene == MENU && startButton.isMouseOver(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				scene = HOME;
			}

			if (homeButton.isMouseOver(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && scene != MENU) {
				homeButton.ChangeButton(textures["Home_button_selected"]);
				tradeButton.ChangeButton(textures["Trade_button"]);
				newsButton.ChangeButton(textures["News_button"]);
				lifestyleButton.ChangeButton(textures["Lifestyle_button"]);
				shopButton.ChangeButton(textures["Shop_button"]);
				financesButton.ChangeButton(textures["Finances_button"]);
				settingsButton.ChangeButton(textures["Settings_button"]);
				scene = HOME;
			}
			if (tradeButton.isMouseOver(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && scene != MENU) {
				tradeButton.ChangeButton(textures["Trade_button_selected"]);
				homeButton.ChangeButton(textures["Home_button"]);
				newsButton.ChangeButton(textures["News_button"]);
				lifestyleButton.ChangeButton(textures["Lifestyle_button"]);
				shopButton.ChangeButton(textures["Shop_button"]);
				financesButton.ChangeButton(textures["Finances_button"]);
				settingsButton.ChangeButton(textures["Settings_button"]);
				scene = TRADE_MARKET;
			}
			if (newsButton.isMouseOver(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && scene != MENU) {
				newsButton.ChangeButton(textures["News_button_selected"]);
				homeButton.ChangeButton(textures["Home_button"]);
				tradeButton.ChangeButton(textures["Trade_button"]);
				lifestyleButton.ChangeButton(textures["Lifestyle_button"]);
				shopButton.ChangeButton(textures["Shop_button"]);
				financesButton.ChangeButton(textures["Finances_button"]);
				settingsButton.ChangeButton(textures["Settings_button"]);
				scene = NEWS;
			}
			if (lifestyleButton.isMouseOver(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && scene != MENU) {
				lifestyleButton.ChangeButton(textures["Lifestyle_button_selected"]);
				homeButton.ChangeButton(textures["Home_button"]);
				tradeButton.ChangeButton(textures["Trade_button"]);
				newsButton.ChangeButton(textures["News_button"]);
				shopButton.ChangeButton(textures["Shop_button"]);
				financesButton.ChangeButton(textures["Finances_button"]);
				settingsButton.ChangeButton(textures["Settings_button"]);
				scene = LIFESTYLE;
			}
			if (shopButton.isMouseOver(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && scene != MENU) {
				shopButton.ChangeButton(textures["Shop_button_selected"]);
				homeButton.ChangeButton(textures["Home_button"]);
				tradeButton.ChangeButton(textures["Trade_button"]);
				newsButton.ChangeButton(textures["News_button"]);
				lifestyleButton.ChangeButton(textures["Lifestyle_button"]);
				financesButton.ChangeButton(textures["Finances_button"]);
				settingsButton.ChangeButton(textures["Settings_button"]);
				scene = SHOP;
			}
			if (financesButton.isMouseOver(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && scene != MENU) {
				financesButton.ChangeButton(textures["Finances_button_selected"]);
				homeButton.ChangeButton(textures["Home_button"]);
				tradeButton.ChangeButton(textures["Trade_button"]);
				newsButton.ChangeButton(textures["News_button"]);
				lifestyleButton.ChangeButton(textures["Lifestyle_button"]);
				shopButton.ChangeButton(textures["Shop_button"]);
				settingsButton.ChangeButton(textures["Settings_button"]);
				scene = FINANCES;
			}
			if (settingsButton.isMouseOver(*window) && sf::Mouse::isButtonPressed(sf::Mouse::Left) && scene != MENU) {
				settingsButton.ChangeButton(textures["Settings_button_selected"]);
				homeButton.ChangeButton(textures["Home_button"]);
				tradeButton.ChangeButton(textures["Trade_button"]);
				newsButton.ChangeButton(textures["News_button"]);
				lifestyleButton.ChangeButton(textures["Lifestyle_button"]);
				shopButton.ChangeButton(textures["Shop_button"]);
				financesButton.ChangeButton(textures["Finances_button"]);
				scene = SETTINGS;
			}
			break;
		}
	}
}

void Game::update() {
	updateGUI();
}

void Game::updateGUI() {
}

void Game::render() {
	window->clear(sf::Color::White);
	if (scene != MENU) {
		renderGUI();
	}

	if (scene == MENU) {
		Game::renderMenu();
	}
	else if (scene == MENU_SETTINGS) {
		
	}
	else if (scene == HOME) {
		Game::renderHome();
	}
	else if (scene == TRADE_MARKET) {
		Game::renderTradeMarket();
	}
	else if (scene == NEWS) {

	}
	else if (scene == LIFESTYLE) {

	}
	else if (scene == SHOP) {

	}
	else if (scene == FINANCES) {

	}
	else if (scene == SETTINGS) {

	}
	

	window->display();
}

void Game::renderGUI() {
	window->draw(portfolioText);

	homeButton.draw(*window);
	tradeButton.draw(*window);
	newsButton.draw(*window);
	lifestyleButton.draw(*window);
	shopButton.draw(*window);
	financesButton.draw(*window);
	settingsButton.draw(*window);
}

void Game::renderMenu() {
	window->draw(startBackground);
	startButton.draw(*window);
}

void Game::renderHome() {
	std::vector<float> values = { 100.f, 230.f, 150.f, 100.f, 0.f };
	pChart.PieChartData(values);

	pChart.ClearVertices();

	pChart.GenerateVertices();
	pChart.draw(*window, sf::RenderStates::Default);
	window->draw(totalValueText);
	window->draw(totalValueMoneyText);
}

void Game::renderTradeMarket() {
	if (clock.getElapsedTime().asMilliseconds() > 1000) {
		clock.restart();
		plotValues.erase(plotValues.begin());
		plotValues.push_back(Game::getDistribution(plotValues.back()));

		plotVolValues.erase(plotVolValues.begin());
		plotVolValues.push_back(20000 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (40000 - 20000))));
	}

	testPlot.setValue(plotValues, plotVolValues);

	testPlot.GenerateVertices();

	window->draw(testPlot);
}

float Game::getDistribution(float old_price) {
	float volatility = 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (10 - 2)));
	//float volatility = 2;

	float rnd = 0.01f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - 0.01f)));

	float change_percent = 2 * volatility * rnd;
	if (change_percent > volatility)
		change_percent -= (2 * volatility);
	
	float change_amount = old_price * change_percent / 100;
	float new_price = old_price + change_amount;

	if (new_price < 100) {
		new_price += std::abs(change_amount) * 2;
	}
	
	return new_price;
}
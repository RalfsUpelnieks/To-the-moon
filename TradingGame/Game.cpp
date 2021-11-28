#include "Game.h"

void Game::initWindow() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	window = new sf::RenderWindow(sf::VideoMode(1280, 720), "To the moon", sf::Style::Close | sf::Style::Titlebar, settings);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);

	srand(static_cast <unsigned> (time(0)));
	scene = TRADE_MARKET;
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
	if (!font.loadFromFile("Fonts/arialbd.ttf"))
		std::cout << "ERROR::GAME::Failed to load font" << "\n";

	//Init point text
	pointText.setPosition(700.f, 25.f);
	pointText.setFont(font);
	pointText.setCharacterSize(20);
	pointText.setFillColor(sf::Color::White);
	pointText.setString("test");

	totalValueText.setFont(font);
	totalValueText.setCharacterSize(18);
	totalValueText.setFillColor(sf::Color(66, 69, 71));
	totalValueText.setString("Portfolio total value");
	totalValueText.setPosition(64, 175);
	totalValueMoneyText.setFont(font);
	totalValueMoneyText.setCharacterSize(17);
	totalValueMoneyText.setFillColor(sf::Color(66, 69, 71));
	totalValueMoneyText.setString("$1.68");
	totalValueMoneyText.setOrigin(totalValueMoneyText.getGlobalBounds().width / 2.f, totalValueMoneyText.getGlobalBounds().height / 2.f);
	totalValueMoneyText.setPosition(150, 202);

	//bar
	bar.setSize(sf::Vector2f(1280, 50));
	bar.setFillColor(sf::Color(240, 240, 240));
	bar.setPosition(sf::Vector2f(0, 34));
	bar.setOutlineColor(sf::Color(135, 135, 135));
	bar.setOutlineThickness(1);

	timeText.setFont(font);
	timeText.setCharacterSize(20);
	timeText.setFillColor(sf::Color::Black);
	timeText.setString("16:39");
	timeText.setPosition(1148, 35);

	dateText.setFont(font);
	dateText.setCharacterSize(18);
	dateText.setFillColor(sf::Color::Black);
	dateText.setString("11/18/2021");
	dateText.setPosition(1130, 60);

	bankAccountText.setFont(font);
	bankAccountText.setCharacterSize(18);
	bankAccountText.setFillColor(sf::Color::Black);
	bankAccountText.setString("Personal bank account");
	bankAccountText.setPosition(5, 35);

	moneyText.setFont(font);
	moneyText.setCharacterSize(20);
	moneyText.setFillColor(sf::Color::Black);
	moneyText.setString("1620,33 EUR");
	moneyText.setPosition(5, 56);

	//PieChart
	pChart.initPieChart(font);

	//text
	newsText.setPosition(10, 86);
	newsText.setFont(font);
	newsText.setCharacterSize(40);
	newsText.setFillColor(sf::Color::White);
	newsText.setOutlineColor(sf::Color(29, 161, 242));
	newsText.setOutlineThickness(3);
	newsText.setString("Chatter");

	newsText2.setPosition(10, 150);
	newsText2.setFont(font);
	newsText2.setCharacterSize(20);
	newsText2.setFillColor(sf::Color::Black);;
	newsText2.setString("Chatter is currently down for maintenace.");

	lifestyleText.setPosition(500, 150);
	lifestyleText.setFont(font);
	lifestyleText.setCharacterSize(20);
	lifestyleText.setFillColor(sf::Color::Black);;
	lifestyleText.setString("You are alive!\nthis text is not centered just so you know. I could change it but no.");

	shopText.setPosition(500, 150);
	shopText.setFont(font);
	shopText.setCharacterSize(40);
	shopText.setFillColor(sf::Color::Black);;
	shopText.setString("     Error 404:\nPage not found");

	settingsText.setPosition(300, 150);
	settingsText.setFont(font);
	settingsText.setCharacterSize(20);
	settingsText.setFillColor(sf::Color::Black);;
	settingsText.setString("All settings have been succesfully changed!\nThe game is perfect as it is no need to change anything\nor i didn't have enough time to make an actual settings menu.");
}

Game::Game() { 
	initWindow();
	initTextures();
	initGUI();
	tradingPage.initTradingMarket(this->font);
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
				homeButton.ChangeButton(textures["Home_button_selected"]);
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
			if (scene == TRADE_MARKET) {
				tradingPage.mouseCheck(*window);
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
		tradingPage.renderTradeMarket(*window);
	}
	else if (scene == NEWS) {
		window->draw(newsText);
		window->draw(newsText2);
	}
	else if (scene == LIFESTYLE) {
		window->draw(lifestyleText);
	}
	else if (scene == SHOP) {
		window->draw(shopText);
	}
	else if (scene == FINANCES) {

	}
	else if (scene == SETTINGS) {
		window->draw(settingsText);
	}
	

	window->display();
}

void Game::renderGUI() {
	window->draw(bar);
	window->draw(timeText);
	window->draw(dateText);
	window->draw(bankAccountText);
	window->draw(moneyText);

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
	pChart.draw(*window);
	window->draw(totalValueText);
	window->draw(totalValueMoneyText);
}
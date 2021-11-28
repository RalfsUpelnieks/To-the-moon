#include "TradingMarket.h"

void TradingMarket::initTradingMarket(const sf::Font& font) {
	this->font = font;

	//buttons
	textures["stocks_button"] = new sf::Texture();
	textures["stocks_button"]->loadFromFile("Textures/Stock_button.png");
	textures["stocks_button_selected"] = new sf::Texture();
	textures["stocks_button_selected"]->loadFromFile("Textures/Stocks_button_selected.png");

	textures["Crypto_button"] = new sf::Texture();
	textures["Crypto_button"]->loadFromFile("Textures/Crypto_button.png");
	textures["Crypto_button_selected"] = new sf::Texture();
	textures["Crypto_button_selected"]->loadFromFile("Textures/Crypto_button_selected.png");

	textures["buy_button"] = new sf::Texture();
	textures["buy_button"]->loadFromFile("Textures/Buy_button.png");
	textures["buy_button_selected"] = new sf::Texture();
	textures["buy_button_selected"]->loadFromFile("Textures/Buy_button_selected.png");

	textures["short_button"] = new sf::Texture();
	textures["short_button"]->loadFromFile("Textures/Short_button.png");
	textures["short_button_selected"] = new sf::Texture();
	textures["short_button_selected"]->loadFromFile("Textures/Short_button_selected.png");

	textures["up_button"] = new sf::Texture();
	textures["up_button"]->loadFromFile("Textures/Up_button.png");
	textures["up_button_selected"] = new sf::Texture();
	textures["up_button_selected"]->loadFromFile("Textures/Up_button_selected.png");

	textures["down_button"] = new sf::Texture();
	textures["down_button"]->loadFromFile("Textures/Down_button.png");
	textures["down_button_selected"] = new sf::Texture();
	textures["down_button_selected"]->loadFromFile("Textures/Down_button_selected.png");

	textures["sell_button"] = new sf::Texture();
	textures["sell_button"]->loadFromFile("Textures/Sell_button.png");

	//trade market lines
	verticalLine1.setSize(sf::Vector2f(1, 635));
	verticalLine1.setPosition(sf::Vector2f(930, 85));
	verticalLine1.setFillColor(lineColor);

	verticalLine2.setSize(sf::Vector2f(1, 340));
	verticalLine2.setPosition(sf::Vector2f(200, 85));
	verticalLine2.setFillColor(lineColor);

	verticalLine3.setSize(sf::Vector2f(1, 635));
	verticalLine3.setPosition(sf::Vector2f(600, 426));
	verticalLine3.setFillColor(lineColor);

	horizontalLine1.setSize(sf::Vector2f(930, 1));
	horizontalLine1.setPosition(sf::Vector2f(0, 425));
	horizontalLine1.setFillColor(lineColor);

	//Left information panel objects
	invNameText.setPosition(4, 86);
	invNameText.setFillColor(sf::Color(40, 40, 40));
	invNameText.setFont(this->font);
	invNameText.setCharacterSize(18);
	
	//porfolio objects
	portfolioPanel.setSize(sf::Vector2f(200, 30));
	portfolioPanel.setPosition(sf::Vector2f(0, 395));
	portfolioPanel.setFillColor(sf::Color(240, 240, 240));
	portfolioPanel.setOutlineColor(lineColor);
	portfolioPanel.setOutlineThickness(1);

	portfolioText.setPosition(8, 400);
	portfolioText.setFillColor(sf::Color(40, 40, 40));
	portfolioText.setFont(this->font);
	portfolioText.setCharacterSize(18);
	portfolioText.setString("Portfolio");

	//Select tab objects
	selectVrtLine1.setSize(sf::Vector2f(1, 32));
	selectVrtLine1.setPosition(sf::Vector2f(1120, 118));
	selectVrtLine1.setFillColor(lineColor);

	selectVrtLine2.setSize(sf::Vector2f(1, 32));
	selectVrtLine2.setPosition(sf::Vector2f(1200, 118));
	selectVrtLine2.setFillColor(lineColor);

	selectPanel.setSize(sf::Vector2f(350, 30));
	selectPanel.setPosition(sf::Vector2f(931, 119));
	selectPanel.setFillColor(sf::Color(240, 240, 240));
	selectPanel.setOutlineColor(lineColor);
	selectPanel.setOutlineThickness(1);

	nameText.setPosition(936, 126);
	nameText.setFillColor(sf::Color(40, 40, 40));
	nameText.setFont(this->font);
	nameText.setCharacterSize(18);
	nameText.setString("Name");

	volText.setPosition(1126, 126);
	volText.setFillColor(sf::Color(40, 40, 40));
	volText.setFont(this->font);
	volText.setCharacterSize(18);
	volText.setString("Vol");

	priceText.setPosition(1206, 126);
	priceText.setFillColor(sf::Color(40, 40, 40));
	priceText.setFont(this->font);
	priceText.setCharacterSize(18);
	priceText.setString("Price");

	stocksButton.Button(textures["stocks_button_selected"], 930.f, 85.f);
	cryptoButton.Button(textures["Crypto_button"], 1105.f, 85.f);

	//order panel
	orderPanel.setSize(sf::Vector2f(329, 30));
	orderPanel.setPosition(sf::Vector2f(601, 426));
	orderPanel.setFillColor(sf::Color(240, 240, 240));
	orderPanel.setOutlineColor(lineColor);
	orderPanel.setOutlineThickness(1);

	orderText.setPosition(716, 430);
	orderText.setFillColor(sf::Color(40, 40, 40));
	orderText.setFont(this->font);
	orderText.setCharacterSize(18);
	orderText.setString("Order menu");

	orderPanel1.setSize(sf::Vector2f(130, 40));
	orderPanel1.setPosition(sf::Vector2f(601.f, 544.f));
	orderPanel1.setFillColor(sf::Color(240, 240, 240));
	orderPanel1.setOutlineColor(lineColor);
	orderPanel1.setOutlineThickness(1);

	orderPanel2.setSize(sf::Vector2f(130, 40));
	orderPanel2.setPosition(sf::Vector2f(601.f, 652.f));
	orderPanel2.setFillColor(sf::Color(240, 240, 240));
	orderPanel2.setOutlineColor(lineColor);
	orderPanel2.setOutlineThickness(1);

	upButton.Button(textures["up_button"], 600.f, 516.f);
	buyButton.Button(textures["buy_button"], 600.f, 584.f);
	shortButton.Button(textures["short_button"], 600.f, 618.f);
	downButton.Button(textures["down_button"], 600.f, 692.f);
	sellButton.Button(textures["sell_button"], 799.f, 600.f);
	
	//Random numbers move along please
	crypto[0].init("Megabitcoin(MTC)", 69420.f, 0.01f, 500000.f);
	crypto[1].init("Catcoin(CAT)", 0.2f, 0.01f, 1000.f);
	crypto[2].init("Athereum(ATH)", 540.f, 100.f, 500000.f);
	crypto[3].init("Finance Coin(FNF)", 49.f, 10.f, 500000.f);
	crypto[4].init("SHALIBA UNI(SHAL)", 429.f, 0.01f, 500000.f);
	crypto[5].init("Heavycoin(HVC)", 4.f, 1.f, 5000.f);

	stocks[0].init("Nikola(NIKL)", 1081.f, 1.f, 400000.f);

	plot.initPlot(sf::Vector2f(250, 85), sf::Vector2f(640, 340), 40, font);
	plot.setValue(stocks[stockSelected].getPrice(), stocks[stockSelected].getVol());
	updatePage();
}

void TradingMarket::renderTradeMarket(sf::RenderTarget& window) {
	if (clock.getElapsedTime().asMilliseconds() > 1000) {
		clock.restart();
		for (int i = 0; i < sizeof(crypto) / sizeof(crypto[0]); ++i) {
			crypto[i].newPrice();
		}
		for (int i = 0; i < sizeof(stocks) / sizeof(stocks[0]); ++i) {
			stocks[i].newPrice();
		}
		updatePage();
	}
	
	plot.GenerateVertices();
	plot.draw(window);

	window.draw(verticalLine1);
	window.draw(verticalLine2);
	window.draw(verticalLine3);
	window.draw(horizontalLine1);
	
	//portfolio objects
	window.draw(portfolioPanel);
	window.draw(portfolioText);
	//select panel objects
	window.draw(selectPanel);
	window.draw(selectVrtLine1);
	window.draw(selectVrtLine2);
	window.draw(invNameText);
	window.draw(nameText);
	window.draw(volText);
	window.draw(priceText);

	for (int i = 0; i < investPanelArray.size(); i++) {
		window.draw(investPanelArray[i]);
	}
	for (int i = 0; i < TextArray.size(); i++) {
		window.draw(TextArray[i]);
	}

	stocksButton.draw(window);
	cryptoButton.draw(window);

	//order menu
	window.draw(orderPanel);
	window.draw(orderText);
	window.draw(orderPanel1);
	window.draw(orderPanel2);
	upButton.draw(window);
	buyButton.draw(window);
	shortButton.draw(window);
	downButton.draw(window);

	sellButton.draw(window);
}

void TradingMarket::updatePage() {
	if (showingTab == STOCK) {
		plot.setValue(stocks[stockSelected].getPrice(), stocks[stockSelected].getVol());
		invNameText.setString(stocks[stockSelected].getName());
	}
	else {
		plot.setValue(crypto[stockSelected].getPrice(), crypto[stockSelected].getVol());
		invNameText.setString(crypto[stockSelected].getName());
	}

	TextArray.clear();
	investPanelArray.clear();
	sf::RectangleShape investPanel;
	sf::Text investNameText;
	sf::Text investVolText;
	sf::Text investPriceText;
	int size;
	if (selectedTab == STOCK) {
		size = sizeof(stocks) / sizeof(stocks[0]);
	}
	else {
		size = sizeof(crypto) / sizeof(crypto[0]);
	}

	for (int i = 0; i < size; ++i) {
		investPanel.setSize(sf::Vector2f(350, 30));
		investPanel.setPosition(sf::Vector2f(931, 150 + 30 * i));
		investPanel.setFillColor(sf::Color(196, 196, 196));
		investPanel.setOutlineColor(lineColor);
		investPanel.setOutlineThickness(1);

		investNameText.setPosition(936, 155 + 30 * i);
		investNameText.setFillColor(sf::Color(40, 40, 40));
		investNameText.setFont(this->font);
		investNameText.setCharacterSize(16);

		investVolText.setPosition(1122, 155 + 30 * i);
		investVolText.setFillColor(sf::Color(40, 40, 40));
		investVolText.setFont(this->font);
		investVolText.setCharacterSize(16);

		investPriceText.setPosition(1202, 155 + 30 * i);
		investPriceText.setFillColor(sf::Color(40, 40, 40));
		investPriceText.setFont(this->font);
		investPriceText.setCharacterSize(16);

		std::stringstream stream;
		if (selectedTab == STOCK) {
			investNameText.setString(stocks[i].getName());
			investVolText.setString(std::to_string(stocks[i].getVol().back()));
			stream << std::fixed << std::setprecision(2) << stocks[i].getPrice().back();
			investPriceText.setString(stream.str());
		}
		else {
			investNameText.setString(crypto[i].getName());
			investVolText.setString(std::to_string(crypto[i].getVol().back()));
			stream << std::fixed << std::setprecision(2) << crypto[i].getPrice().back();
			investPriceText.setString(stream.str());
		}
		investPanelArray.push_back(investPanel);
		TextArray.push_back(investNameText);
		TextArray.push_back(investVolText);
		TextArray.push_back(investPriceText);
	}
	if (selectedTab == showingTab) {
		investPanelArray[stockSelected].setFillColor(sf::Color(121, 125, 128));
	}
}

void TradingMarket::mouseCheck(sf::RenderWindow& window) {
	float mouseX = sf::Mouse::getPosition(window).x;
	float mouseY = sf::Mouse::getPosition(window).y;
	
	if (selectedTab != STOCK && stocksButton.isMouseOver(window)) {
		stocksButton.ChangeButton(textures["stocks_button_selected"]);
		cryptoButton.ChangeButton(textures["Crypto_button"]);
		selectedTab = STOCK;
		updatePage();
	}
	else if (selectedTab != CRYPTO && cryptoButton.isMouseOver(window)) {
		cryptoButton.ChangeButton(textures["Crypto_button_selected"]);
		stocksButton.ChangeButton(textures["stocks_button"]);
		selectedTab = CRYPTO;
		updatePage();
	}

	int size;
	if (selectedTab == STOCK) {
		size = sizeof(stocks) / sizeof(stocks[0]);
	}
	else {
		size = sizeof(crypto) / sizeof(crypto[0]);
	}

	for (int i = 0; i < size; ++i) {
		if (investPanelArray[i].getGlobalBounds().contains(mouseX, mouseY)) {
			stockSelected = i;
			if (selectedTab == STOCK) {
				showingTab = STOCK;
			}
			else {
				showingTab = CRYPTO;
			}
			updatePage();
		}
		
	}
}
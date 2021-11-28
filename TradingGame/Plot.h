#pragma once

#include <iomanip>
#include <sstream>
#include <numeric>
#include <vector>
#include <iostream>
#include "SFML/Graphics.hpp"


class Plot {
private:
    sf::Vector2f origin;
    sf::Vector2f dimension;
    float margin;

    std::vector<float> priceValues;
    std::vector<int> volValues;
    sf::Vector2f CoordBounds;
    sf::Vector2f CoordSteps;

    sf::Font font;

    sf::Color mainColor = sf::Color::Black;
    sf::Color borderColor = sf::Color(135, 135, 135);
    sf::Color barColor;
    sf::Color lineColor = sf::Color(0, 106, 255);

    sf::VertexArray borderVertexArray;
    sf::VertexArray IndicatorLinesVertexArray;
    std::vector<sf::VertexArray> dataSetsVertexArray;
    std::vector<sf::Text> textElementArray;

    void ClearVertices();

    sf::Vector2f CoordToWindowPosition(const sf::Vector2f& loc);

    sf::Vector2f CoordToWindowPositionVol(const sf::Vector2f& coords);

    std::string ToString(const double& d, const size_t& precision = 2);
public:
    void draw(sf::RenderTarget& target);

    void initPlot(const sf::Vector2f& position, const sf::Vector2f& dimension, const float& margin, const sf::Font& font);

    void PlotData(float ymin, float ymax, const std::vector<float>& values);

    void GenerateVertices(); 

    void setValue(const std::vector<float>& priceValues, const std::vector<int>& values);
};
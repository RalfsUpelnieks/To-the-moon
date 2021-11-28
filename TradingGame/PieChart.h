#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <sstream>

#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

class PieChart {
private:
    sf::Vector2f position;
    float radius;

    std::vector<sf::VertexArray> pieSegments;
    std::vector<sf::Text> textElements;

    std::vector<float> values;
    std::vector<std::string> labels;
    std::vector<sf::Color> colors;

    sf::CircleShape circle;
    
public:

    void initPieChart(sf::Font font);

    sf::Font font;

    void PieChartData(const std::vector<float>& values);

    void GenerateVertices();

    void ClearVertices();

    void draw(sf::RenderTarget& window);
};



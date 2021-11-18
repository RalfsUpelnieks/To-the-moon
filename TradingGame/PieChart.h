#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <iomanip>
#include <sstream>

#include "SFML/Graphics.hpp"
#include <iostream>
#include <vector>

class PieChart : public sf::Drawable {
private:
    sf::Vector2f _position;
    float _radius;

    std::vector<sf::VertexArray> _pieSegments;
    std::vector<sf::Text> _textElements;

    std::vector<float> _values;
    std::vector<std::string> _labels;
    std::vector<sf::Color> _colors;

    sf::CircleShape circle;
    
public:

    void initPieChart(sf::Font font);

    sf::Font _font;

    void PieChartData(const std::vector<float>& values);

    void GenerateVertices();

    void ClearVertices();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};



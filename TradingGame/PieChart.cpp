#include "PieChart.h"
#include "Game.h"



void PieChart::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < _pieSegments.size(); i++) {
        target.draw(_pieSegments[i], states);
    }

    for (int i = 0; i < _textElements.size(); i++) {
        target.draw(_textElements[i]);
    }
    target.draw(circle);
}

void PieChart::initPieChart(sf::Font font) {
    _labels = { "Money", "Materials", "Stocks", "Properties", "Cryptocurrency" };
    _colors = { sf::Color(28, 199, 39), sf::Color(143, 143, 143), sf::Color(0, 166, 255), sf::Color(255, 152, 79),  sf::Color(255, 242, 0) };
    _position = sf::Vector2f(150, 200);
    _radius = 100;
    _font = font;

    circle.setRadius(_radius - 10);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(_position);
    circle.setFillColor(sf::Color(255, 255, 255));
}

void PieChart::PieChartData(const std::vector<float>& values) {
    _values = values;
}

void PieChart::GenerateVertices() {
    this->ClearVertices();
    float totalSegmentsValue = 0.f;
    for (size_t i = 0; i < _values.size(); i++) {
        totalSegmentsValue += _values[i];
    }
    float segmentBaseAngle = static_cast<float>(-M_PI / 2);
    float angleStep = static_cast<float>(2 * M_PI / 360);

    float charSize = _radius * 0.15f;
    sf::Vector2f legendBasePosition = sf::Vector2f(_position.x + _radius + 10, _position.y);
    legendBasePosition.y -= (_values.size() / 2) * charSize;
    
    for (int i = 0; i < _values.size(); i++) {
        sf::VertexArray segment;
        segment.setPrimitiveType(sf::PrimitiveType::TriangleFan);

        //Middle point
        segment.append(sf::Vertex(_position, _colors[i]));

        float segmentAngle = (_values[i] / totalSegmentsValue) * static_cast<float>(2 * M_PI);

        for (float theta = segmentBaseAngle; theta < segmentBaseAngle + segmentAngle + angleStep; theta += angleStep) {
            float xPos = _position.x + _radius * cos(theta);
            float yPos = _position.y + _radius * sin(theta);

            segment.append(sf::Vertex(sf::Vector2f(xPos, yPos), _colors[i]));
        }

        _pieSegments.push_back(segment);
        segmentBaseAngle += segmentAngle;
        // Text
        sf::Text text;
        text.setFont(_font);

        //string conversion
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << _values[i] / totalSegmentsValue * 100;
        std::string label = stream.str() + "%" + " - " + _labels[i];

        text.setString(label);
        text.setFillColor(_colors[i]);
        text.setPosition(legendBasePosition);
        text.setCharacterSize(static_cast<unsigned int>(charSize));

        sf::FloatRect fr = text.getLocalBounds();
        text.move(0, i * fr.height * 1.2f);
        _textElements.push_back(text);
    }
}

void PieChart::ClearVertices() {
    _pieSegments.clear();
    _textElements.clear();
}
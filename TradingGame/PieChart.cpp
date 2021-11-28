#include "PieChart.h"
#include "Game.h"

void PieChart::draw(sf::RenderTarget& window) {
    for (int i = 0; i < pieSegments.size(); i++) {
        window.draw(pieSegments[i]);
    }

    for (int i = 0; i < textElements.size(); i++) {
        window.draw(textElements[i]);
    }
    window.draw(circle);
}

void PieChart::initPieChart(sf::Font font) {
    this->labels = { "Money", "Materials", "Stocks", "Properties", "Cryptocurrency" };
    this->colors = { sf::Color(28, 199, 39), sf::Color(143, 143, 143), sf::Color(0, 166, 255), sf::Color(255, 152, 79),  sf::Color(255, 242, 0) };
    this->position = sf::Vector2f(120, 200);
    this->radius = 100;
    this->font = font;

    this->circle.setRadius(this->radius - 10);
    this->circle.setOrigin(this->circle.getRadius(), this->circle.getRadius());
    this->circle.setPosition(this->position);
    this->circle.setFillColor(sf::Color(255, 255, 255));
}

void PieChart::PieChartData(const std::vector<float>& values) {
    this->values = values;
}

void PieChart::GenerateVertices() {
    this->ClearVertices();
    float totalSegmentsValue = 0.f;
    for (size_t i = 0; i < values.size(); i++) {
        totalSegmentsValue += values[i];
    }
    float segmentBaseAngle = static_cast<float>(-M_PI / 2);
    float angleStep = static_cast<float>(2 * M_PI / 360);
    float charSize = radius * 0.15f;

    sf::Vector2f legendBasePosition = sf::Vector2f(position.x + radius + 10, position.y);
    legendBasePosition.y -= (values.size() / 2) * charSize;
    
    for (int i = 0; i < values.size(); i++) {
        sf::VertexArray segment;
        segment.setPrimitiveType(sf::PrimitiveType::TriangleFan);

        //Middle point
        segment.append(sf::Vertex(position, colors[i]));

        float segmentAngle = (values[i] / totalSegmentsValue) * static_cast<float>(2 * M_PI);

        for (float theta = segmentBaseAngle; theta < segmentBaseAngle + segmentAngle + angleStep; theta += angleStep) {
            float xPos = position.x + radius * cos(theta);
            float yPos = position.y + radius * sin(theta);

            segment.append(sf::Vertex(sf::Vector2f(xPos, yPos), colors[i]));
        }

        this->pieSegments.push_back(segment);
        segmentBaseAngle += segmentAngle;
        // Text
        sf::Text text;
        text.setFont(font);

        //string conversion
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << values[i] / totalSegmentsValue * 100;
        std::string label = stream.str() + "%" + " - " + labels[i];

        text.setString(label);
        text.setFillColor(colors[i]);
        text.setPosition(legendBasePosition);
        text.setCharacterSize(static_cast<unsigned int>(charSize));

        sf::FloatRect fr = text.getLocalBounds();
        text.move(0, i * fr.height * 1.2f);
        textElements.push_back(text);
    }
}

void PieChart::ClearVertices() {
    this->pieSegments.clear();
    this->textElements.clear();
}
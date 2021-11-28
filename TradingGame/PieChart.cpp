#include "PieChart.h"
#include "Game.h"

void PieChart::draw(sf::RenderTarget& window) {
    for (int i = 0; i < this->pieSegments.size(); i++) {
        window.draw(this->pieSegments[i]);
    }

    for (int i = 0; i < this->textElements.size(); i++) {
        window.draw(this->textElements[i]);
    }
    window.draw(this->circle);
}

void PieChart::initPieChart(sf::Font font) {
    this->labels = { "Money", "Materials", "Stocks", "Properties", "Cryptocurrency" };
    this->colors = { sf::Color(28, 199, 39), sf::Color(143, 143, 143), sf::Color(0, 166, 255), sf::Color(255, 152, 79),  sf::Color(255, 242, 0) };
    this->position = sf::Vector2f(150, 200);
    this->radius = 100;
    this->font = font;

    circle.setRadius(this->radius - 10);
    circle.setOrigin(this->circle.getRadius(), this->circle.getRadius());
    circle.setPosition(this->position);
    circle.setFillColor(sf::Color(255, 255, 255));
}

void PieChart::PieChartData(const std::vector<float>& values) {
    this->values = values;
}

void PieChart::GenerateVertices() {
    this->ClearVertices();
    float totalSegmentsValue = 0.f;
    for (size_t i = 0; i < this->values.size(); i++) {
        totalSegmentsValue += this->values[i];
    }
    float segmentBaseAngle = static_cast<float>(-M_PI / 2);
    float angleStep = static_cast<float>(2 * M_PI / 360);
    float charSize = this->radius * 0.15f;

    sf::Vector2f legendBasePosition = sf::Vector2f(this->position.x + this->radius + 10, this->position.y);
    legendBasePosition.y -= (this->values.size() / 2) * charSize;
    
    for (int i = 0; i < this->values.size(); i++) {
        sf::VertexArray segment;
        segment.setPrimitiveType(sf::PrimitiveType::TriangleFan);

        //Middle point
        segment.append(sf::Vertex(this->position, this->colors[i]));

        float segmentAngle = (this->values[i] / totalSegmentsValue) * static_cast<float>(2 * M_PI);

        for (float theta = segmentBaseAngle; theta < segmentBaseAngle + segmentAngle + angleStep; theta += angleStep) {
            float xPos = this->position.x + this->radius * cos(theta);
            float yPos = this->position.y + this->radius * sin(theta);

            segment.append(sf::Vertex(sf::Vector2f(xPos, yPos), this->colors[i]));
        }

        this->pieSegments.push_back(segment);
        segmentBaseAngle += segmentAngle;
        // Text
        sf::Text text;
        text.setFont(this->font);

        //string conversion
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << this->values[i] / totalSegmentsValue * 100;
        std::string label = stream.str() + "%" + " - " + this->labels[i];

        text.setString(label);
        text.setFillColor(this->colors[i]);
        text.setPosition(legendBasePosition);
        text.setCharacterSize(static_cast<unsigned int>(charSize));

        sf::FloatRect fr = text.getLocalBounds();
        text.move(0, i * fr.height * 1.2f);
        this->textElements.push_back(text);
    }
}

void PieChart::ClearVertices() {
    this->pieSegments.clear();
    this->textElements.clear();
}
#include "Plot.h"

void Plot::draw(sf::RenderTarget& window) {
    window.draw(IndicatorLinesVertexArray);
    window.draw(borderVertexArray);
    for (int i = 0; i < dataSetsVertexArray.size(); i++) {
        window.draw(dataSetsVertexArray[i]);
    }
    for (int i = 0; i < textElementArray.size(); i++) {
        window.draw(textElementArray[i]);
    }
}

void Plot::initPlot(const sf::Vector2f& position, const sf::Vector2f& dimension, const float& margin, const sf::Font& font) {
    this->origin = position;
    this->dimension = dimension;
    this->margin = margin;
    this->font = font;
}

void Plot::PlotData(float ymin, float ymax, const std::vector<float>& values) {
    float averageValue = std::round(std::accumulate(values.begin(), values.end(), 0.0) / values.size());
    CoordSteps.y = 0;

    do {
        if (averageValue < 10) {
            CoordSteps.y += 0.1;
        }
        else if (averageValue < 20) {
            CoordSteps.y += 0.5;
        }
        else if (averageValue < 50) {
            CoordSteps.y += 1;
        }
        else if (averageValue < 100) {
            CoordSteps.y += 1;
        }
        else if (averageValue >= 100) {
            CoordSteps.y += 2;
        }

        CoordBounds.x = averageValue - CoordSteps.y * 3;
        CoordBounds.y = averageValue + CoordSteps.y * 3;

        if (CoordBounds.x < 0) {
            CoordBounds.x = 0;
            CoordBounds.y = CoordSteps.y * 6;
        }
    } while (ymin < CoordBounds.x or ymax > CoordBounds.y);
}

void Plot::setValue(const std::vector<float>& priceValues, const std::vector<int>& volValues) {
    this->priceValues = priceValues;
    this->volValues = volValues;

    float ymin = INFINITY;
    float ymax = -INFINITY;

    for (int i = 0; i < priceValues.size(); i++) {
        float setMinY = *std::min_element(priceValues.begin(), priceValues.end());
        float setMaxY = *std::max_element(priceValues.begin(), priceValues.end());

        if (setMinY < ymin) {
            ymin = setMinY;
        }

        if (setMaxY > ymax) {
            ymax = setMaxY;
        }
    }

    if (CoordBounds.x == NULL or ymin < CoordBounds.x or ymax > CoordBounds.y or (CoordBounds.y - CoordBounds.x) * 0.6 > ymax - ymin) {
        Plot::PlotData(ymin, ymax, priceValues);
    }
}

void Plot::GenerateVertices() {
    this->ClearVertices();
    const auto characterSize = static_cast<unsigned int>(margin * 0.35);

    // Border
    borderVertexArray.setPrimitiveType(sf::LineStrip);
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(0, CoordBounds.y - CoordBounds.x)), borderColor));
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(0, 0)), borderColor));
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(priceValues.size() - 1.f, 0)), borderColor));
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(priceValues.size() - 1.f, CoordBounds.y - CoordBounds.x)), borderColor));
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(0, CoordBounds.y - CoordBounds.x)), mainColor));

    IndicatorLinesVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
    
    int maxVol = 180000;
    int vol = 0;
    int volStep = maxVol / 6;

    for (float y = CoordBounds.x; y <= CoordBounds.y; y += CoordSteps.y) {
    
        //indicator
        sf::Vector2f windowPosition = CoordToWindowPosition(sf::Vector2f(0, y - CoordBounds.x));

        IndicatorLinesVertexArray.append(sf::Vertex(windowPosition, sf::Color(217, 217, 217)));
        IndicatorLinesVertexArray.append(sf::Vertex(sf::Vector2f(windowPosition.x + dimension.x - 12, windowPosition.y), sf::Color(217, 217, 217)));

        //Price text
        sf::Text priceIndicatorText;
        priceIndicatorText.setCharacterSize(characterSize);
        priceIndicatorText.setFont(font);
        if (CoordSteps.y < 1) {
            priceIndicatorText.setString(ToString(y, 1));
        }
        else {
            priceIndicatorText.setString(ToString(y, 0));
        }
        priceIndicatorText.setFillColor(mainColor);
        sf::Vector2f pricePosition = CoordToWindowPosition(sf::Vector2f(priceValues.size() - 0.8f, y - CoordBounds.x));
        //check if first or last text and sets position
        if (y == CoordBounds.x) {
            priceIndicatorText.setPosition(pricePosition.x, pricePosition.y - 16);
        }
        else if (y == CoordBounds.x + CoordSteps.y * 6) {
            priceIndicatorText.setPosition(pricePosition.x, pricePosition.y - 2);
        }
        else {
            priceIndicatorText.setPosition(pricePosition.x, pricePosition.y - 8);
        }

        textElementArray.push_back(priceIndicatorText);

        //Vol text
        if (y < CoordBounds.x + CoordSteps.y * 3) {
            sf::Text volIndicatorText;
            volIndicatorText.setCharacterSize(characterSize);
            volIndicatorText.setFont(font);
            if (vol == 0) {
                volIndicatorText.setString(ToString(vol / 1000, 0));
                volIndicatorText.setPosition(windowPosition.x - (margin * 0.25f), windowPosition.y - 9);
            }
            else {
                volIndicatorText.setString(ToString(vol / 1000, 0) + "K");
                volIndicatorText.setPosition(windowPosition.x - (margin * 0.25f), windowPosition.y - 5);
            }
            volIndicatorText.setFillColor(mainColor);
            volIndicatorText.move(-volIndicatorText.getLocalBounds().width - 2, -volIndicatorText.getLocalBounds().height / 2);
            textElementArray.push_back(volIndicatorText);
            vol += volStep;
        }
    }

    //Generate data lines
    sf::VertexArray graph1;
    sf::VertexArray graph2;

    graph1.setPrimitiveType(sf::PrimitiveType::LinesStrip);

    for (float i = 0; i < priceValues.size(); i++) {
        sf::Vector2f windowPosition = CoordToWindowPosition(sf::Vector2f{ i, priceValues[i] - CoordBounds.x});
        graph1.append(sf::Vertex(windowPosition, lineColor));
    }

    // Generates bars
    graph2.setPrimitiveType(sf::PrimitiveType::Quads);

    for (float i = 1; i < priceValues.size(); i++) {
        if (priceValues[i] - priceValues[i - 1] < 0) {
            barColor = sf::Color::Red;
        }
        else {
            barColor = sf::Color::Green;
        }

        sf::Vector2f dataValue = sf::Vector2f{i, (float)volValues[i]};
        sf::Vector2f windowPosition = CoordToWindowPositionVol(dataValue);
        sf::Vector2f zeroWindowPosition = CoordToWindowPositionVol(sf::Vector2f(dataValue.x, 0));

        graph2.append(sf::Vertex(sf::Vector2f((windowPosition.x - 2) - 2.5, windowPosition.y), barColor));
        graph2.append(sf::Vertex(sf::Vector2f((windowPosition.x + 2) - 2.5, windowPosition.y), barColor));
        graph2.append(sf::Vertex(sf::Vector2f((zeroWindowPosition.x + 2) - 2.5, zeroWindowPosition.y), barColor));
        graph2.append(sf::Vertex(sf::Vector2f((zeroWindowPosition.x - 2) - 2.5, zeroWindowPosition.y), barColor));
    }
    dataSetsVertexArray.push_back(graph2);
    dataSetsVertexArray.push_back(graph1);
}

void Plot::ClearVertices() {
    borderVertexArray.clear();
    IndicatorLinesVertexArray.clear();
    dataSetsVertexArray.clear();
    textElementArray.clear();
}

sf::Vector2f Plot::CoordToWindowPosition(const sf::Vector2f& coords) {
    sf::Vector2f windowPosition;
    windowPosition.x = origin.x + (dimension.x * (coords.x / priceValues.size()));
    windowPosition.y = origin.y + (dimension.y - dimension.y * (coords.y / (CoordBounds.y - CoordBounds.x)));
    return windowPosition;
}

sf::Vector2f Plot::CoordToWindowPositionVol(const sf::Vector2f& coords) {
    sf::Vector2f windowPosition;
    float yAxisMax = 180000;

    windowPosition.x = origin.x + (dimension.x * (coords.x / priceValues.size()));
    windowPosition.y = origin.y + (dimension.y - dimension.y * (coords.y / yAxisMax));
    return windowPosition;
}

std::string Plot::ToString(const double& d, const size_t& precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << d;
    return stream.str();
}
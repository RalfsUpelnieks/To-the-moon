#include "Plot.h"

void Plot::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(IndicatorLinesVertexArray, states);
    target.draw(borderVertexArray, states);
    for (int i = 0; i < dataSetsVertexArray.size(); i++) {
        target.draw(dataSetsVertexArray[i], states);
    }
    for (int i = 0; i < textElementArray.size(); i++) {
        target.draw(textElementArray[i], states);
    }
}

void Plot::initPlot(const sf::Vector2f& position, const sf::Vector2f& dimension, const float& margin, const sf::Font& font , const sf::Color& color) {
    this->origin = position;
    this->dimension = dimension;
    this->margin = margin;
    this->color = color;
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
    //Topleft
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(0, CoordBounds.y - CoordBounds.x)), mainColor));
    //Origin
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(0, 0)), mainColor));
    //BottomRight
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(priceValues.size() - 1.f, 0)), mainColor));
    //TopRight
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(priceValues.size() - 1.f, CoordBounds.y - CoordBounds.x)), mainColor));
    //Topleft
    borderVertexArray.append(sf::Vertex(CoordToWindowPosition(sf::Vector2f(0, CoordBounds.y - CoordBounds.x)), mainColor));

    IndicatorLinesVertexArray.setPrimitiveType(sf::PrimitiveType::Lines);
    
    int maxVol = 180000;
    int vol = 0;
    int volStep = maxVol / 6;

    for (float y = CoordBounds.x; y <= CoordBounds.y; y += CoordSteps.y) {
    
        //indicator
        sf::Vector2f windowPosition = CoordToWindowPosition(sf::Vector2f(0, y - CoordBounds.x));

        IndicatorLinesVertexArray.append(sf::Vertex(windowPosition, sf::Color(217, 217, 217)));
        IndicatorLinesVertexArray.append(sf::Vertex(sf::Vector2f(windowPosition.x + dimension.y - 6, windowPosition.y), sf::Color(217, 217, 217)));

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
        priceIndicatorText.setPosition(CoordToWindowPosition(sf::Vector2f(priceValues.size() + 3, y - CoordBounds.x)));
        
        sf::FloatRect tDimension = priceIndicatorText.getLocalBounds();
        priceIndicatorText.move(-tDimension.width - 2, -tDimension.height / 2);

        textElementArray.push_back(priceIndicatorText);

        //Vol text
        if (y < CoordBounds.x + CoordSteps.y * 3) {
            sf::Text volIndicatorText;
            volIndicatorText.setCharacterSize(characterSize);
            volIndicatorText.setFont(font);
            if (vol == 0) {
                volIndicatorText.setString(ToString(vol / 1000, 0));
            }
            else {
                volIndicatorText.setString(ToString(vol / 1000, 0) + "K");
            }
            volIndicatorText.setFillColor(mainColor);
            volIndicatorText.setPosition(windowPosition.x - (margin * 0.25f), windowPosition.y - 5);

            sf::FloatRect tDimension2 = volIndicatorText.getLocalBounds();
            volIndicatorText.move(-tDimension2.width - 2, -tDimension2.height / 2);

            textElementArray.push_back(volIndicatorText);
            vol += volStep;
        }
        
    }

    //Generate actual data lines

    sf::VertexArray graph1;
    sf::VertexArray graph2;

    sf::Color col = color;

    graph1.setPrimitiveType(sf::PrimitiveType::LinesStrip);

    for (float i = 0; i < priceValues.size(); i++) {
        sf::Vector2f windowPosition = CoordToWindowPosition(sf::Vector2f{ i, priceValues[i] - CoordBounds.x});
        graph1.append(sf::Vertex(windowPosition, col));
    }

    // Generates bars

    graph2.setPrimitiveType(sf::PrimitiveType::Quads);

    for (float i = 1; i < priceValues.size(); i++) {

        if (priceValues[i] - priceValues[i - 1] < 0) {
            col = sf::Color::Red;
        }
        else {
            col = sf::Color::Green;
        }

        sf::Vector2f dataValue = sf::Vector2f{i, (float)volValues[i]};
        sf::Vector2f windowPosition = CoordToWindowPositionVol(dataValue);
        sf::Vector2f zeroWindowPosition = CoordToWindowPositionVol(sf::Vector2f(dataValue.x, 0));

        graph2.append(sf::Vertex(sf::Vector2f((windowPosition.x - 2) - 2.5, windowPosition.y), col));
        graph2.append(sf::Vertex(sf::Vector2f((windowPosition.x + 2) - 2.5, windowPosition.y), col));

        graph2.append(sf::Vertex(sf::Vector2f((zeroWindowPosition.x + 2) - 2.5, zeroWindowPosition.y), col));
        graph2.append(sf::Vertex(sf::Vector2f((zeroWindowPosition.x - 2) - 2.5, zeroWindowPosition.y), col));
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

    float xAxisLength = dimension.x;
    float xAxisMax = priceValues.size();
    float yAxisLength = dimension.y;
    float yAxisMax = 180000;

    windowPosition.x = origin.x + (xAxisLength * (coords.x / xAxisMax));
    windowPosition.y = origin.y + (dimension.y - yAxisLength * (coords.y / yAxisMax));
    return windowPosition;
}

std::string Plot::ToString(const double& d, const size_t& precision) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << d;
    return stream.str();
}
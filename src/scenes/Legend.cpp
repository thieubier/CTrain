#include "Legend.hpp"

Legend::Legend(const sf::Vector2f& pos) : position(pos) {
    if (!font.loadFromFile("src/files/Roboto-Regular.ttf")) {
        throw std::runtime_error("Erreur : Impossible de charger la police 'Roboto-Regular.ttf'");
    }
}

void Legend::addEntry(const std::string& label, const sf::Color& color) {
    float offsetY = circles.size() * 30.0f;

    // Création d'une pastille
    sf::CircleShape circle(10.0f);
    circle.setFillColor(color);
    circle.setPosition(position.x, position.y + offsetY);
    circles.push_back(circle);

    // Création du texte correspondant
    sf::Text text(label, font, 14);
    text.setFillColor(sf::Color::Black);
    text.setPosition(position.x + 25.0f, position.y + offsetY - 5.0f);
    labels.push_back(text);
}

void Legend::draw(sf::RenderWindow& window) const {
    for (const auto& circle : circles) {
        window.draw(circle);
    }
    for (const auto& label : labels) {
        window.draw(label);
    }
}

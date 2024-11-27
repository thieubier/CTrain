#include "Cursor.hpp"

Cursor::Cursor() {
    shape.setRadius(15.0f);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Yellow);
    shape.setOutlineThickness(3.0f);
    shape.setOrigin(15.0f, 15.0f); // Centrer le curseur
}

void Cursor::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}

void Cursor::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

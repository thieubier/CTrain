#include "Switch.hpp"

Switch::Switch(const std::string name, const sf::Vector2f& position)
    : Rail(name, position, position), activeIndex(0) {}

void Switch::addConnection(Rail* rail) {
    connectedRails.push_back(rail);
}

void Switch::activateNextRail() {
    if (!connectedRails.empty()) {
        activeIndex = (activeIndex + 1) % connectedRails.size();
    }
}

Rail* Switch::getActiveRail() const {
    return connectedRails.empty() ? nullptr : connectedRails[activeIndex];
}

void Switch::draw(sf::RenderWindow& window) const {
    sf::CircleShape switchShape(12.0f); // Augmenter la taille
    switchShape.setPosition(position.x - 12, position.y - 12); // Centrer le cercle
    switchShape.setFillColor(activeIndex == 0 ? sf::Color(50, 205, 50) : sf::Color(220, 20, 60)); // Vert ou rouge
    switchShape.setOutlineColor(sf::Color::Black); // Bordure noire
    switchShape.setOutlineThickness(2.0f); // Bordure épaisse

    window.draw(switchShape);
}


#include "Rail.hpp"

#include <iostream>

Rail::Rail(const std::string name, const sf::Vector2f& start, const sf::Vector2f& end)
    : name(name), start(start), end(end), position(start), nextRail(nullptr), previousRail(nullptr) {}

void Rail::connectToNext(Rail* rail) {
    nextRail = rail;
}

void Rail::connectToPrevious(Rail* rail) {
     previousRail = rail;
}

std::string Rail::toString()
{
    return name + " " + std::to_string(start.x) + " " + std::to_string(end.x)
    + " " + std::to_string(start.y) + " " + std::to_string(end.y);
}

void Rail::draw(sf::RenderWindow& window) const {
    // Calcul de la direction et de la longueur
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159;

    // Rectangle représentant le rail
    sf::RectangleShape railShape(sf::Vector2f(length, 6.0f)); // Largeur de 6px
    railShape.setFillColor(sf::Color(169, 169, 169)); // Gris foncé pour les rails
    railShape.setOrigin(0, 3.0f); // Centré sur l'axe vertical
    railShape.setPosition(start);
    railShape.setRotation(angle);

    window.draw(railShape);
}


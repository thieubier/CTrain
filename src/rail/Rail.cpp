#include "Rail.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// Constructeur
Rail::Rail(const std::string& name, const sf::Vector2f& start, const sf::Vector2f& end)
    : name(name), start(start), end(end) {}

// Renvoie le nom du rail
const std::string& Rail::toString() const {
    return name;
}

// Ajoute une connexion entre un point de ce rail et un autre rail
void Rail::connect(const sf::Vector2f& point, Rail* rail) {
    connections.push_back({point, rail});
}

// Renvoie le rail connecté à un point donné
Rail* Rail::getConnectedRail(const sf::Vector2f& point) {
    for (const auto& connection : connections) {
        if (connection.point == point) {
            return connection.rail;
        }
    }
    return nullptr; // Aucun rail connecté trouvé
}

// Dessine le rail sur la fenêtre SFML
void Rail::draw(sf::RenderWindow& window) const {
    // Épaisseur des traits
    const float thickness = 4.0f;

    // Calcul de la direction du segment
    sf::Vector2f direction = end - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    direction /= length; // Normalisation

    // Longueur d'un segment et d'un espace pour les pointillés
    const float segmentLength = 15.0f;
    const float gapLength = 10.0f;

    // Décomposer le rail en segments pointillés
    float currentLength = 0.0f;
    while (currentLength < length) {
        sf::Vector2f segmentStart = start + direction * currentLength;
        sf::Vector2f segmentEnd = start + direction * std::min(currentLength + segmentLength, length);

        // Dessin d'une ligne pointillée avec épaisseur
        sf::RectangleShape segment(segmentEnd - segmentStart);
        segment.setPosition(segmentStart);
        segment.setSize({segmentLength, thickness});
        segment.setRotation(std::atan2(direction.y, direction.x) * 180.0f / M_PI);
        segment.setFillColor(sf::Color::White);

        window.draw(segment);

        // Passer au prochain segment
        currentLength += segmentLength + gapLength;
    }
}

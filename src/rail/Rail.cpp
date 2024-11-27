#include "Rail.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

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
    sf::Vertex line[] = {
        sf::Vertex(start, sf::Color::White),
        sf::Vertex(end, sf::Color::White)
    };
    window.draw(line, 2, sf::Lines);
}

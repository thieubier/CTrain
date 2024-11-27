#include "Switch.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructeur
Switch::Switch(const std::string& name, const sf::Vector2f& position)
    : Rail(name, position, position), isRight(false) {}

// Définit l'état du switch (droite ou gauche)
void Switch::setState(bool toRight) {
    isRight = toRight;
    std::cout << "Switch '" << name << "' mis à jour : état = " << (isRight ? "droite" : "gauche") << std::endl;
}

bool Switch::getState() const {
    return isRight;
}

// Obtenir le rail suivant selon l'état du switch
Rail* Switch::getNextRail() {
    if (connections.empty()) {
        std::cerr << "Switch '" << name << "' n'a aucune connexion." << std::endl;
        return nullptr;
    }

    Rail* nextRail = isRight ? (connections.size() > 1 ? connections[1].rail : nullptr) : connections[0].rail;

    if (nextRail) {
        std::cout << "Switch '" << name << "' retourne le rail : " << nextRail->toString()
                  << " (état : " << (isRight ? "droite" : "gauche") << ")" << std::endl;
    } else {
        std::cerr << "Switch '" << name << "' n'a pas de rail correspondant pour l'état : "
                  << (isRight ? "droite" : "gauche") << std::endl;
    }
    return nextRail;
}

// Ajouter une connexion au switch
void Switch::addConnection(const sf::Vector2f& point, Rail* rail) {
    connections.push_back({point, rail});
    std::cout << "Connexion ajoutée au switch '" << name << "' avec le rail '" << rail->toString()
              << "' au point : " << point.x << ", " << point.y << std::endl;
}

// Dessiner le switch
void Switch::draw(sf::RenderWindow& window) const {
    sf::CircleShape switchShape(12.0f);
    switchShape.setPosition(start.x - 12, start.y - 12); // Centrer le switch sur sa position
    switchShape.setFillColor(isRight ? sf::Color(220, 20, 60) : sf::Color(50, 205, 50)); // Rouge (droite) ou Vert (gauche)
    switchShape.setOutlineColor(sf::Color::Black);
    switchShape.setOutlineThickness(2.0f);

    window.draw(switchShape);
}

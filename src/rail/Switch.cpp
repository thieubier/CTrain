#include "Switch.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../settings/Globals.hpp" // Import du fichier Globals pour accéder aux rails globaux

// Constructeur
Switch::Switch(const std::string& name, const sf::Vector2f& position)
    : Rail(name, position, position), isRight(false) {}

// Définir l'état du switch
void Switch::setState(bool toRight) {
    isRight = toRight;
    std::cout << "Switch '" << name << "' mis à jour : état = " << (isRight ? "droite" : "gauche") << std::endl;
}

// Obtenir l'état actuel
bool Switch::getState() const {
    return isRight;
}

// Obtenir le rail suivant
Rail* Switch::getNextRail(const Rail* previousRail) {
    std::cout << "Switch '" << name << "' vérifie les connexions en dur." << std::endl;

    if (name == "railSwitch1") {
        if (previousRail->toString() == "rail1") {
            std::cout << "Switch '" << name << "' - rail entrant : rail1. ";
            return isRight ? &rail3 : &rail2;
        }
        if (previousRail->toString() == "rail2") {
            std::cout << "Switch '" << name << "' - rail entrant : rail2. ";
            return isRight ? &rail1 : &rail3;
        }
        if (previousRail->toString() == "rail3") {
            std::cout << "Switch '" << name << "' - rail entrant : rail3. ";
            return isRight ? &rail2 : &rail1;
        }
    } else if (name == "railSwitch2") {
        if (previousRail->toString() == "rail4") {
            std::cout << "Switch '" << name << "' - rail entrant : rail4. ";
            return isRight ? &rail6 : &rail7;
        }
        if (previousRail->toString() == "rail6") {
            std::cout << "Switch '" << name << "' - rail entrant : rail6. ";
            return isRight ? &rail7 : &rail4;
        }
        if (previousRail->toString() == "rail7") {
            std::cout << "Switch '" << name << "' - rail entrant : rail7. ";
            return isRight ? &rail4 : &rail6;
        }
    } else if (name == "railSwitch3") {
        if (previousRail->toString() == "rail5") {
            std::cout << "Switch '" << name << "' - rail entrant : rail5. ";
            return isRight ? &rail8 : &rail6;
        }
        if (previousRail->toString() == "rail6") {
            std::cout << "Switch '" << name << "' - rail entrant : rail6. ";
            return isRight ? &rail5 : &rail8;
        }
        if (previousRail->toString() == "rail8") {
            std::cout << "Switch '" << name << "' - rail entrant : rail8. ";
            return isRight ? &rail6 : &rail5;
        }
    }

    // Erreur : aucun cas ne correspond
    std::cerr << "Erreur : Switch '" << name << "' ne trouve aucune connexion pour le rail entrant : "
              << (previousRail ? previousRail->toString() : "nullptr") << std::endl;
    return nullptr;
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
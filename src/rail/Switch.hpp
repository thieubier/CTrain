#ifndef SWITCH_HPP
#define SWITCH_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include "Rail.hpp"

class Switch : public Rail {
public:
    Switch(const std::string& name, const sf::Vector2f& position);

    void setState(bool toRight);      // Définit l'état du switch : droite (true) ou gauche (false)
    bool getState() const;            // Récupère l'état du switch
    Rail* getNextRail();              // Obtenir le prochain rail selon l'état
    void addConnection(const sf::Vector2f& point, Rail* rail); // Ajouter une connexion
    void draw(sf::RenderWindow& window) const;                 // Dessiner le switch

private:
    bool isRight; // État du switch : droite (true) ou gauche (false)

    struct Connection {
        sf::Vector2f point; // Point de connexion sur ce rail
        Rail* rail;         // Rail associé
    };

    std::vector<Connection> connections; // Liste des connexions
};

#endif

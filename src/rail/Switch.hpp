#ifndef SWITCH_HPP
#define SWITCH_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "../rail/Rail.hpp"

class Switch : public Rail {
public:
    Switch(const std::string& name, const sf::Vector2f& position);

    void setState(bool toRight);              // Définir l'état du switch
    bool getState() const;                    // Obtenir l'état actuel
    Rail* getNextRail(const Rail* previousRail); // Obtenir le rail suivant

    void draw(sf::RenderWindow& window) const; // Dessiner le switch

private:
    bool isRight;  // État du switch : droite ou gauche
};

#endif

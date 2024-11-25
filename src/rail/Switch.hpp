#ifndef SWITCH_HPP
#define SWITCH_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Rail.hpp"

class Switch : public Rail { // Héritage public de Rail
public:
    std::vector<Rail*> connectedRails; // Liste des rails connectés
    int activeIndex; // Index du rail actif

    Switch(std::string name, const sf::Vector2f& position);

    void addConnection(Rail* rail); // Ajouter un rail au switch
    void activateNextRail();        // Change le rail actif
    Rail* getActiveRail() const;    // Retourne le rail actif
    void draw(sf::RenderWindow& window) const override;
};

#endif // SWITCH_HPP

#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <SFML/Graphics.hpp>
#include "../rail/Switch.hpp"

class Cursor {
public:
    Cursor();

    void setPosition(const sf::Vector2f& position); // Met à jour la position
    void draw(sf::RenderWindow& window) const;      // Affiche le curseur

private:
    sf::CircleShape shape; // Forme visuelle du curseur
};

#endif // CURSOR_HPP

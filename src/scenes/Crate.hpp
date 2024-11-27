#ifndef CRATE_HPP
#define CRATE_HPP

#include <SFML/Graphics.hpp>

class Crate {
public:
    Crate(const sf::Vector2f& position, const std::string& texturePath);

    void draw(sf::RenderWindow& window) const;    // Dessiner la caisse
    sf::Vector2f getPosition() const;            // Obtenir la position de la caisse
    bool checkCollision(const sf::Vector2f& trainPosition, float trainRadius) const; // Vérifier collision

private:
    sf::Vector2f position;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif

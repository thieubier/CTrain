#include "Crate.hpp"
#include <stdexcept>
#include <cmath>

Crate::Crate(const sf::Vector2f& position, const std::string& texturePath)
    : position(position) {
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Erreur : Impossible de charger la texture " + texturePath);
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(0.2f, 0.2f); // Taille réduite
}

void Crate::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::Vector2f Crate::getPosition() const {
    return position;
}

bool Crate::checkCollision(const sf::Vector2f& trainPosition, float trainRadius) const {
    float distance = std::sqrt(std::pow(position.x - trainPosition.x, 2) + std::pow(position.y - trainPosition.y, 2));
    return distance < trainRadius; // Collision si la distance est inférieure au rayon
}

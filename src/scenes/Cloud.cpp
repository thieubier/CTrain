#include "Cloud.hpp"

Cloud::Cloud(const sf::Texture& texture, const sf::Vector2f& startPosition) {
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);
    sprite.setScale(0.3f, 0.3f); // Ajuste la taille des nuages
    sprite.setColor(sf::Color(255, 255, 255, 200)); // Ajoute une transparence (128 sur 255)
}

void Cloud::move(float deltaTime) {
    sprite.move(-50.0f * deltaTime, 0); // Déplace les nuages vers la gauche
    if (sprite.getPosition().x < -sprite.getGlobalBounds().width) {
        sprite.setPosition(800.0f, sprite.getPosition().y); // Réapparaît à droite
    }
}

void Cloud::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

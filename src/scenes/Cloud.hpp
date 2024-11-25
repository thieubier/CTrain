#ifndef CLOUD_HPP
#define CLOUD_HPP

#include <SFML/Graphics.hpp>

class Cloud {
public:
    sf::Sprite sprite;

    Cloud(const sf::Texture& texture, const sf::Vector2f& startPosition);
    void move(float deltaTime);
    void draw(sf::RenderWindow& window) const;

};

#endif // CLOUD_HPP

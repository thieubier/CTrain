#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <SFML/Graphics.hpp>
#include "../rail/Rail.hpp"
#include "../rail/Switch.hpp"

class Rail;
class Switch;

class Train {
public:
    sf::CircleShape shape;
    sf::Vector2f position;
    float speed;
    Rail* currentRail;
    Rail* previousRail;
    bool movingTowardsEnd;
    sf::Texture trainTexture;
    sf::Sprite trainSprite;

    Train(Rail* startRail, bool direction, float speed);

    void move(float deltaTime);
    void switchRail(Switch* railSwitch);
    void draw(sf::RenderWindow& window);
};

#endif

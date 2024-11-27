#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <SFML/Graphics.hpp>
#include "../rail/Rail.hpp"

class Rail;

class Train {
public:
    Train(Rail* startRail, bool direction, float speed);

    void move(float deltaTime);             // Déplacer le train
    void draw(sf::RenderWindow& window);    // Dessiner le train

private:
    Rail* currentRail;
    sf::Vector2f position;
    bool movingTowardsEnd;
    float speed;

    sf::Texture trainTexture;
    sf::Sprite trainSprite;
};

#endif

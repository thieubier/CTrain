#ifndef TRAIN_HPP
#define TRAIN_HPP

#include <SFML/Graphics.hpp>
#include "../rail/Rail.hpp"
#include "../rail/Switch.hpp"

class Rail;

class Train {
public:
    Train(Rail* startRail, bool direction, float speed);

    void move(float deltaTime);             // Déplacer le train
    void draw(sf::RenderWindow& window);    // Dessiner le train

private:
    Rail* currentRail;                      // Rail actuel
    Rail* previousRail;                     // Rail précédent
    sf::Vector2f position;                  // Position actuelle du train
    bool movingTowardsEnd;                  // Direction du mouvement
    float speed;                            // Vitesse du train

    sf::Texture trainTexture;               // Texture du train
    sf::Sprite trainSprite;                 // Sprite du train
    void loadTexture();                     // Méthode pour charger la texture
};

#endif

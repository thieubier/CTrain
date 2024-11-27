#include "Train.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

// Constructeur
Train::Train(Rail* startRail, bool direction, float speed)
    : currentRail(startRail), movingTowardsEnd(direction), speed(speed) {
    position = startRail->start;

    if (!trainTexture.loadFromFile("src/files/assets/Trains etc/Train.png")) {
        throw std::runtime_error("Erreur : Impossible de charger 'train.png'");
    }
    trainSprite.setTexture(trainTexture);
    trainSprite.setScale(0.1f, 0.1f);
    trainSprite.setPosition(position);
}

// Déplace le train le long des rails
void Train::move(float deltaTime) {
    if (!currentRail) return;

    sf::Vector2f target = movingTowardsEnd ? currentRail->end : currentRail->start;
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < speed * deltaTime) {
        position = target;
        currentRail = currentRail->getConnectedRail(target);
        if (!currentRail) {
            std::cout << "Aucune connexion trouvée. Train arrêté." << std::endl;
            return;
        }
        movingTowardsEnd = (currentRail->start == target);
    } else {
        direction /= distance;
        position += direction * speed * deltaTime;
    }
    trainSprite.setPosition(position - sf::Vector2f(10.f, 10.f));
}

// Dessine le train sur la fenêtre SFML
void Train::draw(sf::RenderWindow& window) {
    window.draw(trainSprite);
}

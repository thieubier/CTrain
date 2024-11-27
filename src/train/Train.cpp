#include "Train.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

// Constructeur
Train::Train(Rail* startRail, bool direction, float speed)
    : currentRail(startRail), movingTowardsEnd(direction), speed(speed) {
    position = startRail->start;
    loadTexture(); // Charger la texture
    trainSprite.setScale(0.1f, 0.1f);
    trainSprite.setPosition(position);
}

// Déplace le train le long des rails
void Train::move(float deltaTime) {
    if (!currentRail) {
        std::cout << "Train bloqué : Aucun rail courant." << std::endl;
        return;
    }

    sf::Vector2f target = movingTowardsEnd ? currentRail->end : currentRail->start;
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < speed * deltaTime) {
        position = target;
        std::cout << "Train atteint le point : " << target.x << ", " << target.y << std::endl;

        if (auto* switchRail = dynamic_cast<Switch*>(currentRail)) {
            std::cout << "Le rail actuel est un switch : " << switchRail->toString() << std::endl;
            Rail* nextRail = switchRail->getNextRail(previousRail);
            if (!nextRail) {
                std::cout << "Aucune connexion trouvée depuis le switch." << std::endl;
                return;
            }
            previousRail = currentRail;
            currentRail = nextRail;
        } else {
            previousRail = currentRail;
            currentRail = currentRail->getConnectedRail(target);
        }

        if (!currentRail) {
            std::cout << "Aucune connexion trouvée depuis le rail courant." << std::endl;
            return;
        }

        movingTowardsEnd = (currentRail->start == target);
    } else {
        direction /= distance;
        position += direction * speed * deltaTime;
        if (direction.x < 0) {
            trainSprite.setScale(-0.1f, 0.1f); // Inverser l'image horizontalement
        } else {
            trainSprite.setScale(0.1f, 0.1f); // Image normale
        }
    }
    trainSprite.setPosition(position - sf::Vector2f(10.f, 10.f));
}

void Train::loadTexture() {
    if (!trainTexture.loadFromFile("src/files/assets/Trains etc/Train.png")) {
        throw std::runtime_error("Erreur : Impossible de charger 'Train.png'");
    }
    trainSprite.setTexture(trainTexture);
}

// Dessine le train sur la fenêtre SFML
void Train::draw(sf::RenderWindow& window) {
    window.draw(trainSprite);
}

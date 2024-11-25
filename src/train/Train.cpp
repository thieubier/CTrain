#include "Train.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>

Train::Train(Rail* startRail, bool direction, float speed)
    : currentRail(startRail), movingTowardsEnd(direction), speed(speed) {
    position = startRail->start;

    if (!trainTexture.loadFromFile("src/files/assets/Trains etc/Train.png")) {
        throw std::runtime_error("Erreur : Impossible de charger 'train.jpeg'");
    }
    trainSprite.setColor(sf::Color(255, 255, 255, 255));
    trainSprite.setTexture(trainTexture);
    trainSprite.setScale(0.1f, 0.1f);
    trainSprite.setPosition(position);
}

void Train::move(float deltaTime) {
    if (!currentRail) {
        std::cout << "Erreur : Aucun rail courant. Le train ne peut pas bouger." << std::endl;
        return;
    }

    sf::Vector2f target = movingTowardsEnd ? currentRail->end : currentRail->start;
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < speed * deltaTime) {
        position = target;

        if (movingTowardsEnd && currentRail->nextRail) {
            currentRail = currentRail->nextRail;
        } else if (!movingTowardsEnd && currentRail->previousRail) {
            currentRail = currentRail->previousRail;
        } else if (auto* switchRail = dynamic_cast<Switch*>(currentRail)) {
            currentRail = switchRail->getActiveRail();
        } else {
            std::cout << "Aucun rail suivant ou précédent disponible." << std::endl;
            currentRail = nullptr;
        }

        // Met à jour la direction du train
        const float epsilon = 0.01f;
        movingTowardsEnd = (std::abs(currentRail->start.x - position.x) < epsilon &&
                            std::abs(currentRail->start.y - position.y) < epsilon);
    } else if (distance > 0) {
        direction /= distance;
        position += direction * speed * deltaTime;
    }

    trainSprite.setPosition(position);
}

void Train::switchRail(Switch* railSwitch) {
    if (!currentRail || !railSwitch) return;

    currentRail = currentRail->nextRail;
}


void Train::draw(sf::RenderWindow& window) {
    sf::Vector2f adjustedPosition(position.x - 10.0f, position.y - 10.0f);
    trainSprite.setPosition(sf::Vector2f(adjustedPosition.x, adjustedPosition.y));
    window.draw(trainSprite);
}
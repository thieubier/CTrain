#include <SFML/Graphics.hpp>
#include "rail/Rail.hpp"
#include "rail/Switch.hpp"
#include "train/Train.hpp"
#include "scenes/Cloud.hpp"
#include "scenes/Cursor.hpp"
#include "scenes/Legend.hpp"
#include <iostream>

#include "scenes/Crate.hpp"
#include "settings/Globals.hpp"

int main() {
    sf::ContextSettings settings;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Train Simulation", sf::Style::Default, settings);

    sf::Texture cloudTexture;
    if (!cloudTexture.loadFromFile("src/files/cloud.png")) {
        std::cerr << "Erreur : Impossible de charger 'cloud.png'" << std::endl;
        return -1;
    }

    Crate crate1({500, 100}, "src/files/assets/Crates etc/CrateSmall.png");
    Crate crate2({600, 400}, "src/files/assets/Crates etc/CrateSmall.png");

    Legend legend({10.0f, 10.0f});
    legend.addEntry("Gauche", sf::Color(50, 205, 50)); // Vert pour gauche
    legend.addEntry("Droite", sf::Color(220, 20, 60)); // Rouge pour droite

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("src/files/background_detailed.jpeg")) {
        std::cerr << "Erreur : Impossible de charger 'background_detailed.jpeg'" << std::endl;
        return -1;
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    // Bouton de réinitialisation
    sf::RectangleShape resetButton(sf::Vector2f(150, 40));
    resetButton.setPosition(window.getSize().x - 160, 10);
    resetButton.setFillColor(sf::Color(100, 100, 100));
    resetButton.setOutlineColor(sf::Color::Black);
    resetButton.setOutlineThickness(2);

    sf::Font font;
    if (!font.loadFromFile("src/files/Roboto-Regular.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police 'Roboto-Regular.ttf'" << std::endl;
        return -1;
    }

    sf::Text resetButtonText("Restart", font, 20);
    resetButtonText.setPosition(resetButton.getPosition().x + 20, resetButton.getPosition().y + 5);
    resetButtonText.setFillColor(sf::Color::White);

    std::vector clouds = {
        Cloud(cloudTexture, {800, 100}),
        Cloud(cloudTexture, {1000, 200}),
        Cloud(cloudTexture, {1200, 150})
    };

    Switch railSwitch1("railSwitch1", {300, 300});
    Switch railSwitch2("railSwitch2", {700, 200});
    Switch railSwitch3("railSwitch3", {700, 400});

    // Configuration des connexions entre les rails
    rail1.connect({300, 300}, &railSwitch1);
    rail2.connect({500, 200}, &rail4);
    rail3.connect({500, 400}, &rail5);
    rail4.connect({700, 200}, &railSwitch2);
    rail5.connect({700, 400}, &railSwitch3);
    rail7.connect({700, 100}, &rail9);
    rail9.connect({300, 100}, &rail10);
    rail10.connect({100, 300}, &rail1);

    Train train(&rail1, true, 100.0f);

    // Gestion des switches et du curseur
    std::vector<Switch*> switches = {&railSwitch1, &railSwitch2, &railSwitch3};
    Cursor cursor;
    int currentSwitchIndex = 0;
    cursor.setPosition(switches[currentSwitchIndex]->start); // Position initiale du curseur

    sf::Clock clock;

    auto resetSimulation = [&]() {
        std::cout << "Réinitialisation de la simulation." << std::endl;

        // Réinitialiser le train avec recharge de la texture
        train = Train(&rail1, true, 100.0f);

        // Réinitialiser les switches
        for (auto* sw : switches) {
            sw->setState(false); // Par défaut, tous les switches à gauche
        }
    };

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Tab) {
                    currentSwitchIndex = (currentSwitchIndex + 1) % switches.size();
                    cursor.setPosition(switches[currentSwitchIndex]->start);
                }

                if (event.key.code == sf::Keyboard::Space) {
                    std::cout << "Activation du switch : " << switches[currentSwitchIndex]->toString() << std::endl;
                    switches[currentSwitchIndex]->setState(!switches[currentSwitchIndex]->getState());
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (resetButton.getGlobalBounds().contains(mousePos)) {
                        resetSimulation();
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Déplacement des nuages
        for (auto& cloud : clouds) {
            cloud.move(deltaTime);
        }

        // Déplacement du train
        train.move(deltaTime);

        // Rendu
        window.clear();
        window.draw(backgroundSprite);

        // Dessiner les rails
        rail1.draw(window);
        rail2.draw(window);
        rail3.draw(window);
        rail4.draw(window);
        rail5.draw(window);
        rail6.draw(window);
        rail7.draw(window);
        rail8.draw(window);
        rail9.draw(window);
        rail10.draw(window);

        // Dessiner les switches
        railSwitch1.draw(window);
        railSwitch2.draw(window);
        railSwitch3.draw(window);

        // Dessiner le curseur
        cursor.draw(window);
        crate1.draw(window);
        crate2.draw(window);

        // Dessiner le train
        train.draw(window);

        // Dessiner la légende
        legend.draw(window);

        // Dessiner les nuages
        for (const auto& cloud : clouds) {
            cloud.draw(window);
        }

        window.display();
    }

    return 0;
}
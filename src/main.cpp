#include <SFML/Graphics.hpp>
#include "rail/Rail.hpp"
#include "rail/Switch.hpp"
#include "train/Train.hpp"
#include <iostream>

#include "scenes/Cloud.hpp"

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8; // Pour des graphismes plus fluides
    sf::RenderWindow window(sf::VideoMode(800, 600), "Train Simulation", sf::Style::Default, settings);

    sf::Texture cloudTexture;
    if (!cloudTexture.loadFromFile("src/files/cloud.png")) {
        std::cerr << "Erreur : Impossible de charger 'cloud.png'" << std::endl;
        return -1;
    }

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

    std::vector clouds = {
        Cloud(cloudTexture, {800, 100}),
        Cloud(cloudTexture, {1000, 200}),
        Cloud(cloudTexture, {1200, 150})
    };

    Rail rail1("rail1", {100.0, 300}, {300, 300});
    Rail rail2("rail2", {300, 300}, {500, 200});
    Rail rail3("rail3", {300, 300}, {500, 400});
    Rail rail4("rail4", {500, 200}, {700, 200});
    Rail rail5("rail5", {500, 400}, {700, 400});
    Rail rail6("rail6", {700, 200}, {700, 400});
    Rail rail7("rail7", {700, 200}, {700, 100});
    Rail rail8("rail8", {700, 400}, {700, 500});

    Switch railSwitch1("railSwitch1",{300, 300});
    Switch railSwitch2("railSwitch2",{700, 200});
    Switch railSwitch3("railSwitch3",{700, 400});

    // Switch 1 : Rail 1 à Rail 2 ou Rail 3
    railSwitch1.addConnection(&rail2);
    railSwitch1.addConnection(&rail3);
    rail1.connectToNext(&railSwitch1);

    // Rail 2 : Connecté à Rail 4
    rail2.connectToNext(&rail4);
    rail2.connectToPrevious(&railSwitch1);

    // Rail 3 : Connecté à Rail 5
    rail3.connectToNext(&rail5);
    rail3.connectToPrevious(&railSwitch1);

    // Rail 4 : Connecté à Switch 2
    rail4.connectToNext(&railSwitch2);
    rail4.connectToPrevious(&rail2);

    // Rail 5 : Connecté à Switch 3
    rail5.connectToNext(&railSwitch3);
    rail5.connectToPrevious(&rail3);

    // Rail 6 : Connecté entre Switch 2 et Switch 3
    rail6.connectToNext(&railSwitch3);
    rail6.connectToPrevious(&railSwitch2);

    // Switch 2 : Rail 4 à Rail 6
    railSwitch2.addConnection(&rail4);
    railSwitch2.addConnection(&rail6);

    // Switch 3 : Rail 5 à Rail 6
    railSwitch3.addConnection(&rail5);
    railSwitch3.addConnection(&rail6);

    Train train(&rail1, true, 100.0f);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space) {
                    railSwitch1.activateNextRail();
                }
                if (event.key.code == sf::Keyboard::S) {
                    railSwitch2.activateNextRail();
                }
                if (event.key.code == sf::Keyboard::D) {
                    railSwitch3.activateNextRail();
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

        // Rendu (dessin)
        window.clear();

        // Dessiner le fond
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

        // Dessiner les switches
        railSwitch1.draw(window);
        railSwitch2.draw(window);
        railSwitch3.draw(window);

        // Dessiner le train
        train.draw(window);

        // Dessiner les nuages
        for (const auto& cloud : clouds) {
            cloud.draw(window);
        }

        window.display();
    }
    return 0;
}

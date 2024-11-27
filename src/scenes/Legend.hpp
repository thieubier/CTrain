#ifndef LEGEND_HPP
#define LEGEND_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Legend {
private:
    std::vector<sf::CircleShape> circles; // Les pastilles colorées
    std::vector<sf::Text> labels;        // Les descriptions des couleurs
    sf::Font font;                       // La police pour le texte
    sf::Vector2f position;               // Position de la légende

public:
    Legend(const sf::Vector2f& pos);
    void addEntry(const std::string& label, const sf::Color& color);
    void draw(sf::RenderWindow& window) const;
};

#endif // LEGEND_HPP

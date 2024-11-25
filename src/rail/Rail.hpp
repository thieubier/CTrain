#ifndef RAIL_HPP
#define RAIL_HPP

#include <SFML/Graphics.hpp>

class Rail {
public:
    std::string name;
    sf::Vector2f start;
    sf::Vector2f end;
    sf::Vector2f position;
    Rail* nextRail;
    Rail* previousRail;

    Rail(std::string name, const sf::Vector2f& start, const sf::Vector2f& end);

    std::string toString();
    void connectToNext(Rail* rail);
    void connectToPrevious(Rail* rail);
    virtual void draw(sf::RenderWindow& window) const;
};

#endif // RAIL_HPP

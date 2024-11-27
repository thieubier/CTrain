#ifndef RAIL_HPP
#define RAIL_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Rail {
public:
    sf::Vector2f start, end; // Points de début et de fin du rail
    Rail(const std::string& name, const sf::Vector2f& start, const sf::Vector2f& end);

    virtual ~Rail() = default; // Ajoute un destructeur virtuel

    const std::string& toString() const; // Nom du rail
    void connect(const sf::Vector2f& point, Rail* rail); // Ajouter une connexion
    Rail* getConnectedRail(const sf::Vector2f& point);   // Obtenir le rail connecté à un point
    virtual void draw(sf::RenderWindow& window) const;   // Dessiner le rail

protected:
    std::string name;

private:
    struct Connection {
        sf::Vector2f point;
        Rail* rail;
    };

    std::vector<Connection> connections; // Connexions à d'autres rails
};

#endif

#pragma once
#include <SFML/Graphics.hpp>

class fruit {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    float fallSpeed;
    bool falling;
    sf::Time lifespan;
    sf::Clock lifespanClock;
    void spawn();
public:
    fruit();
    void reset();
    void update();
    void draw(sf::RenderWindow& window) const;
    float getX() const { return position.x; }
    float getY() const { return position.y; }
    float getRadius() const { return sprite.getGlobalBounds().width / 3.0f; }
    sf::FloatRect getBounds() const; 
    bool is_falling() const;
    sf::Vector2f getPosition() const
    {
        return sprite.getPosition();
    }
};


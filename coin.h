#pragma once
#include <SFML/Graphics.hpp>



class Coin {

private:

    
    sf::Sprite sprite;
    sf::Vector2f position;
    sf::Texture texture;
    sf::Clock lifespanClock;
    sf::Time lifespan; // Adjust as needed
    const float fallSpeed;
    sf::Clock onGroundClock;
    bool isOnGround;
    float groundLevel;
    // private function to handle the coin's behavior when on the ground
    void handleOnGround();
    bool collected;  // Add this member variable to track whether the coin is collected


public:


    Coin();
    void collect();
    sf::FloatRect getBounds() const;
    bool isCollected() const;
    void reset();
    void spawn();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    bool isCollected(const sf::FloatRect& playerBounds);
    sf::Vector2f getPosition() const;

};


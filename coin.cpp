
#include "Coin.h"
#include<iostream>

Coin::Coin() : collected(false), fallSpeed(0.5f), isOnGround(false)
{
    if (!texture.loadFromFile("assets/images/gem.png"))
    {
        std::cerr << "Failed to load coin texture!" << std::endl;
    }
    else {
        std::cerr << "coin is loaded" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(1.0f, 1.0f);

    // Set initial position to a random x-coordinate and above the window
    position.x = static_cast<float>(rand() % 800);
    position.y = -50.0f;
    sprite.setPosition(position);

    //  coin properties
    lifespanClock.restart();
    lifespan = sf::seconds(3.0f);  
}

void Coin::update(sf::RenderWindow& window)
{
    if (!collected)
    {
        // If not collected, let the coin fall
        position.y += fallSpeed;
        sprite.setPosition(position);

        // Check if the coin reached the ground
        if (position.y >= groundLevel - sprite.getGlobalBounds().height / 2.0f)
        {
            isOnGround = true;
            handleOnGround();
        }

        // Check if the coin's lifespan has expired
        if (lifespanClock.getElapsedTime() > lifespan)
        {
            collected = true;
        }
    }
}

void Coin::collect() {
    collected = true;
}

sf::Vector2f Coin::getPosition() const {
    return sprite.getPosition();
}
void Coin::spawn()
{
    // Randomly choose a side of the window to spawn the coin
    float randomX = static_cast<float>(rand() % 800);  // Adjust as needed
    position = sf::Vector2f(randomX, 0.0f);

     
    collected = false;  
}

void Coin::draw(sf::RenderWindow& window) const
{
    
    window.draw(sprite);
}

sf::FloatRect Coin::getBounds() const {
    return sprite.getGlobalBounds();
}

bool Coin::isCollected() const {
    return collected;
}

void Coin::reset()
{
    collected = false;
    position.x = static_cast<float>(rand() % 800);
    position.y = -50.0f;
    sprite.setPosition(position);
    lifespanClock.restart();
    isOnGround = false;
}

void Coin::handleOnGround()
{
    if (isOnGround)
    {
       
        sf::Time timeOnGround = lifespanClock.getElapsedTime();
        if (timeOnGround > sf::seconds(2.0f)) // Adjust the duration the coin stays on the ground
        {
            // Reset the coin's position above the window
            position.x = static_cast<float>(rand() % 800);
            position.y = -50.0f;
            sprite.setPosition(position);

            // Restart the clock
            lifespanClock.restart();
            isOnGround = false; // Reset the on ground flag
        }
    }
}

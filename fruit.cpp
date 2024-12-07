#include "Fruit.h"
#include <SFML/Graphics.hpp>
#include<iostream>

fruit::fruit() : falling(true), fallSpeed(1.0f)
{
    // fruit image load
    if (!texture.loadFromFile("assets/images/ff.png"))
    {
        std::cerr << "Failed to load fruit texture!" << std::endl;
    }
    else {
        std::cerr << "fruit loading" << std::endl;
    }

    // texture is called and scale is adjusted

    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);

    //initial position of fruit is being randomly set in x-coordinate and above the window
    position.x = static_cast<float>(rand() % 800);
    position.y = -sprite.getGlobalBounds().height;  //the initial y-coordinate

    sprite.setPosition(position);

    // fruit lifesppan adjusted
    lifespanClock.restart();
    lifespan = sf::seconds(3.0f);
}

void fruit::update()
{
    if (falling)
    {
        position.y += fallSpeed;
        sprite.setPosition(position);

        // it check if the fruit is below the window
        if (position.y > 600.0f)
        {
            falling = false;
            spawn();  // respawn a new fruit
        }
    }
}

void fruit::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

bool fruit::is_falling() const
{
    return falling;
}

sf::FloatRect fruit::getBounds() const
{
    return sprite.getGlobalBounds();
}

void fruit::spawn()
{
    // to randomly choose a side of the window to spawn the fruit
    float randomX = static_cast<float>(rand() % 800);  // Adjust as needed
    position = sf::Vector2f(randomX, 0.0f);

    fallSpeed = 1.0f;  // adjust fall speed as needed
    falling = true;
}

void fruit::reset()
{
    // re-initializing of the fruit properties to their initial state
    falling = false;
    fallSpeed = 1.0f;

    if (!texture.loadFromFile("assets/images/ff.png"))
    {
        std::cerr << "Failed to load fruit texture!" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setScale(1.0f, 1.0f);

    position.x = static_cast<float>(rand() % 800);
    position.y = -50.0f;
    sprite.setPosition(position);

    lifespanClock.restart();
    lifespan = sf::seconds(3.0f);
}
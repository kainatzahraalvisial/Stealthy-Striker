#pragma
#include "Game.h"
#include "GameOverScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include<fstream>
#include<cmath>

using namespace sf;

Game::Game(sf::RenderWindow& window) : window(window),player(), score(0), timeLimit(sf::seconds(120.0f)), currentTime(sf::Time::Zero)
{
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
    }

    gameState = GameState::MainMenu;

    if (!skyTexture.loadFromFile("assets/images/s.png"))
    {
        std::cerr << "Failed to load sky texture!" << std::endl;
    }
   

    if (!groundTexture.loadFromFile("assets/images/g.png"))
    {
        std::cerr << "Failed to load ground texture!" << std::endl;
    }
   
    // set up text for score
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(10, 10);

    // set up text for time
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setPosition(200, 10);

    // set up sky sprite
    skySprite.setTexture(skyTexture);
    skySprite.setScale(2.0f, 2.0f);


    // set up ground sprite
    groundSprite.setTexture(groundTexture);
    groundSprite.setScale(2.0f, 2.0f);
    groundSprite.setPosition(0, player.getGroundLevel());

    
}

void Game::DrawUI()
{
    //GAME OVER TEXT
    if (player.getBounds().intersects(fruit.getBounds()) && fruit.is_falling())
    {
        window.draw(this->gameOverText);
    }
}


void Game::handleInput(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::K)
            {
                collectCoin();  // Calling a function to handle coin collection
            }
        }
    }
}

//  a new function to handle coin collection
void Game::collectCoin()
{
    if (coin.getBounds().intersects(player.getBounds()) && coin.isCollected() == false)
    {
        // checking for collision and collect the coin
        std::cout << "Coin collected! Score +20" << std::endl;
        score += 10;
        coin.collect();  // mark the coin as collected
    }
}

void Game::updateScore()
{
    
    scoreText.setString("Score: " + std::to_string(score));
}

void Game::updateTime()
{
    
   /* currentTime += gameclock.restart();

    if (currentTime >= timeLimit)
    {
        // game over logic (display game over screen, reset game)
        std::cout << "Game Over! Final Score: " << score << std::endl;
       
    }

    timeText.setString("Time: " + std::to_string(currentTime.asSeconds()) + "s / " + std::to_string(timeLimit.asSeconds()) + "s");*/
}

// Update function for the in-game state
void Game::updateInGame(sf::RenderWindow& window)
{
    player.update(window);
    fruit.update();
    coin.update(window);
    updateScore();
    updateTime();

    // Check for collisions and game over condition
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::K) &&
        coin.getBounds().intersects(player.getBounds()))
    {
        // Increase the score
        std::cout << "Coin collected! Score +10" << std::endl;
        score += 10;


        //WRITING THE SCORES TO THE BINARY FILE
        std::ofstream binaryFile("score_data.dat", std::ios::binary | std::ios::trunc);
        if (binaryFile.is_open())
        {
            // Write the data to the binary file
            binaryFile.write(reinterpret_cast<const char*>(&this->score), sizeof(this->score));

            // Check for errors during writing
            if (!binaryFile)
            {
                std::cerr << "Error writing to binary file!" << std::endl;
            }

            // Close the binary file
            binaryFile.close();
        }
        else
        {
            // Handle file opening error
            std::cerr << "Error opening binary file!" << std::endl;
        }

        // Reset the collected coin and spawn a new one
        coin.reset();
        coin.spawn();
    }

    if (std::sqrt(std::pow(player.getX() - fruit.getX(), 2) + std::pow(player.getY() - fruit.getY(), 2)) < player.getRadius() + fruit.getRadius() && fruit.is_falling())
    {
        // Game over logic when the player collides with a falling fruit
        std::cout << "Game Over! Player collided with a fruit!" << std::endl;

        // Set player status to "dead" or perform any other game over actions
        player.setAlive(false);

        gameState = GameState::GameOver;
    }
}


void Game::handleGameOverState(sf::RenderWindow& window, GameOverScreen& gameOverScreen)
{
    std::cout << "Entering handleGameOverState" << std::endl;

    // Handle mouse clicks for game over screen
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            gameOverScreen.handleGameOver(window);
            if (gameOverScreen.shouldRestart())
            {
                player.resetPosition();
                coin.reset();
                gameState = GameState::InGame;
            }
            else if (gameOverScreen.shouldGoToMainMenu())
            {
                window.close();
            }
        }
    }

    // Draw the game entities
    window.clear();
    window.draw(skySprite);
    window.draw(groundSprite);
    player.draw(window);
    fruit.draw(window);
    coin.draw(window);
    window.draw(scoreText);
    window.draw(timeText);

    // Display the window
    window.display();
}



bool Game::startGame(sf::RenderWindow& window)
{
    player.resetPosition();
    coin.reset();
    gameState = GameState::InGame;

    GameOverScreen gameOverScreen(window, score, gameClock, player, coin, fruit, currentTime, gameState);

    // Main game loop
    while (window.isOpen())
    {
        handleInput(window);

        if (gameState == GameState::InGame)
        {
            updateInGame(window);
        }
        else if (gameState == GameState::GameOver)
        {
            handleGameOverState(window, gameOverScreen);
        }

        // Draw the game entities outside the if-else block
        window.clear();
        window.draw(skySprite);
        window.draw(groundSprite);
        player.draw(window);
        fruit.draw(window);
        coin.draw(window);
        window.draw(scoreText);
        window.draw(timeText);

        // Display the window
        window.display();
    }
    return true;
}

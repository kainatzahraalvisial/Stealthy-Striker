#pragma
#include<iostream>
#include <SFML/Graphics.hpp>
#include "GameOverScreen.h"


GameOverScreen::GameOverScreen(sf::RenderWindow& window, int& score, sf::Clock& gameClock, player& Player, Coin& coin, fruit& Fruit, sf::Time& currentTime, GameState& gameState)
    : window(window), score(score), gameClock(gameClock), gameclock(gameClock), Player(Player), coin(coin), Fruit(Fruit), currentTime(currentTime), gameState(gameState)
{
    // Constructor implementation goes here
    // ...
}

void GameOverScreen::handleGameOver(sf::RenderWindow& window)
{
    // Load font and textures
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf"))
    {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    if (!restartButtonTexture.loadFromFile("assets/images/RM.png") ||
        !mainMenuButtonTexture.loadFromFile("assets/images/pm.png"))
    {
        // Handle error loading image
        std::cerr << "Error loading image." << std::endl;
        return;
    }

    restartButton.setTexture(restartButtonTexture);
    mainMenuButton.setTexture(mainMenuButtonTexture);

    restartButton.setPosition(400 - restartButton.getLocalBounds().width / 2, 400);
    mainMenuButton.setPosition(400 - mainMenuButton.getLocalBounds().width / 2, 500);

    sf::Text restartText("Restart Game", font, 15);
    sf::Text mainMenuText("Main Menu", font, 15);

    restartText.setPosition(400 - restartText.getLocalBounds().width / 2, 407);
    mainMenuText.setPosition(400 - mainMenuText.getLocalBounds().width / 2, 507);

    sf::Text gameOverText("Game Over!", font, 26);
    sf::Text finalScoreText("Final Score: " + std::to_string(score), font, 15);

    gameOverText.setPosition(400 - gameOverText.getLocalBounds().width / 2, 185);
    finalScoreText.setPosition(400 - finalScoreText.getLocalBounds().width / 2, 257);

    // Create a new window for the game over screen
    sf::RenderWindow gameOverWindow(sf::VideoMode(800, 600), "Game Over");
    gameOverWindow.setFramerateLimit(60);


    std::cout << "Restart Button Position: (" << restartButton.getPosition().x << ", " << restartButton.getPosition().y << ")\n";
    std::cout << "MainMenu Button Position: (" << mainMenuButton.getPosition().x << ", " << mainMenuButton.getPosition().y << ")\n";
    std::cout << "Restart Button Size: (" << restartButton.getLocalBounds().width << ", " << restartButton.getLocalBounds().height << ")\n";
    std::cout << "MainMenu Button Size: (" << mainMenuButton.getLocalBounds().width << ", " << mainMenuButton.getLocalBounds().height << ")\n";

    // Continue rendering the game over screen until the window is closed
    while (gameOverWindow.isOpen())
    {
        sf::Event event;
        while (gameOverWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gameOverWindow.close();
                window.close(); // Close the main game window when the game over window is closed
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(gameOverWindow);

                if (restartButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    // Restart button clicked
                    resetGame();
                    gameState = GameState::InGame;
                    gameOverWindow.close();
                }
                else if (mainMenuButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
                {
                    // Main menu button clicked
                    gameState = GameState::MainMenu;
                    gameOverWindow.close();
                }
            }
        }

        // Clear the game over window
        gameOverWindow.clear();

        // Draw game entities
        gameOverWindow.draw(gameOverText);
        gameOverWindow.draw(finalScoreText);
        gameOverWindow.draw(restartButton);
        gameOverWindow.draw(mainMenuButton);
        gameOverWindow.draw(restartText);
        gameOverWindow.draw(mainMenuText);

        // Display the game over window
        gameOverWindow.display();
    }
}

void GameOverScreen::draw(sf::RenderWindow& window)
{
    std::cout << "Drawing GameOverScreen" << std::endl;
    // Draw messages and buttons
    window.draw(gameOverMsg);
    window.draw(finalScoreMsg);
    window.draw(restartButton);
    window.draw(mainMenuButton);

    // Display the window content
    window.display();
}

bool GameOverScreen::shouldRestart() const
{
    return restartClicked;
}

bool GameOverScreen::shouldGoToMainMenu() const
{
    // Implement the logic for going back to the main menu
    // Similar to shouldRestart(), return true if a certain condition is met
    // For simplicity, let's assume you have a member variable called goToMainMenuClicked
    return goToMainMenuClicked;
}

bool GameOverScreen::showGameOverScreen()
{  
    handleGameOver(window);
    // handle mouse clicks
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            handleGameOverMouseClicks(event, window);
            break;
        default:
            break;
        }
    }
    return false;
}

void GameOverScreen::resetGame()
{
    Player.resetPosition();
    coin.reset();
    Fruit.reset();
    score = 0;
    currentTime = sf::Time::Zero;
    gameclock.restart();
}

void GameOverScreen::handleGameOverMouseClicks(const sf::Event& event, sf::RenderWindow& window)
{

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    // Check if the mouse click is within the bounds of the "Restart Game" button
    if (restartButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        // Restart the game
        resetGame();
        gameState = GameState::InGame;
    }
    // Check if the mouse click is within the bounds of the "Main Menu" button
    else if (mainMenuButton.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        // Return to the main menu
        gameState = GameState::MainMenu;
    }
}
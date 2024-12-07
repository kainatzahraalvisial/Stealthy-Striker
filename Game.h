#pragma once
#include "Enum.h"
#include"SFML/Graphics.hpp"
#include "player.h"
#include "fruit.h"
#include "coin.h"
#include<fstream>
class GameOverScreen;  // Forward declaration


class Game {

private:
    player player;
    fruit fruit;
    Coin coin;
    GameOverScreen gameOverScreen(sf::RenderWindow& window);
    sf::RenderWindow& window;
    GameState gameState;

    int score;
    
    sf::Time currentTime;
    sf::Time timeLimit;
    sf::Font font;
    sf::Text scoreText;
    sf::Text timeText;
    sf::Texture skyTexture;
    sf::Sprite skySprite;
    sf::Texture groundTexture;
    sf::Sprite groundSprite;
    sf::Texture backgroundTexture;
    sf::Sprite restartButton;
    sf::Sprite mainMenuButton;
     sf::Clock gameclock;
     sf::Clock gameClock;

     sf::Text restartText;
     sf::Text mainMenuText;
     sf::Text gameOverText;
     sf::Text finalScoreText;

    void collectCoin();
    void handleInput(sf::RenderWindow& window);
    void updateScore();
    void updateTime();
    bool gameOver = false; // Flag to track if the game is over
    bool gameRestarted = false;
  
public:

    bool startGame(sf::RenderWindow& window);
    Game(sf::RenderWindow& window);
    void DrawUI();
    void updateInGame(sf::RenderWindow& window);
    void handleGameOverState(sf::RenderWindow& window, GameOverScreen& gameOverScreen);
}; 

#pragma once
#include "Enum.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Coin.h"
#include "Fruit.h"

class Game;  // Forward declaration


class GameOverScreen
{
public:
    GameOverScreen(sf::RenderWindow& window, int& score, sf::Clock& gameClock, player& Player, Coin& coin, fruit& Fruit, sf::Time& currentTime, GameState& gameState);

    void draw(sf::RenderWindow& window);
    bool showGameOverScreen();
    void resetGame();
    void handleGameOverMouseClicks(const sf::Event& event, sf::RenderWindow& window);
    bool shouldRestart() const;
    bool shouldGoToMainMenu() const;
    void handleGameOver(sf::RenderWindow& window);

private:
    sf::RenderWindow& window;
    int& score;
    bool restartClicked = false;
    bool goToMainMenuClicked = false;
    sf::Clock gameClock;
    sf::Clock& gameclock;
    player& Player;
    Coin& coin;
    fruit& Fruit;
    sf::Time& currentTime;
    GameState& gameState;
    sf::Texture restartButtonTexture;
    sf::Texture mainMenuButtonTexture;
    sf::Texture gameOverMsgTexture;
    sf::Texture finalScoreMsgTexture;

    sf::Sprite restartButton;
    sf::Sprite mainMenuButton;
    sf::Sprite gameOverMsg;
    sf::Sprite finalScoreMsg;

    sf::Text restartText;
    sf::Text mainMenuText;
    sf::Text gameOverText;
    sf::Text finalScoreText;

    sf::Font font;

    // ... other members ...
};
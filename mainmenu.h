#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>



class Game;

class mainmenu
{
public:


    enum class GameState
    {
        MainMenu,
        InGame,
        GameOver
    };

    GameState getGameState();  // Add this method
    void setGameState(GameState state);

    mainmenu(sf::RenderWindow& window);

    void handle_input();
    void update();
    void render();
    const sf::Text& getGameNameText() const { return gameNameText; }
    const sf::Text& getStartGameText() const { return start_gametext; }
    const sf::Text& getCreditsText() const { return creditstext; }
    const sf::Text& getExitText() const { return exittext; }
private:
    sf::RenderWindow& window;

    sf::Text gameNameText;
    sf::Text start_gametext;
    sf::Text leader_boardtext;
    sf::Text creditstext;
    sf::Text exittext;
    sf::Font font;
    sf::Font f;
    Game* game;
    

    GameState gameState;

    void credits();
    void showPopup(const std::string& title, const std::string& content);
    void start_game();


};

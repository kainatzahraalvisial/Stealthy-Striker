#include"Game.h"
#include"mainmenu.h"
#include <SFML/Window/Event.hpp>

mainmenu::mainmenu(sf::RenderWindow& window) : window(window)
{
    // font loading
    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf"))
    {
        // error...
    }


    // text object for game name
    gameNameText.setFont(font);
    gameNameText.setString("Stealthy Striker");
    gameNameText.setCharacterSize(36);  // Increase the character size for a larger font
    gameNameText.setPosition(200, 150);

    // text objects for start game
    start_gametext.setFont(font);
    start_gametext.setString("Start Game");
    start_gametext.setCharacterSize(24);
    start_gametext.setPosition(200, 200);

    

    // text objects for credits
    creditstext.setFont(font);
    creditstext.setString("Credit");
    creditstext.setCharacterSize(24);
    creditstext.setPosition(200, 300);

    // text objects for exit
    exittext.setFont(font);
    exittext.setString("Exit");
    exittext.setCharacterSize(24);
    exittext.setPosition(200, 400);

}

void mainmenu::handle_input()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Check if the mouse click is within the bounds of the "Start Game" text
            sf::FloatRect startGameBounds = start_gametext.getGlobalBounds();
            if (startGameBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                start_game();
            }

          

            // it check for "credit" text
            sf::FloatRect creditsBounds = creditstext.getGlobalBounds();
            if (creditsBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
            {

                credits();
            }

            // it check for "Exit" text
            sf::FloatRect exitBounds = exittext.getGlobalBounds();
            if (exitBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
            {

                window.close();
            }
        }
    }

}


mainmenu::GameState mainmenu::getGameState()  // Implement this method
{
    return gameState;
}

void mainmenu::setGameState(GameState state)  // Implement this method
{
    gameState = state;
}

void mainmenu::update()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::FloatRect startGameBounds = start_gametext.getGlobalBounds();
    sf::FloatRect creditsBounds = creditstext.getGlobalBounds();
    sf::FloatRect exitBounds = exittext.getGlobalBounds();

    if (startGameBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
    {
        start_gametext.setFillColor(sf::Color::Yellow);
        creditstext.setFillColor(sf::Color::Blue);
        exittext.setFillColor(sf::Color::Green);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            gameState = GameState::InGame;
        }
    }
    else
    {
        start_gametext.setFillColor(sf::Color::White);
        creditstext.setFillColor(sf::Color::White);
        exittext.setFillColor(sf::Color::White);
    }
}


void mainmenu::render()
{
    window.clear();
    window.draw(gameNameText);
    window.draw(start_gametext);
    window.draw(creditstext);
    window.draw(exittext);
    window.display();


}

void mainmenu::showPopup(const std::string& title, const std::string& content)
{
    sf::RenderWindow popupWindow(sf::VideoMode(400, 200), title);
    sf::Font font;

    if (!font.loadFromFile("assets/fonts/ThaleahFat.ttf"))
    {
        // Handle font loading error
    }

    sf::Text popupText(content, font, 20);
    popupText.setPosition(20, 50);
    popupText.setFillColor(sf::Color::White);

    while (popupWindow.isOpen())
    {
        sf::Event event;
        while (popupWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                popupWindow.close();
        }

        popupWindow.clear(sf::Color(50, 50, 50)); // Dark background color

        // Draw your popup content
        popupWindow.draw(popupText);

        popupWindow.display();
    }
}

void mainmenu::credits()
{
    // Implementation for handling the credits
    std::string message = "Stealthy Striker\n\nCreated by: me\nVersion: 1.0";

    // Show the custom popup window
    showPopup("Game Credits", message);
}

void mainmenu::start_game() 
{
    // Create an instance of the Game class
    Game game(window);

    // Call the startGame function of the Game class
    game.startGame(window);

    gameState = GameState::MainMenu;

}

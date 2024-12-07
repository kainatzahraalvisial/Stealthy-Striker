#include "Game.h"
#include "mainmenu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Stealthy Striker!");
    mainmenu Mainmenu(window);
    Game game(window);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Mainmenu.handle_input();
        Mainmenu.update();

        if (Mainmenu.getGameState() == mainmenu::GameState::InGame)
        {
            // Handle input, update, and rendering for the in-game state
            if (!game.startGame(window))
            {
                // Game over, return to the main menu
                Mainmenu.setGameState(mainmenu::GameState::MainMenu);
            }
        }
        else
        {
            // Rendering the main menu when not in the in-game state
            Mainmenu.render();
        }
    }

    return 0;
}

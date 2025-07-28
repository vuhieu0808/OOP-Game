#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "menu/menu.h"
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    Player player;
    Menu menu;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Map gameMap;
    Camera camera;

    void updateGame(float deltaTime);
    void renderGame();
    void checkWinCondition();

public:
    Game();

    void run();
};

#endif // GAME_H
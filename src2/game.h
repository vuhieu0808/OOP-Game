#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <SFML/Graphics.hpp>

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    Player player;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Map gameMap;
    Camera camera;

public:
    Game();

    void run();
};

#endif // GAME_H
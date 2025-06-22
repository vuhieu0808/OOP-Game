#pragma once

#include <SFML/Graphics.hpp>
#include "map.h"
#include "camera.h"
#include "player.h"

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;

class Player;

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    Map gameMap;
    Player player;
    Camera camera;  // Thêm camera
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

public:
    Game();
    void run();
};
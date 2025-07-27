#pragma once

#include <SFML/Graphics.hpp>
#include "map.h"
#include "camera.h"
#include "player.h"
#include "menu.h"
#include "gameObserver.h"

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

class Player;

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;
    Map gameMap;
    Player player;
    Camera camera;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    Menu menu;

    std::vector<IGameObserver*> observers;

public:
    Game();
    void run();

    void addObserver(IGameObserver* observer);
    void removeObserver(IGameObserver* observer);
    void notifyObservers(GameEvent event);
};
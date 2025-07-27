#include "game.h"
#include "animationSystem.h"
#include <iostream>

Game::Game() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Vuhieu King"),
    player("media/player/idle.png", gameMap), // Khởi tạo player với vị trí ban đầu
    camera(sf::Vector2f(576, 270))
{
    window.setFramerateLimit(60);
    
    // Tải texture cho nền
    if (!backgroundTexture.loadFromFile("media/background.jpg")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!gameMap.loadFromFile("media/map/map2.tmx")) {
        std::cerr << "Failed to load map!" << std::endl;
        return;
    }
    player.setPosition(gameMap.getPlayerStartPos());
    camera.setBounds(sf::FloatRect(0, 0, gameMap.getMapSize().x, gameMap.getMapSize().y));
}

void Game::run() {
    // Observer pattern
    AnimationSystem animationSystem(&player);
    player.addObserver(&animationSystem);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Xử lý input và cập nhật game
        player.handleInput();
        player.update(deltaTime);
        camera.update(player.getPosition());

        // Vẽ game
        window.clear();
        
        // Vẽ nền
        sf::View defaultView = window.getDefaultView();
        window.setView(defaultView);
        window.draw(backgroundSprite);
        
        // Vẽ game world
        camera.applyTo(window);
        gameMap.draw(window);
        player.draw(window);
        
        window.display();
    }
}
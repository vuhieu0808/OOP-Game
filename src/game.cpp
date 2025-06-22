#include "game.h"
#include <iostream>

Game::Game() : 
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Vuhieu King"),
    camera(sf::Vector2f(480, 480)),
    player(sf::Vector2f(100.f, 100.f), camera, gameMap)
{
    window.setFramerateLimit(60);
    
    if (!gameMap.loadFromFile("level1.map")) {
        std::cerr << "Failed to load map!" << std::endl;
    }

    backgroundTexture.loadFromFile("media/background.jpg");
    backgroundSprite.setTexture(backgroundTexture);
    
    // Thiết lập bounds cho camera = kích thước map
    camera.setBounds(sf::FloatRect(0, 0, gameMap.getMapSize().x, gameMap.getMapSize().y));
    

    // Đặt vị trí ban đầu cho player từ map
    player.setPosition(gameMap.getPlayerStartPos());
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        
        // Cập nhật player
        player.handleInput();
        player.update(deltaTime);
        
        // Cập nhật camera (screen-by-screen)
        camera.update(player.getPosition());
        
        window.clear();
        
        // Vẽ background (dùng default view)
        sf::View defaultView = window.getDefaultView();
        window.setView(defaultView);
        window.draw(backgroundSprite);
        
        // Áp dụng camera và vẽ game world
        camera.applyTo(window);
        gameMap.draw(window);
        player.draw(window);
        
        window.display();
    }
}
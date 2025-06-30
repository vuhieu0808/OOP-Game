#include "game.h"
#include <iostream>

Game::Game() : 
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Vuhieu King"),
    camera(sf::Vector2f(720, 720)),
    player(sf::Vector2f(100.f, 100.f), camera, gameMap),
    menu(window)  // Khởi tạo menu
{
    window.setFramerateLimit(60);
    
    player.loadTextures("media/player/idle.png", 
                        "media/player/walk.png", 
                        "media/player/walk.png", 
                        "media/player/charge.png");

    backgroundTexture.loadFromFile("media/background.jpg");
    backgroundSprite.setTexture(backgroundTexture);
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) 
                window.close();
            
            // Xử lý phím ESC để tạm dừng/tiếp tục
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (menu.getCurrentState() == MenuState::Playing) {
                    menu.setState(MenuState::Pause);
                }
                else if (menu.getCurrentState() == MenuState::Pause) {
                    menu.setState(MenuState::Playing);
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Nếu game đang tạm dừng
        if (menu.getCurrentState() == MenuState::Pause) {
            // Vẽ game trước
            window.clear();
            
            // Vẽ background
            sf::View defaultView = window.getDefaultView();
            window.setView(defaultView);
            window.draw(backgroundSprite);
            
            // Vẽ game world
            camera.applyTo(window);
            gameMap.draw(window);
            player.draw(window);

            menu.update();
            
            // Rồi mới vẽ menu pause lên trên
            window.setView(defaultView);
            menu.render();
            
            window.display();
            continue;
        }


        // Nếu đang ở menu chính hoặc settings
        if (menu.getCurrentState() != MenuState::Playing) {
            menu.update();
            menu.render();
            
            if (menu.getCurrentState() == MenuState::Playing) {
                if (!gameMap.loadFromFile(menu.getSelectedMap())) {
                    std::cerr << "Failed to load map!" << std::endl;
                    menu.setState(MenuState::Start);
                    continue;
                }
                camera.setBounds(sf::FloatRect(0, 0, gameMap.getMapSize().x, gameMap.getMapSize().y));
                player.setPosition(gameMap.getPlayerStartPos());
            }
            continue;
        }

        // Cập nhật game khi đang chơi
        player.handleInput();
        player.update(deltaTime);
        camera.update(player.getPosition());

        // Render game
        window.clear();
        
        // Vẽ background
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
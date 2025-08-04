#include "game.h"
#include "animationSystem.h"
#include <iostream>

Game::Game() :
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Vuhieu King"),
    player("media/player/idle.png", gameMap),
    camera(sf::Vector2f(576, 270)),
    menu(window)  // Khởi tạo menu
{
    window.setFramerateLimit(60);
    
    // Tải texture cho nền
    if (!backgroundTexture.loadFromFile("media/background.jpg")) {
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Game::run() {
    AnimationSystem animationSystem(&player);
    player.addObserver(&animationSystem);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            // Xử lý phím ESC để pause game
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if (menu.getCurrentState() == Menu::State::Playing) {
                    menu.changeState(Menu::State::Pause);
                }
                else if (menu.getCurrentState() == Menu::State::Pause) {
                    menu.changeState(Menu::State::Playing);
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();

        // Cập nhật trạng thái game từ menu
        auto oldState = menu.getCurrentState();

        switch (menu.getCurrentState()) {
            case Menu::State::Start:
            case Menu::State::Settings:
            case Menu::State::Pause:
            case Menu::State::Win:
                menu.handleInput();
                menu.render();
                break;
                
            case Menu::State::Playing:
                updateGame(deltaTime);
                renderGame();
                checkWinCondition();
                break;
        }

        auto newState = menu.getCurrentState();

        if (oldState == Menu::State::Start && newState == Menu::State::Playing) {
            if (!gameMap.loadFromFile(menu.getSelectedMap())) {
                std::cerr << "Failed to load map!" << std::endl;
                return;
            }
            player.setPosition(gameMap.getPlayerStartPos());
            camera.setBounds(sf::FloatRect(0, 0, gameMap.getMapSize().x, gameMap.getMapSize().y));
        }
    }
}

void Game::updateGame(float deltaTime) {
    player.handleInput();
    player.update(deltaTime);
    camera.update(player.getPosition());
}

void Game::renderGame() {
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

void Game::checkWinCondition() {
    if (player.checkWinCondition()) {
        std::cout << "You win!" << std::endl;
        menu.changeState(Menu::State::Win);
    }
}
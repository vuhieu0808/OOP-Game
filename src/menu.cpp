#include "menu.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

Menu::Menu(sf::RenderWindow& window) : window(window), currentState(MenuState::Start), selectedMapIndex(0) {
    // Load font
    if (!font.loadFromFile("media/fonts/PressStart2P-Regular.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    
    // Load background
    if (!backgroundTexture.loadFromFile("media/background_1.jpg")) {
        std::cerr << "Failed to load menu background!" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    
    // Setup menu items
    setupPauseMenu();
    setupStartMenu();
    
    // Available maps
    mapFiles = {"media/map/map2.tmx"};
    // mapFiles = {"level1.map"};
}

void Menu::setupStartMenu() {
    titleText.setString("VU HIEU KING");
    titleText.setFont(font);
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Red);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(
        window.getSize().x / 2 - titleText.getGlobalBounds().width / 2,
        100
    );
    
    startMenuItems.clear();
    
    std::vector<std::string> items = {"Start Game", "Settings", "Exit"};
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text item;
        item.setString(items[i]);
        item.setFont(font);
        item.setCharacterSize(50);
        item.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        item.setPosition(
            window.getSize().x / 2 - item.getGlobalBounds().width / 2,
            300 + i * 80
        );
        startMenuItems.push_back(item);
    }
}

void Menu::setupSettingsMenu() {
    titleText.setString("SETTINGS");
    titleText.setFont(font);
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Red);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(
        window.getSize().x / 2 - titleText.getGlobalBounds().width / 2,
        100
    );
    
    settingsMenuItems.clear();
    
    // Map selection item
    sf::Text mapText;
    mapText.setString("Map: " + mapFiles[selectedMapIndex]);
    mapText.setFont(font);
    mapText.setCharacterSize(50);
    mapText.setFillColor(sf::Color::Yellow);
    mapText.setPosition(
        window.getSize().x / 2 - mapText.getGlobalBounds().width / 2,
        300
    );
    settingsMenuItems.push_back(mapText);
    
    // Back item
    sf::Text backText;
    backText.setString("Back to Menu");
    backText.setFont(font);
    backText.setCharacterSize(50);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(
        window.getSize().x / 2 - backText.getGlobalBounds().width / 2,
        400
    );
    settingsMenuItems.push_back(backText);
}

void Menu::setupPauseMenu() {
    titleText.setString("PAUSED");
    titleText.setFont(font);
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Red);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(
        window.getSize().x / 2 - titleText.getGlobalBounds().width / 2,
        100
    );

    pauseMenuItems.clear();

    std::vector<std::string> items = {"Continue", "Back to Menu"};
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text item;
        item.setString(items[i]);
        item.setFont(font);
        item.setCharacterSize(50);
        item.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        item.setPosition(
            window.getSize().x / 2 - item.getGlobalBounds().width / 2,
            300 + i * 80
        );
        pauseMenuItems.push_back(item);
    }
}

void Menu::setupWinMenu() {
    titleText.setString("VICTORY!");
    titleText.setFont(font);
    titleText.setCharacterSize(80);
    titleText.setFillColor(sf::Color::Green);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(
        window.getSize().x / 2 - titleText.getGlobalBounds().width / 2,
        100
    );
    
    winMenuItems.clear();
    
    sf::Text backText;
    backText.setString("Back to Menu");
    backText.setFont(font);
    backText.setCharacterSize(50);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(
        window.getSize().x / 2 - backText.getGlobalBounds().width / 2,
        300
    );
    winMenuItems.push_back(backText);
}

void Menu::update() {
    if (currentState == MenuState::Start) {
        handleStartMenuInput();
    }
    else if (currentState == MenuState::Settings) {
        handleSettingsMenuInput();
    }
    else if (currentState == MenuState::Pause) { 
        handlePauseMenuInput();
    }
    else if (currentState == MenuState::Win) {
        handleWinMenuInput();
    }
}

void Menu::handleStartMenuInput() {
    // Xử lý phím mũi tên
    static bool keyReleased = true; // Biến tạm để tránh giữ phím
    
    if (keyReleased) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            keyReleased = false;
            // Tìm item đang được chọn (màu vàng)
            for (size_t i = 0; i < startMenuItems.size(); ++i) {
                if (startMenuItems[i].getFillColor() == sf::Color::Yellow) {
                    // Đổi màu item hiện tại thành trắng
                    startMenuItems[i].setFillColor(sf::Color::White);
                    
                    // Chọn item phía trên (vòng lại nếu ở đầu)
                    size_t prev = (i == 0) ? startMenuItems.size() - 1 : i - 1;
                    startMenuItems[prev].setFillColor(sf::Color::Yellow);
                    break;
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            keyReleased = false;
            for (size_t i = 0; i < startMenuItems.size(); ++i) {
                if (startMenuItems[i].getFillColor() == sf::Color::Yellow) {
                    startMenuItems[i].setFillColor(sf::Color::White);
                    
                    // Chọn item phía dưới (vòng lại nếu ở cuối)
                    size_t next = (i + 1) % startMenuItems.size();
                    startMenuItems[next].setFillColor(sf::Color::Yellow);
                    break;
                }
            }
        }
    }
    
    // Reset biến keyReleased khi nhả phím
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        keyReleased = true;
    }
    
    // Xử lý phím Enter
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        for (size_t i = 0; i < startMenuItems.size(); ++i) {
            if (startMenuItems[i].getFillColor() == sf::Color::Yellow) {
                if (i == 0) { // Start Game
                    currentState = MenuState::Playing;
                }
                else if (i == 1) { // Settings
                    currentState = MenuState::Settings;
                    setupSettingsMenu(); // Khởi tạo lại menu settings
                }
                else if (i == 2) { // Exit
                    window.close();
                }
                break;
            }
        }
        // Delay nhỏ để tránh bấm quá nhanh
        sf::sleep(sf::milliseconds(200));
    }
}

void Menu::handleSettingsMenuInput() {
    bool keyPressed = false;

    // Xử lý phím lên/xuống để chọn item
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        keyPressed = true;
        // Tìm item đang được chọn (màu vàng)
        for (size_t i = 0; i < settingsMenuItems.size(); ++i) {
            if (settingsMenuItems[i].getFillColor() == sf::Color::Yellow) {
                // Đổi màu item hiện tại thành trắng
                settingsMenuItems[i].setFillColor(sf::Color::White);
                
                // Chọn item phía trên (vòng lại nếu ở đầu)
                size_t prev = (i == 0) ? settingsMenuItems.size() - 1 : i - 1;
                settingsMenuItems[prev].setFillColor(sf::Color::Yellow);
                break;
            }
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        keyPressed = true;
        for (size_t i = 0; i < settingsMenuItems.size(); ++i) {
            if (settingsMenuItems[i].getFillColor() == sf::Color::Yellow) {
                settingsMenuItems[i].setFillColor(sf::Color::White);
                
                // Chọn item phía dưới (vòng lại nếu ở cuối)
                size_t next = (i + 1) % settingsMenuItems.size();
                settingsMenuItems[next].setFillColor(sf::Color::Yellow);
                break;
            }
        }
    }

    // Xử lý phím trái/phải khi đang chọn mục Map
    if (settingsMenuItems[0].getFillColor() == sf::Color::Yellow) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            keyPressed = true;
            selectedMapIndex = (selectedMapIndex == 0) ? mapFiles.size() - 1 : selectedMapIndex - 1;
            settingsMenuItems[0].setString("Map: " + mapFiles[selectedMapIndex]);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            keyPressed = true;
            selectedMapIndex = (selectedMapIndex + 1) % mapFiles.size();
            settingsMenuItems[0].setString("Map: " + mapFiles[selectedMapIndex]);
        }
    }

    // Xử lý phím Enter
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        keyPressed = true;
        for (size_t i = 0; i < settingsMenuItems.size(); ++i) {
            if (settingsMenuItems[i].getFillColor() == sf::Color::Yellow) {
                if (i == 1) { // Back to Menu
                    currentState = MenuState::Start;
                    setupStartMenu();
                }
                break;
            }
        }
    }

    // Thêm delay nếu có phím được nhấn
    if (keyPressed) {
        sf::sleep(sf::milliseconds(150));
    }
}

void Menu::handlePauseMenuInput() {
    static bool keyReleased = true;
    
    if (keyReleased) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            keyReleased = false;
            for (size_t i = 0; i < pauseMenuItems.size(); ++i) {
                if (pauseMenuItems[i].getFillColor() == sf::Color::Yellow) {
                    pauseMenuItems[i].setFillColor(sf::Color::White);
                    size_t prev = (i == 0) ? pauseMenuItems.size() - 1 : i - 1;
                    pauseMenuItems[prev].setFillColor(sf::Color::Yellow);
                    break;
                }
            }
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            keyReleased = false;
            for (size_t i = 0; i < pauseMenuItems.size(); ++i) {
                if (pauseMenuItems[i].getFillColor() == sf::Color::Yellow) {
                    pauseMenuItems[i].setFillColor(sf::Color::White);
                    size_t next = (i + 1) % pauseMenuItems.size();
                    pauseMenuItems[next].setFillColor(sf::Color::Yellow);
                    break;
                }
            }
        }
    }
    
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        keyReleased = true;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        for (size_t i = 0; i < pauseMenuItems.size(); ++i) {
            if (pauseMenuItems[i].getFillColor() == sf::Color::Yellow) {
                if (i == 0) { // Continue
                    currentState = MenuState::Playing;
                }
                else if (i == 1) { // Back to Menu
                    currentState = MenuState::Start;
                    setupStartMenu();
                }
                sf::sleep(sf::milliseconds(200));
                break;
            }
        }
    }
}

void Menu::handleWinMenuInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        currentState = MenuState::Start;
        setupStartMenu();
        sf::sleep(sf::milliseconds(200));
    }
}

void Menu::render() {
    // Chỉ clear window và vẽ background nếu không phải là pause menu
    if (currentState != MenuState::Pause) {
        window.clear();
        window.draw(backgroundSprite);
    }
    
    // Vẽ tiêu đề
    window.draw(titleText);
    
    // Vẽ các mục menu tương ứng
    if (currentState == MenuState::Start) {
        for (const auto& item : startMenuItems) {
            window.draw(item);
        }
    }
    else if (currentState == MenuState::Settings) {
        for (const auto& item : settingsMenuItems) {
            window.draw(item);
        }
    }
    else if (currentState == MenuState::Pause) {
        // Vẽ overlay mờ
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 150)); // Màu đen với độ trong suốt
        window.draw(overlay);
        
        // Vẽ các mục pause menu
        for (const auto& item : pauseMenuItems) {
            window.draw(item);
        }
    }
    else if (currentState == MenuState::Win) {
        for (const auto& item : winMenuItems) {
            window.draw(item);
        }
    }
    
    // Chỉ display nếu không phải là pause menu
    // (pause menu sẽ được display bởi Game::run())
    if (currentState != MenuState::Pause) {
        window.display();
    }
}

MenuState Menu::getCurrentState() const {
    return currentState;
}

std::string Menu::getSelectedMap() const {
    return mapFiles[selectedMapIndex];
}

void Menu::setState(MenuState state) {
    currentState = state;
    if (state == MenuState::Start) {
        setupStartMenu();
    }
    else if (state == MenuState::Settings) {
        setupSettingsMenu();
    }
    else if (state == MenuState::Pause) { 
        setupPauseMenu();
    }
    else if (state == MenuState::Win) {
        setupWinMenu();
    }
}

void Menu::onGameEvent(GameEvent event) {
    switch (event) {
        case GameEvent::PlayerWin:
            setState(MenuState::Win);
            break;
        case GameEvent::GamePaused:
            if (getCurrentState() == MenuState::Playing) {
                setState(MenuState::Pause);
            }
            break;
        case GameEvent::GameResumed:
            if (getCurrentState() == MenuState::Pause) {
                setState(MenuState::Playing);
            }
            break;
        default:
            break;
    }
}
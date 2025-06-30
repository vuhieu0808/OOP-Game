#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

enum class MenuState {
    Start,
    Settings,
    Playing,
    Pause
};

class Menu {
private:
    sf::RenderWindow& window;
    MenuState currentState;
    
    // Font và text
    sf::Font font;
    sf::Text titleText;
    std::vector<sf::Text> startMenuItems;
    std::vector<sf::Text> settingsMenuItems;
    std::vector<sf::Text> pauseMenuItems;
    
    // Background
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    // Map selection
    int selectedMapIndex;
    std::vector<std::string> mapFiles;
    
    void setupStartMenu();
    void setupSettingsMenu();
    void setupPauseMenu();
    void handleStartMenuInput();
    void handleSettingsMenuInput();
    void handlePauseMenuInput();

public:
    Menu(sf::RenderWindow& window);
    void update();
    void render();
    MenuState getCurrentState() const;
    std::string getSelectedMap() const;
    void setState(MenuState state);
};
#ifndef MENU_H
#define MENU_H

#include "states/base_state.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

class MenuInputHandler;

class Menu {
public:
    enum class State { Start, Settings, Pause, Win, Playing };
    
    Menu(sf::RenderWindow& window);
    
    // Main functions
    void render();
    void handleInput();
    void changeState(State newState);
    
    // State access
    State getCurrentState() const { return currentState; }
    MenuState& getCurrentStateObj() { return *currentStateObj; }
    
    // Resource access
    sf::RenderWindow& getWindow() { return window; }
    const sf::Font& getFont() const { return font; }
    const sf::Sprite& getBackground() const { return backgroundSprite; }
    MenuInputHandler& getInputHandler() { return *inputHandler; }
    
    // Get map files
    void setSelectedMap(const std::string& map) { selectedMap = map; }
    const std::string& getSelectedMap() const { return selectedMap; }

    ~Menu();

private:
    // Window and resources
    sf::RenderWindow& window;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    // State management
    State currentState;
    std::unique_ptr<MenuState> currentStateObj;
    
    // Input handling
    std::unique_ptr<MenuInputHandler> inputHandler;
    
    // Private helper
    void loadResources();

    std::string selectedMap;
};

#endif // MENU_H
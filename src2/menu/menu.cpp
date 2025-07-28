#include "menu.h"
#include "menu_input_handler.h"
#include "states/start_state.h"
#include "states/settings_state.h"
#include "states/pause_state.h"
#include "states/win_state.h"

Menu::~Menu() = default;

Menu::Menu(sf::RenderWindow& window) 
    : window(window), currentState(State::Start),
    inputHandler(std::make_unique<MenuInputHandler>()) {
    loadResources();
    changeState(State::Settings);
    selectedMap = "media/map/map1.tmx"; // Default map
    changeState(State::Start);
}

void Menu::loadResources() {
    // Load font
    if (!font.loadFromFile("media/fonts/PressStart2P-Regular.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    
    // Load background
    if (!backgroundTexture.loadFromFile("media/background_1.jpg")) {
        throw std::runtime_error("Failed to load background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);
}

void Menu::changeState(State newState) {
    currentState = newState;
    
    switch (newState) {
        case State::Start:
            currentStateObj = std::make_unique<StartState>();
            break;
        case State::Settings:
            currentStateObj = std::make_unique<SettingsState>();
            break;
        case State::Pause:
            currentStateObj = std::make_unique<PauseState>();
            break;
        case State::Win:
            currentStateObj = std::make_unique<WinState>();
            break;
        case State::Playing:
            currentStateObj.reset();
            return;
    }
    
    if (currentStateObj) currentStateObj->enter(*this);
}

void Menu::render() {
    if (!currentStateObj) return;
    currentStateObj->render(*this);
}

void Menu::handleInput() {
    if (!currentStateObj) return;
    if (auto command = inputHandler->handleInput()) {
        if (command->execute(*this)) {
            sf::sleep(sf::milliseconds(150));
        }
    }
}
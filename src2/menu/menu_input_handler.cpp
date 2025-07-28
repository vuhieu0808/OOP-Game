#include "menu_input_handler.h"
#include "commands/navigate_command.h"
#include "commands/select_command.h"

MenuInputHandler::MenuInputHandler() {
    initializeKeyBindings();
}

void MenuInputHandler::initializeKeyBindings() {
    keyBindings[sf::Keyboard::Up] = []() { return std::make_unique<NavigateUpCommand>(); };
    keyBindings[sf::Keyboard::Down] = []() { return std::make_unique<NavigateDownCommand>(); };
    keyBindings[sf::Keyboard::Left] = []() { return std::make_unique<NavigateLeftCommand>(); };
    keyBindings[sf::Keyboard::Right] = []() { return std::make_unique<NavigateRightCommand>(); };

    keyBindings[sf::Keyboard::Enter] = []() { return std::make_unique<SelectCommand>(); };
}

std::unique_ptr<MenuCommand> MenuInputHandler::handleInput() {
    for (const auto& [key, creator] : keyBindings) {
        if (sf::Keyboard::isKeyPressed(key)) {
            return creator();
        }
    }
    return nullptr;
}
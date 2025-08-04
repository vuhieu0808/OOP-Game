#ifndef MENU_INPUT_HANDLER_H
#define MENU_INPUT_HANDLER_H

#include "commands/menu_command.h"

#include <SFML/Window/Keyboard.hpp>
#include <memory>
#include <map>
#include <functional>

class MenuInputHandler {
public:
    MenuInputHandler();
    
    std::unique_ptr<MenuCommand> handleInput();
    
private:
    std::map<sf::Keyboard::Key, std::function<std::unique_ptr<MenuCommand>()>> keyBindings;
    
    void initializeKeyBindings();
};

#endif // MENU_INPUT_HANDLER_H
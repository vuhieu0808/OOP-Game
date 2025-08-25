#include "start_state.h"
#include "../menu.h"

void StartState::enter(Menu& menu) {
    title.setString("JUMP MASTER");
    title.setFont(menu.getFont());
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        menu.getWindow().getSize().x / 2 - title.getGlobalBounds().width / 2,
        100
    );
    
    menuItems.clear();
    
    std::vector<std::string> items = {"Start Game", "Settings", "Exit"};
    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text item;
        item.setString(items[i]);
        item.setFont(menu.getFont());
        item.setCharacterSize(50);
        item.setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        item.setPosition(
            menu.getWindow().getSize().x / 2 - item.getGlobalBounds().width / 2,
            300 + i * 80
        );
        menuItems.push_back(item);
    }

    currentIndex = 0;
    selectedIndex = 0;
}

void StartState::render(Menu& menu) {
    menu.getWindow().clear();
    menu.getWindow().draw(menu.getBackground());
    menu.getWindow().draw(title);
    for (const auto& item : menuItems) {
        menu.getWindow().draw(item);
    }
    menu.getWindow().display();
}

void StartState::onSelect(Menu& menu) {
    switch (currentIndex) {
        case 0: // Start Game
            menu.changeState(Menu::State::Playing);
            break;
        case 1: // Settings
            menu.changeState(Menu::State::Settings);
            break;
        case 2: // Exit
            menu.getWindow().close();
            break;
    }
}
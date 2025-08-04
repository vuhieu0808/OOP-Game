#include "win_state.h"
#include "../menu.h"

void WinState::enter(Menu& menu) {
    printf("Entering WinState\n");
    title.setString("VICTORY");
    title.setFont(menu.getFont());
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Green);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        menu.getWindow().getSize().x / 2 - title.getGlobalBounds().width / 2,
        100
    );
    
    menuItems.clear();
    
    std::vector<std::string> items = {"Main Menu"};
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

void WinState::render(Menu& menu) {
    auto defaultView = menu.getWindow().getDefaultView();
    menu.getWindow().setView(defaultView);
    menu.getWindow().draw(title);
    for (const auto& item : menuItems) {
        menu.getWindow().draw(item);
    }
    
    menu.getWindow().display();
}

void WinState::onSelect(Menu& menu) {
    switch (currentIndex) {
        case 0: // Main Menu
            menu.changeState(Menu::State::Start);
            break;
    }
}
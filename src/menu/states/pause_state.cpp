#include "pause_state.h"
#include "../menu.h"

void PauseState::enter(Menu& menu) {
    title.setString("PAUSED");
    title.setFont(menu.getFont());
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        menu.getWindow().getSize().x / 2 - title.getGlobalBounds().width / 2,
        100
    );
    
    menuItems.clear();
    
    std::vector<std::string> items = {"Continue", "Main Menu"};
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

void PauseState::render(Menu& menu) {
    auto defaultView = menu.getWindow().getDefaultView();
    
    menu.getWindow().setView(defaultView);
    sf::RectangleShape overlay(sf::Vector2f(menu.getWindow().getSize()));
    overlay.setFillColor(sf::Color(0, 0, 0, 255)); // Màu đen với độ trong suốt
    
    menu.getWindow().draw(overlay);
    
    menu.getWindow().draw(title);
    for (const auto& item : menuItems) {
        menu.getWindow().draw(item);
    }
    menu.getWindow().setView(defaultView);
    menu.getWindow().display();
}

void PauseState::onSelect(Menu& menu) {
    switch (currentIndex) {
        case 0: // Continue
            menu.changeState(Menu::State::Playing);
            break;
        case 1: // Main Menu
            menu.changeState(Menu::State::Start);
            break;
    }
}
#include "settings_state.h"
#include "../menu.h"

void SettingsState::enter(Menu& menu) {
    title.setString("SETTINGS");
    title.setFont(menu.getFont());
    title.setCharacterSize(80);
    title.setFillColor(sf::Color::Red);
    title.setStyle(sf::Text::Bold);
    title.setPosition(
        menu.getWindow().getSize().x / 2 - title.getGlobalBounds().width / 2,
        100
    );
    
    menuItems.clear();
    
    // Map selection item
    sf::Text mapText;
    mapText.setString("Map: " + mapFiles[selectedMapIndex]);
    mapText.setFont(menu.getFont());
    mapText.setCharacterSize(50);
    mapText.setFillColor(sf::Color::Yellow);
    mapText.setPosition(
        menu.getWindow().getSize().x / 2 - mapText.getGlobalBounds().width / 2,
        300
    );
    menuItems.push_back(mapText);
    
    // Back item
    sf::Text backText;
    backText.setString("Back to Menu");
    backText.setFont(menu.getFont());
    backText.setCharacterSize(50);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(
        menu.getWindow().getSize().x / 2 - backText.getGlobalBounds().width / 2,
        400
    );
    menuItems.push_back(backText);
}

void SettingsState::render(Menu& menu) {
    menu.getWindow().clear();
    menu.getWindow().draw(menu.getBackground());
    menu.getWindow().draw(title);
    for (const auto& item : menuItems) {
        menu.getWindow().draw(item);
    }
    menu.getWindow().display();
}

void SettingsState::onSelect(Menu& menu) {
    switch (currentIndex) {
        case 0: // Map selection
            // Logic to change map can be added here
            break;
        case 1: // Back to Menu
            menu.setSelectedMap(mapFiles[selectedMapIndex]);
            menu.changeState(Menu::State::Start);
            break;
    }
}

void SettingsState::decreaseMapIndex() {
    selectedMapIndex = (selectedMapIndex - 1 + mapFiles.size()) % mapFiles.size();
    menuItems[0].setString("Map: " + mapFiles[selectedMapIndex]);
}

void SettingsState::increaseMapIndex() {
    selectedMapIndex = (selectedMapIndex + 1) % mapFiles.size();
    menuItems[0].setString("Map: " + mapFiles[selectedMapIndex]);
}

std::string SettingsState::getCurrentMap() const {
    return mapFiles[selectedMapIndex];
}
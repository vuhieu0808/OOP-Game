#include "base_state.h"

void MenuState::increaseIndex() {
    menuItems[currentIndex].setFillColor(sf::Color::White);
    currentIndex++;
    if (currentIndex >= menuItems.size()) {
        currentIndex = 0; // Wrap around to the first item
    }
    menuItems[currentIndex].setFillColor(sf::Color::Yellow);
}

void MenuState::decreaseIndex() {
    menuItems[currentIndex].setFillColor(sf::Color::White);
    currentIndex--;
    if (currentIndex < 0) {
        currentIndex = menuItems.size() - 1; // Wrap around to the last item
    }
    menuItems[currentIndex].setFillColor(sf::Color::Yellow);
}

void MenuState::selectItem() {
    selectedIndex = currentIndex;
}
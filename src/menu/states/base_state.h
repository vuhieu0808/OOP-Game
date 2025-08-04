#ifndef BASE_STATE_H
#define BASE_STATE_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Menu;

class MenuState {
protected:
    sf::Text title;
    std::vector<sf::Text> menuItems;
    int currentIndex = 0;
    int selectedIndex = 0;
    
public:
    virtual ~MenuState() = default;
    virtual void enter(Menu& menu) = 0;
    virtual void render(Menu& menu) = 0;
    virtual void onSelect(Menu& menu) = 0;

    void increaseIndex();
    void decreaseIndex();
    void selectItem();
};

#endif // BASE_STATE_H
#include "gameObject.h"
#include <SFML/Graphics.hpp>


GameObject::GameObject(const sf::Vector2f& pos) {
    shape.setPosition(pos);
}

sf::FloatRect GameObject::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

const sf::Vector2f& GameObject::getPosition() const {
    return shape.getPosition();
}

void GameObject::setPosition(const sf::Vector2f& pos) {
    shape.setPosition(pos);
}
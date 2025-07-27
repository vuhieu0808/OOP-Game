#include "gameObject.h"

GameObject::GameObject(const std::string& textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load texture: " + textureFile);
    }
    shape.setTexture(texture);
    size = sf::Vector2f(shape.getGlobalBounds().width, shape.getGlobalBounds().height);
}

void GameObject::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void GameObject::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}

void GameObject::setSize(const sf::Vector2f& newSize) {
    size = newSize;
    // shape.setScale(newSize.x / texture.getSize().x, newSize.y / texture.getSize().y);
}

void GameObject::setTexture(const sf::Texture& newTexture) {
    texture = newTexture;
    shape.setTexture(texture);
}

void GameObject::setScale(float scaleX, float scaleY) {
    shape.setScale(scaleX, scaleY);
}

void GameObject::setOrigin(float originX, float originY) {
    shape.setOrigin(originX, originY);
}

sf::FloatRect GameObject::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

const sf::Vector2f& GameObject::getPosition() const {
    return shape.getPosition();
}

const sf::Vector2f& GameObject::getSize() const {
    return size;
}

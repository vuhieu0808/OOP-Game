#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::Sprite shape;
    sf::Texture texture;
    sf::Vector2f size;

public:
    GameObject(const std::string& textureFile);
    virtual void draw(sf::RenderWindow& window);

    // Setters
    void setPosition(const sf::Vector2f& position);
    void setSize(const sf::Vector2f& newSize);
    void setTexture(const sf::Texture& newTexture);
    void setScale(float scaleX, float scaleY);
    void setOrigin(float originX, float originY);

    // Getters
    sf::FloatRect getGlobalBounds() const;
    const sf::Vector2f& getPosition() const;
    const sf::Vector2f& getSize() const;
};

#endif // GAME_OBJECT_H
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
protected:
    sf::Vector2f velocity;
    sf::RectangleShape shape;
    
public:
    GameObject(const sf::Vector2f& pos);
    virtual ~GameObject() = default;
    
    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getGlobalBounds() const;
    
    const sf::Vector2f& getPosition() const;
    void setPosition(const sf::Vector2f& pos);
};


#endif
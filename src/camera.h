#pragma once
#include <SFML/Graphics.hpp>

class Camera {
private:
    sf::View view;
    sf::Vector2f screenSize;  // Kích thước mỗi khung hình (1600x900)
    sf::Vector2i currentScreen; // Vị trí khung hình hiện tại (screenX, screenY)
    sf::FloatRect bounds;      // Giới hạn map
    
public:
    Camera(sf::Vector2f screenSize);
    
    void update(const sf::Vector2f& playerPosition);
    void applyTo(sf::RenderWindow& window);
    void setBounds(const sf::FloatRect& newBounds);
    
    const sf::Vector2i& getCurrentScreen() const;
    sf::Vector2f getScreenPosition() const;
    const sf::Vector2f& getSize() const { return screenSize; }
};
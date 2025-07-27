#include "camera.h"

Camera::Camera(sf::Vector2f screenSize) : 
    screenSize(screenSize),
    currentScreen(0, 0)
{
    view.setSize(screenSize);
    view.setCenter(screenSize / 2.f);
}

void Camera::update(const sf::Vector2f& playerPosition) {
    // Tính toán khung hình hiện tại dựa trên vị trí player
    sf::Vector2i newScreen(
        static_cast<int>(playerPosition.x / screenSize.x),
        static_cast<int>(playerPosition.y / screenSize.y)
    );
    
    // Nếu player sang khung hình mới
    if (newScreen != currentScreen) {
        currentScreen = newScreen;
        
        // Tính vị trí center mới (giữa khung hình)
        sf::Vector2f newCenter(
            (currentScreen.x + 0.5f) * screenSize.x,
            (currentScreen.y + 0.5f) * screenSize.y
        );
        
        // Giới hạn trong bounds
        newCenter.x = std::max(bounds.left + screenSize.x/2, 
                              std::min(bounds.left + bounds.width - screenSize.x/2, newCenter.x));
        newCenter.y = std::max(bounds.top + screenSize.y/2, 
                              std::min(bounds.top + bounds.height - screenSize.y/2, newCenter.y));
        
        view.setCenter(newCenter);
    }
}

void Camera::applyTo(sf::RenderWindow& window) {
    window.setView(view);
}

void Camera::setBounds(const sf::FloatRect& newBounds) {
    bounds = newBounds;
}

const sf::Vector2i& Camera::getCurrentScreen() const {
    return currentScreen;
}

sf::Vector2f Camera::getScreenPosition() const {
    return sf::Vector2f(
        currentScreen.x * screenSize.x,
        currentScreen.y * screenSize.y
    );
}
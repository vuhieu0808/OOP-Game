#pragma once
#include <SFML/Graphics.hpp>
#include "camera.h"
#include "map.h"

class Player {
private:
    Camera& camera;
    const Map& gameMap;

    // Hình dạng và thuộc tính nhân vật
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool isGrounded;
    
    // Hệ thống tích lực nhảy
    sf::RectangleShape jumpChargeBar;
    sf::RectangleShape jumpChargeBarBorder;
    float jumpCharge;
    bool isChargingJump;
    int moveDirection;
    bool isJumping;     // Trạng thái đang nhảy
    
    // Các hằng số vật lý
    const float gravity = 0.5f;
    const float baseJumpStrength = -2.f;
    const float maxJumpStrength = -16.f;
    const float chargeRate = 0.01667f;
    const float maxCharge = 1.5f;
    const float moveSpeed = 3.f;
    const float jumpHorizontalFactor = 0.7f; // Tỉ lệ tốc độ ngang khi nhảy
    const float airResistanceFactor = 0.98f; // Lực cản không khí
    const float COLLISION_THRESHOLD = 5.0f;

public:
    Player(sf::Vector2f position, Camera& cam, const Map& map);
    
    void update(float deltaTime);
    void handleInput();
    void draw(sf::RenderWindow& window);
    
    const sf::Vector2f& getPosition() const;
    void setPosition(sf::Vector2f position);
    sf::FloatRect getGlobalBounds() const;
    sf::RectangleShape getJumpChargeBar() const;
    sf::RectangleShape getJumpChargeBarBorder() const;
};
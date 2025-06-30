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
    
    // Texture system
    sf::Texture idleTexture;
    sf::Texture walkTexture;
    sf::Texture jumpTexture;
    sf::Texture chargeTexture;
    bool isFacingRight;
    
    // Hệ thống tích lực nhảy
    sf::RectangleShape jumpChargeBar;
    sf::RectangleShape jumpChargeBarBorder;
    float jumpCharge;
    bool isChargingJump;
    int moveDirection;
    bool isGrounded;
    bool isJumping;
    
    // Các hằng số vật lý
    const float gravity = 0.5f * 2000;
    const float baseJumpStrength = -2.f * 20;
    const float maxJumpStrength = -20.f * 50;
    const float chargeRate = 0.01667f * 100;
    const float maxCharge = 1.5f * 100;
    const float moveSpeed = 3.f * 50;
    const float jumpHorizontalFactor = 0.7f;
    const float COLLISION_THRESHOLD = 5.0f;

public:
    Player(sf::Vector2f position, Camera& cam, const Map& map);
    
    bool loadTextures(
        const std::string& idleTex,
        const std::string& walkTex,
        const std::string& jumpTex,
        const std::string& chargeTex
    );
    
    void update(float deltaTime);
    void handleInput();
    void draw(sf::RenderWindow& window);
    
    const sf::Vector2f& getPosition() const;
    void setPosition(sf::Vector2f position);
    sf::FloatRect getGlobalBounds() const;
    sf::RectangleShape getJumpChargeBar() const;
    sf::RectangleShape getJumpChargeBarBorder() const;
};
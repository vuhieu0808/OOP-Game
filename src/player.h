#pragma once
#include <SFML/Graphics.hpp>
#include "camera.h"
#include "map.h"
#include "gameObject.h"

class Player : public GameObject {
private:
    Camera& camera;
    const Map& gameMap;

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
    const float maxJumpStrength = -15.f * 50;
    const float chargeRate = 0.01667f * 100;
    const float maxCharge = 1.5f * 100;
    const float moveSpeed = 2.f * 50;
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
    
    void update(float deltaTime) override;
    void handleInput();
    void draw(sf::RenderWindow& window) override;
    
    sf::RectangleShape getJumpChargeBar() const;
    sf::RectangleShape getJumpChargeBarBorder() const;

    bool checkWinCondition(const Map& gameMap) const;
};
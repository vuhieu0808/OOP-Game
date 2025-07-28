#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "gameObject.h"
#include "observer.h"
#include "map.h"
#include "camera.h"

class Command;

class Player : public GameObject, public Subject {
public:
    enum class PlayerState {
        Idle,
        Walking,
        Jumping,
        ChargingJump
    };

private:
    sf::Vector2f velocity; // Vận tốc của player
    PlayerState currentState; // Trạng thái hiện tại của player

    // Trạng thái player
    float jumpCharge; // Tích lũy nhảy
    bool isChargingJump; // Đang tích lũy nhảy
    int moveDirection; // Hướng di chuyển
    bool isGround; // Đang ở trên mặt đất
    bool isJumping; // Đang nhảy
    bool isFacingRight; // Hướng nhìn của player

    // Hệ thống tích lực nhảy
    sf::RectangleShape jumpChargeBar;
    sf::RectangleShape jumpChargeBarBorder;

    const Map& gameMap; // Tham chiếu đến bản đồ

    // Các hằng số vật lý
    const float gravity = 0.5f * 2000; // Trọng lực
    const float baseJumpStrength = -2.f * 20; // Sức mạnh nhảy cơ bản
    const float maxJumpStrength = -15.f * 50; // Sức mạnh nhảy tối đa
    const float chargeRate = 0.01667f * 100; // Tốc độ tích lực
    const float maxCharge = 1.5f * 100; // Tối đa tích lực
    const float moveSpeed = 2.f * 50; // Tốc độ di chuyển
    const float jumpHorizontalFactor = 0.7f; // Hệ số nhảy ngang
    const float COLLISION_THRESHOLD = 5.0f; // Ngưỡng va chạm

public:
    Player(const std::string& textureFile, const Map& map);
    void draw(sf::RenderWindow& window) override;
    
    // Observer pattern
    std::string stateToString(PlayerState state) const;
    void changeState(PlayerState newState);

    // Update và xử lý input
    void update(float deltaTime);
    void handleInput();

    // Setters
    void setVelocityX(float vx);
    void setVelocityY(float vy);
    void setMoveDirection(int direction);
    void startCharging();
    void stopCharging();
    void setGrounded(bool grounded);
    void setJumping(bool jumping);
    void setFacingRight(bool facingRight);

    // Getters
    float getMoveSpeed() const;
    float getBaseJumpStrength() const;
    int getMoveDirection() const;
    bool isGrounded() const;
    bool isCharging() const;
    float calculateJumpStrength() const;
    bool getIsFacingRight() const;
    void increaseJumpCharge();
    void jump();

    bool checkWinCondition() const;
};

#endif // PLAYER_H
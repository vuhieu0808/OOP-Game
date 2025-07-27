#include "player.h"
#include "inputHandler.h"
#include <iostream>

Player::Player(const std::string& textureFile, const Map& map) : 
    GameObject(textureFile), 
    currentState(PlayerState::Idle),
    gameMap(map) 
{
    // Thiết lập hình dạng nhân vật
    this->setSize(sf::Vector2f(32.f, 32.f));
    this->setPosition(sf::Vector2f(100.f, 100.f)); // Vị trí khởi tạo
    velocity = sf::Vector2f(0.f, 0.f);
    
    jumpCharge = 0.f;
    isChargingJump = false;
    moveDirection = 0;
    isJumping = false;
    isFacingRight = true; // Ban đầu hướng nhìn sang phải

    // Thiết lập thanh tích lực nhảy
    jumpChargeBar.setSize(sf::Vector2f(10.f, 0.f));
    jumpChargeBar.setFillColor(sf::Color::Yellow);
    
    jumpChargeBarBorder.setSize(sf::Vector2f(14.f, 104.f));
    jumpChargeBarBorder.setFillColor(sf::Color::Black);
}

// Setters
void Player::setVelocityX(float vx) { velocity.x = vx; }
void Player::setVelocityY(float vy) { velocity.y = vy; }
void Player::setMoveDirection(int direction) { moveDirection = direction; }
void Player::startCharging() { isChargingJump = true; jumpCharge = 0.f; }
void Player::stopCharging() { isChargingJump = false; }
void Player::setGrounded(bool grounded) { isGround = grounded; }
void Player::setJumping(bool jumping) { isJumping = jumping; }
void Player::setFacingRight(bool facingRight) { isFacingRight = facingRight; }

// Getters
float Player::getMoveSpeed() const { return moveSpeed; }
float Player::getBaseJumpStrength() const { return baseJumpStrength; }
int Player::getMoveDirection() const { return moveDirection; }
bool Player::isGrounded() const { return isGround; }
bool Player::isCharging() const { return isChargingJump; }
float Player::calculateJumpStrength() const {
    return baseJumpStrength + (maxJumpStrength - baseJumpStrength) * (jumpCharge / maxCharge);
}
bool Player::getIsFacingRight() const { return isFacingRight; }

void Player::increaseJumpCharge() {
    jumpCharge += chargeRate;
    if (jumpCharge > maxCharge) {
        jumpCharge = maxCharge;
    }
}

void Player::jump() {
    float jumpPower = calculateJumpStrength();
    isGround = false;
    isJumping = true; // Cờ đang nhảy
    isChargingJump = false; // Kết thúc tích lũy nhảy
    jumpCharge = 0.f; // Reset tích lũy nhảy
    
    if (moveDirection == -1) { // Nhảy trái lên
        velocity.x = -moveSpeed * jumpHorizontalFactor;
    } 
    else if (moveDirection == 1) { // Nhảy phải lên
        velocity.x = moveSpeed * jumpHorizontalFactor;
    } 
    else { // Nhảy thẳng lên
        velocity.x = 0.f;
    }
    velocity.y = jumpPower;
}

void Player::draw(sf::RenderWindow& window) {
    GameObject::draw(window);
    if (isChargingJump) {
        sf::View originalView = window.getView(); // Save current view
        window.setView(window.getDefaultView());  // Switch to default view
        window.draw(jumpChargeBarBorder);
        window.draw(jumpChargeBar);
        window.setView(originalView); // Restore original view
    }
}

std::string Player::stateToString(PlayerState state) const {
    switch (state) {
        case PlayerState::Idle:         return "Idle";
        case PlayerState::Walking:      return "Walking";
        case PlayerState::Jumping:      return "Jumping";
        case PlayerState::ChargingJump: return "ChargingJump";
        default:                        return "Unknown";
    }
}

void Player::changeState(PlayerState newState) {
    currentState = newState;
    notify(stateToString(currentState));
}

void Player::handleInput() {
    InputHandler::getInstance().handleInput(*this);
}

void Player::update(float deltaTime) {
    // Áp dụng trọng lực
    velocity.y += gravity * deltaTime;
    
    // Lấy danh sách các tile va chạm từ map
    auto solidTiles = gameMap.getSolidTiles();
    sf::FloatRect playerBounds = shape.getGlobalBounds();
    
    // Xử lý di chuyển ngang (trục X)
    sf::Vector2f newPosition = shape.getPosition();
    if (!isChargingJump) {
        newPosition.x += velocity.x * deltaTime;
    }
    sf::FloatRect nextPlayerBoundsX(newPosition.x, playerBounds.top, playerBounds.width, playerBounds.height);

    // Kiểm tra va chạm ngang
    for (const auto& platform : solidTiles) {
        sf::FloatRect platformBounds = platform;
        if (nextPlayerBoundsX.intersects(platformBounds)) {
            // Xác định hướng va chạm
            float playerRight = playerBounds.left + playerBounds.width;
            float platformRight = platformBounds.left + platformBounds.width;
            
            // Va chạm từ bên trái platform
            if (velocity.x > 0 && playerRight - velocity.x * deltaTime <= platformBounds.left + COLLISION_THRESHOLD) {
                newPosition.x = platformBounds.left - playerBounds.width;
                velocity.x = -velocity.x * 0.8f; // Bật ngược lại với hệ số giảm
            }
            else if (velocity.x < 0 && playerBounds.left - velocity.x * deltaTime >= platformRight - COLLISION_THRESHOLD) {
                newPosition.x = platformBounds.left + platformBounds.width;
                velocity.x = -velocity.x * 0.8f; // Bật ngược lại với hệ số giảm
            }
        }
    }

    // Cập nhật vị trí tạm thời cho trục X
    shape.setPosition(newPosition);
    playerBounds = shape.getGlobalBounds();

    // Xử lý di chuyển dọc (trục Y)
    newPosition.y += velocity.y * deltaTime;
    isGround = false;

    // Kiểm tra va chạm dọc
    for (const auto& platform : solidTiles) {
        sf::FloatRect platformBounds = platform;
        sf::FloatRect nextPlayerBoundsY(playerBounds.left, newPosition.y, playerBounds.width, playerBounds.height);

        if (nextPlayerBoundsY.intersects(platformBounds)) {
            float playerBottom = playerBounds.top + playerBounds.height;
            float playerTop = playerBounds.top;
            float platformTop = platformBounds.top;
            float platformBottom = platformBounds.top + platformBounds.height;

            if (velocity.y >= 0) { // Rơi xuống
                // Kiểm tra xem player có vượt qua đỉnh platform không
                if (playerBottom <= platformTop && playerBottom + velocity.y * deltaTime >= platformTop) {
                    // Đặt player ngay trên đỉnh platform
                    newPosition.y = platformTop - playerBounds.height;
                    velocity.y = 0.f;
                    isGround = true;
                }
            } else if (velocity.y < 0) { // Nhảy lên
                // Kiểm tra va chạm với đáy platform
                if (playerTop >= platformBottom && playerTop + velocity.y * deltaTime <= platformBottom) {
                    newPosition.y = platformBottom;
                    velocity.y = 0.5f; // Bật nhẹ xuống dưới
                }
            }
        }
    }

    auto mapSize = gameMap.getMapSize();

    if (newPosition.y > mapSize.y) {
        newPosition.y = gameMap.getPlayerStartPos().y;
    }

    // Cập nhật vị trí cuối cùng
    shape.setPosition(newPosition);

    // Cập nhật thanh tích lực
    if (isChargingJump) {
        float barHeight = 100.f * (jumpCharge / maxCharge);
        jumpChargeBar.setSize(sf::Vector2f(10.f, barHeight));
        
        // Đặt vị trí thanh tích lực
        jumpChargeBar.setPosition(20.f, 20.f + (100.f - barHeight));
        jumpChargeBarBorder.setPosition(18.f, 18.f);
    } else {
        jumpChargeBar.setSize(sf::Vector2f(10.f, 0.f));
    }
}
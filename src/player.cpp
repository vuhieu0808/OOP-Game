#include "player.h"
#include "game.h"
#include <iostream>

Player::Player(sf::Vector2f position, Camera& cam, const Map& gameMap) : 
    camera(cam),
    isGrounded(false),
    jumpCharge(0.f),
    isChargingJump(false),
    gameMap(gameMap)
{
    // Thiết lập hình dạng nhân vật
    shape.setSize(sf::Vector2f(32.f, 32.f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
    velocity = sf::Vector2f(0.f, 0.f);

    // Thiết lập thanh tích lực nhảy
    jumpChargeBar.setSize(sf::Vector2f(10.f, 0.f));
    jumpChargeBar.setFillColor(sf::Color::Yellow);
    
    jumpChargeBarBorder.setSize(sf::Vector2f(14.f, 104.f));
    jumpChargeBarBorder.setFillColor(sf::Color::Black);
}

void Player::handleInput() {
    // Xử lý di chuyển thông thường khi không tích lực
    if (!isChargingJump && isGrounded) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x = -moveSpeed;
            moveDirection = -1; // Lưu hướng trái
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x = moveSpeed;
            moveDirection = 1; // Lưu hướng phải
        }
        else {
            velocity.x = 0.f;
            moveDirection = 0; // Không di chuyển ngang
        }
    }

    // Khi đang tích lực thì chỉ lưu hướng, không di chuyển
    if (isChargingJump && isGrounded) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            moveDirection = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            moveDirection = 1;
        }
        // Giữ nguyên moveDirection nếu không bấm phím nào
    }

    // Xử lý nhảy
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (isGrounded && !isChargingJump) {
            isChargingJump = true;
            jumpCharge = 0.f;
            // Mặc định hướng hiện tại khi bắt đầu tích lực
            moveDirection = (velocity.x < 0) ? -1 : (velocity.x > 0) ? 1 : 0;
        }

        if (isChargingJump && isGrounded) {
            jumpCharge += chargeRate;
            jumpCharge = std::min(jumpCharge, maxCharge);
        }
    }
    else if (isChargingJump && isGrounded) {
        // Thực hiện nhảy với hướng đã khóa
        float jumpPower = baseJumpStrength + (maxJumpStrength - baseJumpStrength) * (jumpCharge / maxCharge);
        
        // Vector nhảy cố định theo hướng đã chọn
        if (moveDirection == -1) { // Nhảy trái lên
            velocity.x = -moveSpeed * jumpHorizontalFactor;
            velocity.y = jumpPower;
        }
        else if (moveDirection == 1) { // Nhảy phải lên
            velocity.x = moveSpeed * jumpHorizontalFactor;
            velocity.y = jumpPower;
        }
        else { // Nhảy thẳng lên
            velocity.x = 0.f;
            velocity.y = jumpPower;
        }

        isGrounded = false;
        isChargingJump = false;
        jumpCharge = 0.f;
        isJumping = true; // Cờ đang nhảy
    }

    // Khi đang bay thì KHÔNG THỂ thay đổi hướng
    if (isJumping && !isGrounded) {
        // Vô hiệu hóa input trái/phải
        // Giữ nguyên velocity.x đã được set khi nhảy
    }

    // Reset khi chạm đất
    if (isGrounded) {
        isJumping = false;
    }
}

void Player::update(float deltaTime) {
    // Áp dụng trọng lực
    velocity.y += gravity;
    
    // Lấy danh sách các tile va chạm từ map
    auto solidTiles = gameMap.getSolidTiles();
    sf::FloatRect playerBounds = shape.getGlobalBounds();
    
    // Xử lý di chuyển ngang (trục X)
    sf::Vector2f newPosition = shape.getPosition();
    if (!isChargingJump) {
        newPosition.x += velocity.x;
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
            if (velocity.x > 0 && playerRight - velocity.x <= platformBounds.left + COLLISION_THRESHOLD) {
                newPosition.x = platformBounds.left - playerBounds.width;
                velocity.x = -velocity.x * 0.8f; // Bật ngược lại với hệ số giảm
            }
            // Va chạm từ bên phải platform
            else if (velocity.x < 0 && playerBounds.left - velocity.x >= platformRight - COLLISION_THRESHOLD) {
                newPosition.x = platformBounds.left + platformBounds.width;
                velocity.x = -velocity.x * 0.8f; // Bật ngược lại với hệ số giảm
            }
        }
    }

    // Cập nhật vị trí tạm thời cho trục X
    shape.setPosition(newPosition);
    playerBounds = shape.getGlobalBounds();

    // Xử lý di chuyển dọc (trục Y)
    float displacementY = velocity.y;
    newPosition.y += displacementY;
    isGrounded = false;

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
                if (playerBottom <= platformTop && playerBottom + displacementY >= platformTop) {
                    // Đặt player ngay trên đỉnh platform
                    newPosition.y = platformTop - playerBounds.height;
                    velocity.y = 0.f;
                    isGrounded = true;
                }
            } else if (velocity.y < 0) { // Nhảy lên
                // Kiểm tra va chạm với đáy platform
                if (playerTop >= platformBottom && playerTop + displacementY <= platformBottom) {
                    newPosition.y = platformBottom;
                    velocity.y = 0.5f; // Bật nhẹ xuống dưới
                }
            }
        }
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

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
    if (isChargingJump) {
        // window.draw(jumpChargeBarBorder);
        // window.draw(jumpChargeBar);
        sf::View originalView = window.getView(); // Save current view
        window.setView(window.getDefaultView());  // Switch to default view
        window.draw(jumpChargeBarBorder);
        window.draw(jumpChargeBar);
        window.setView(originalView); // Restore original view
    }
}

const sf::Vector2f& Player::getPosition() const {
    return shape.getPosition();
}

void Player::setPosition(sf::Vector2f position) {
    shape.setPosition(position);
}

sf::FloatRect Player::getGlobalBounds() const {
    return shape.getGlobalBounds();
}

sf::RectangleShape Player::getJumpChargeBar() const {
    return jumpChargeBar;
}

sf::RectangleShape Player::getJumpChargeBarBorder() const {
    return jumpChargeBarBorder;
}
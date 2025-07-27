#include "inputHandler.h"
#include "player.h"
#include "command.h"

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

void InputHandler::handleInput(Player& player) {
    // Di chuyển
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        left = std::make_unique<MoveLeftCommand>();
        left->execute(player);
        player.changeState(Player::PlayerState::Walking);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        right = std::make_unique<MoveRightCommand>();
        right->execute(player);
        player.changeState(Player::PlayerState::Walking);
    } else {
        stop = std::make_unique<StopCommand>();
        stop->execute(player);
        player.changeState(Player::PlayerState::Idle);
    }

    // Khi đang tích lực thì chỉ lưu hướng, không di chuyển
    if (player.isCharging() && player.isGrounded()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player.setMoveDirection(-1);
            player.setFacingRight(false);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player.setMoveDirection(1);
            player.setFacingRight(true);
        }
        player.changeState(Player::PlayerState::ChargingJump);
    }

    // Nhảy
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!player.isCharging() && player.isGrounded()) {
            startCharge = std::make_unique<StartChargingCommand>();
            startCharge->execute(player);
            player.changeState(Player::PlayerState::ChargingJump);
        }

        if (player.isCharging() && player.isGrounded()) {
            charge = std::make_unique<ChargeJumpCommand>();
            charge->execute(player);
        }
    } else if (player.isCharging() && player.isGrounded()) {
        releaseJump = std::make_unique<ReleaseJumpCommand>();
        releaseJump->execute(player);
        player.changeState(Player::PlayerState::Jumping);
    }

    if (player.isGrounded()) {
        player.setJumping(false);
    }
}

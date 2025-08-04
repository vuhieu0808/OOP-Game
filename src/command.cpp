#include "command.h"
#include "player.h"
#include <iostream>

void MoveLeftCommand::execute(Player& player) {
    if (!player.isCharging() && player.isGrounded()) {
        player.setMoveDirection(-1);
        player.setVelocityX(-player.getMoveSpeed());
        player.setFacingRight(false);
    }
    if (player.isCharging() && player.isGrounded()) {
        player.setMoveDirection(-1);
        player.setFacingRight(false);
    }
}

void MoveRightCommand::execute(Player& player) {
    if (!player.isCharging() && player.isGrounded()) {
        player.setMoveDirection(1);
        player.setVelocityX(player.getMoveSpeed());
        player.setFacingRight(true);
    }
    if (player.isCharging() && player.isGrounded()) {
        player.setMoveDirection(1);
        player.setFacingRight(true);
    }
}

void StopCommand::execute(Player& player) {
    if (!player.isCharging() && player.isGrounded()) {
        player.setMoveDirection(0);
        player.setVelocityX(0.f);
    }
    else if (player.isCharging() && player.isGrounded()) {
        // Giữ nguyên hướng và trạng thái tích lũy nhảy
    }
}

void StartChargingCommand::execute(Player& player) {
    player.startCharging();
}

void ChargeJumpCommand::execute(Player& player) {
    player.increaseJumpCharge();
}

void ReleaseJumpCommand::execute(Player& player) {
    player.jump();
}
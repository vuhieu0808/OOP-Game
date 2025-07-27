#include "animationSystem.h"
#include <iostream>

AnimationSystem::AnimationSystem(Player* player) : player(player) {
    // Load textures for different states
    if (!idleTexture.loadFromFile("media/player/idle.png")) {
        throw std::runtime_error("Failed to load idle texture");
    }
    if (!walkTexture.loadFromFile("media/player/walk.png")) {
        throw std::runtime_error("Failed to load walk texture");
    }
    if (!jumpTexture.loadFromFile("media/player/jump.png")) {
        throw std::runtime_error("Failed to load jump texture");
    }
    if (!chargeTexture.loadFromFile("media/player/charge.png")) {
        throw std::runtime_error("Failed to load charge texture");
    }

    // Set initial texture
    player->setTexture(idleTexture);
}

void AnimationSystem::onNotify(const std::string& eventName) {
    if (eventName == "Idle") {
        player->setTexture(idleTexture);
    } 
    else if (eventName == "Walking") {
        player->setTexture(walkTexture);
    } 
    else if (eventName == "Jumping") {
        player->setTexture(jumpTexture);
    } 
    else if (eventName == "ChargingJump") {
        player->setTexture(chargeTexture);
    }

    if (player->getIsFacingRight()) {
        player->setScale(1.f, 1.f);
        player->setOrigin(0.f, 0.f);
    } 
    else {
        player->setScale(-1.f, 1.f);
        player->setOrigin(player->getSize().x, 0.f);
    }
}
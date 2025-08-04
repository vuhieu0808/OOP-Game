#ifndef ANIMATION_SYSTEM_H
#define ANIMATION_SYSTEM_H

#include "observer.h"
#include "player.h"

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AnimationSystem : public Observer {
private: 
    Player* player;
    
    // textures for different states
    sf::Texture idleTexture; // Đứng yên
    sf::Texture walkTexture; // Đi bộ
    sf::Texture jumpTexture; // Nhảy
    sf::Texture chargeTexture; // Tích lực nhảy

public:
    AnimationSystem(Player* player);

    void onNotify(const std::string& eventName) override;
};

#endif // ANIMATION_SYSTEM_H
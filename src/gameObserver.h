#ifndef GAME_OBSERVER_H
#define GAME_OBSERVER_H

#include <vector>
#include <functional>

enum class GameEvent {
    PlayerWin,
    GamePaused,
    GameResumed
};

class IGameObserver {
public:
    virtual ~IGameObserver() = default;
    virtual void onGameEvent(GameEvent event) = 0;
};

#endif // GAME_OBSERVER_H
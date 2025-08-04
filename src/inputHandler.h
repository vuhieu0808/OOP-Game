#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include "command.h"

#include <memory>

class Player;

class InputHandler {
private:
    InputHandler() = default;

    std::unique_ptr<Command> left;
    std::unique_ptr<Command> right;
    std::unique_ptr<Command> stop;
    std::unique_ptr<Command> startCharge;
    std::unique_ptr<Command> charge;
    std::unique_ptr<Command> releaseJump;

public:
    static InputHandler& getInstance() {
        static InputHandler instance;
        return instance;
    }

    InputHandler(const InputHandler&) = delete;
    InputHandler& operator=(const InputHandler&) = delete;

    void handleInput(Player& player);
};

#endif // INPUT_HANDLER_H

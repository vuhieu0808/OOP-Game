#ifndef COMMAND_H
#define COMMAND_H

class Player;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Player& player) = 0;
};

class MoveLeftCommand : public Command {
public:
    void execute(Player& player) override;
};

class MoveRightCommand : public Command {
public:
    void execute(Player& player) override;
};

class StopCommand : public Command {
public:
    void execute(Player& player) override;
};

class StartChargingCommand : public Command {
public:
    void execute(Player& player) override;
};

// Tích lũy nhảy khi giữ space
class ChargeJumpCommand : public Command {
public:
    void execute(Player& player) override;
};

// Thả space để kết thúc việc tích lũy nhảy
class ReleaseJumpCommand : public Command {
public:
    void execute(Player& player) override;
};

#endif // COMMAND_H
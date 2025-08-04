#ifndef NAVIGATE_COMMAND_H
#define NAVIGATE_COMMAND_H

#include "menu_command.h"

class NavigateUpCommand : public MenuCommand {
public:
    bool execute(Menu& menu) override;
};

class NavigateDownCommand : public MenuCommand {
public:
    bool execute(Menu& menu) override;
};

class NavigateLeftCommand : public MenuCommand {
public:
    bool execute(Menu& menu) override;
};

class NavigateRightCommand : public MenuCommand {
public:
    bool execute(Menu& menu) override;
};

#endif // NAVIGATE_COMMAND_H
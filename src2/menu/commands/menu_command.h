#ifndef MENU_COMMAND_H
#define MENU_COMMAND_H

#include "../menu.h"

class MenuCommand {
public:
    virtual ~MenuCommand() = default;
    virtual bool execute(Menu& menu) = 0;
};

#endif // MENU_COMMAND_H
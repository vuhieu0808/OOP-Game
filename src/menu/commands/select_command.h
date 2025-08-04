#ifndef SELECT_COMMAND_H
#define SELECT_COMMAND_H

#include "menu_command.h"

class SelectCommand : public MenuCommand {
public:
    bool execute(Menu& menu) override;
};

#endif // SELECT_COMMAND_H
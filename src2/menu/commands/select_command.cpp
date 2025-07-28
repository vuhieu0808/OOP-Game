#include "select_command.h"
#include "../states/base_state.h"

bool SelectCommand::execute(Menu& menu) {
    menu.getCurrentStateObj().selectItem();
    menu.getCurrentStateObj().onSelect(menu);
    return true;
}
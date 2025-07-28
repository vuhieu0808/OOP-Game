#include "navigate_command.h"
#include "../states/base_state.h"
#include "../states/settings_state.h"

bool NavigateUpCommand::execute(Menu& menu) {
    menu.getCurrentStateObj().decreaseIndex();
    return true;
}

bool NavigateDownCommand::execute(Menu& menu) {
    menu.getCurrentStateObj().increaseIndex();
    return true;
}

bool NavigateLeftCommand::execute(Menu& menu) {
    if (dynamic_cast<SettingsState*>(&menu.getCurrentStateObj())) {
        auto& settings = static_cast<SettingsState&>(menu.getCurrentStateObj());
        settings.decreaseMapIndex();
        return true;
    }
    return false;
}

bool NavigateRightCommand::execute(Menu& menu) {
    if (dynamic_cast<SettingsState*>(&menu.getCurrentStateObj())) {
        auto& settings = static_cast<SettingsState&>(menu.getCurrentStateObj());
        settings.increaseMapIndex();
        return true;
    }
    return false;
}
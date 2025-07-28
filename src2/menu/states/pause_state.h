#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "base_state.h"

class PauseState : public MenuState {
public:
    void enter(Menu& menu) override;
    void render(Menu& menu) override;
    void onSelect(Menu& menu) override;
};

#endif // PAUSE_STATE_H
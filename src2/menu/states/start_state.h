#ifndef START_STATE_H
#define START_STATE_H

#include "base_state.h"

class StartState : public MenuState {
public:
    void enter(Menu& menu) override;
    void render(Menu& menu) override;
    void onSelect(Menu& menu) override;
};

#endif // START_STATE_H
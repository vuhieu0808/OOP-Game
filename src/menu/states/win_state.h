#ifndef WIN_STATE_H
#define WIN_STATE_H

#include "base_state.h"

class WinState : public MenuState {
public:
    void enter(Menu& menu) override;
    void render(Menu& menu) override;
    void onSelect(Menu& menu) override;
};

#endif // WIN_STATE_H
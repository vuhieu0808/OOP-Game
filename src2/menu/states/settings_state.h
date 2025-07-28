#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "base_state.h"

class SettingsState : public MenuState {
public:
    void enter(Menu& menu) override;
    void render(Menu& menu) override;
    void onSelect(Menu& menu) override;

    void decreaseMapIndex();
    void increaseMapIndex();

    std::string getCurrentMap() const;

private:
    std::vector<std::string> mapFiles = {"media/map/map1.tmx", "media/map/map2.tmx", "media/map/map3.tmx"};
    int selectedMapIndex = 0;
};

#endif // SETTINGS_STATE_H
#ifndef ATG_ENGINE_SIM_UI_CONTROLS_H
#define ATG_ENGINE_SIM_UI_CONTROLS_H

#include "ui_element.h"

// Help overlay listing every keyboard/mouse control (toggled with F1 / the
// Controls button). Styled like the console panel.
class UiControls : public UiElement {
    public:
        UiControls();
        virtual ~UiControls();

        virtual void render();
};

#endif /* ATG_ENGINE_SIM_UI_CONTROLS_H */

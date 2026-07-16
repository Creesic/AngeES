#ifndef ATG_ENGINE_SIM_UI_CONSOLE_H
#define ATG_ENGINE_SIM_UI_CONSOLE_H

#include "ui_element.h"

// Compile-error log panel shown when the console is toggled (F5 / Console
// button). Mirrors 1.14a's ErrorLogDisplay: a framed panel listing the
// most recent .mr compile output.
class UiConsole : public UiElement {
    public:
        UiConsole();
        virtual ~UiConsole();

        virtual void render();
};

#endif /* ATG_ENGINE_SIM_UI_CONSOLE_H */

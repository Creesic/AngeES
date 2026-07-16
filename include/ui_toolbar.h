#ifndef ATG_ENGINE_SIM_UI_TOOLBAR_H
#define ATG_ENGINE_SIM_UI_TOOLBAR_H

#include "ui_element.h"

class UiButton;

class UiToolbar : public UiElement {
    public:
        UiToolbar();
        virtual ~UiToolbar();

        virtual void initialize(EngineSimApplication *app);
        virtual void update(float dt);
        virtual void render();
        virtual void signal(UiElement *element, Event event);

        UiButton *getConsoleButton() { return m_consoleButton; }
        UiButton *getControlsButton() { return m_controlsButton; }

    protected:
        UiButton *m_loadEngineButton;
        UiButton *m_reloadButton;
        UiButton *m_loadThemeButton;
        UiButton *m_exitButton;
        UiButton *m_consoleButton;
        UiButton *m_controlsButton;
};

#endif /* ATG_ENGINE_SIM_UI_TOOLBAR_H */

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

    protected:
        UiButton *m_loadEngineButton;
        UiButton *m_reloadButton;
        UiButton *m_loadThemeButton;
        UiButton *m_exitButton;
};

#endif /* ATG_ENGINE_SIM_UI_TOOLBAR_H */

#ifndef ATG_ENGINE_SIM_UI_TAB_BAR_H
#define ATG_ENGINE_SIM_UI_TAB_BAR_H

#include "ui_element.h"

#include <vector>

class UiButton;

class UiTabBar : public UiElement {
    public:
        UiTabBar();
        virtual ~UiTabBar();

        virtual void initialize(EngineSimApplication *app);
        virtual void update(float dt);
        virtual void render();
        virtual void signal(UiElement *element, Event event);

    protected:
        std::vector<UiButton *> m_tabButtons;
};

#endif /* ATG_ENGINE_SIM_UI_TAB_BAR_H */

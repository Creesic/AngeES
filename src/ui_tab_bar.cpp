#include "../include/ui_tab_bar.h"

#include "../include/ui_button.h"
#include "../include/engine_sim_application.h"
#include "../include/view_manager.h"

UiTabBar::UiTabBar() {
    /* void */
}

UiTabBar::~UiTabBar() {
    /* void */
}

void UiTabBar::initialize(EngineSimApplication *app) {
    UiElement::initialize(app);

    ViewManager *views = m_app->getViewManager();
    for (int i = 0; i < views->getViewCount(); ++i) {
        UiButton *button = addElement<UiButton>(this);
        button->m_text = ViewManager::tabLabel(views->getView(i));
        button->m_fontSize = 16.0f;
        m_tabButtons.push_back(button);
    }
}

void UiTabBar::update(float dt) {
    const int n = (int)m_tabButtons.size();
    if (n > 0) {
        Grid grid;
        grid.h_cells = n;
        grid.v_cells = 1;
        for (int i = 0; i < n; ++i) {
            m_tabButtons[i]->m_bounds = grid.get(m_bounds, i, 0).inset(4.0f);
        }
    }

    UiElement::update(dt);
}

void UiTabBar::render() {
    UiElement::render();

    const int current = m_app->getViewManager()->getCurrentIndex();
    const int n = (int)m_tabButtons.size();
    if (n > 0 && current >= 0 && current < n) {
        Grid grid;
        grid.h_cells = n;
        grid.v_cells = 1;
        drawFrame(
            grid.get(m_bounds, current, 0).inset(4.0f),
            2.0f,
            m_app->getHightlight1Color(),
            m_app->getBackgroundColor(),
            false);
    }
}

void UiTabBar::signal(UiElement *element, Event event) {
    if (event != Event::Clicked) return;

    for (int i = 0; i < (int)m_tabButtons.size(); ++i) {
        if (element == m_tabButtons[i]) {
            m_app->getViewManager()->select(i);
            return;
        }
    }
}

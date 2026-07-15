#include "../include/ui_toolbar.h"

#include "../include/ui_button.h"
#include "../include/engine_sim_application.h"
#include "../include/platform_file_dialog.h"

UiToolbar::UiToolbar() {
    m_loadEngineButton = nullptr;
    m_reloadButton = nullptr;
    m_loadThemeButton = nullptr;
    m_exitButton = nullptr;
    m_consoleButton = nullptr;
}

UiToolbar::~UiToolbar() {
    /* void */
}

void UiToolbar::initialize(EngineSimApplication *app) {
    UiElement::initialize(app);

    m_loadEngineButton = addElement<UiButton>(this);
    m_loadEngineButton->m_text = "Load Engine";
    m_loadEngineButton->m_fontSize = 16.0f;

    m_reloadButton = addElement<UiButton>(this);
    m_reloadButton->m_text = "Reload";
    m_reloadButton->m_fontSize = 16.0f;

    m_loadThemeButton = addElement<UiButton>(this);
    m_loadThemeButton->m_text = "Load Theme";
    m_loadThemeButton->m_fontSize = 16.0f;

    m_exitButton = addElement<UiButton>(this);
    m_exitButton->m_text = "Exit";
    m_exitButton->m_fontSize = 16.0f;

    // Rendered separately in the engine-visualization header (positioned by the
    // app in renderScene), not part of the 4-button info-panel row below.
    m_consoleButton = addElement<UiButton>(this);
    m_consoleButton->m_text = "Console [F5]";
    m_consoleButton->m_fontSize = 16.0f;
}

void UiToolbar::update(float dt) {
    Grid grid;
    grid.h_cells = 4;
    grid.v_cells = 1;

    // The 4 action buttons fill the toolbar's info-panel row. The console button
    // is positioned separately by the app (engine-viz header), so it is not laid
    // out here.
    m_loadEngineButton->m_bounds = grid.get(m_bounds, 0, 0).inset(4.0f);
    m_reloadButton->m_bounds     = grid.get(m_bounds, 1, 0).inset(4.0f);
    m_loadThemeButton->m_bounds  = grid.get(m_bounds, 2, 0).inset(4.0f);
    m_exitButton->m_bounds       = grid.get(m_bounds, 3, 0).inset(4.0f);

    UiElement::update(dt);
}

void UiToolbar::render() {
    UiElement::render();
}

void UiToolbar::signal(UiElement *element, Event event) {
    if (event != Event::Clicked) return;

    if (element == m_loadEngineButton) {
        const std::string path = PlatformFileDialog::openFile(
            "Load Engine", "Engine scripts (*.mr)", "*.mr");
        if (!path.empty()) {
            m_app->requestEngineReload(path);
        }
    }
    else if (element == m_reloadButton) {
        m_app->requestEngineReload(m_app->getScriptPath());
    }
    else if (element == m_exitButton) {
        m_app->quit();
    }
    else if (element == m_consoleButton) {
        m_app->toggleConsole();
    }
    // m_loadThemeButton: intentionally inert (stub, per spec).
}

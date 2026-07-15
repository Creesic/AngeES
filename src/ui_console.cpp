#include "../include/ui_console.h"

#include "../include/engine_sim_application.h"

#include <string>
#include <vector>

UiConsole::UiConsole() {
    /* void */
}

UiConsole::~UiConsole() {
    /* void */
}

void UiConsole::render() {
    drawFrame(m_bounds, 2.0f, m_app->getForegroundColor(), m_app->getBackgroundColor());

    const Bounds inner = m_bounds.inset(15.0f);

    drawText("CONSOLE  (F5 to close)", inner, 24.0f, Bounds::tl);

    const std::vector<std::string> &log = m_app->getConsoleLog();

    const float lineHeight = 22.0f;
    float lineY = inner.top() - 44.0f;
    for (const std::string &line : log) {
        const Bounds lineBounds(inner.width(), lineHeight, { inner.left(), lineY }, Bounds::tl);
        drawText(line, lineBounds, 16.0f, Bounds::tl);
        lineY -= lineHeight;
    }
}

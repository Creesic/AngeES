#include "../include/ui_controls.h"

#include "../include/engine_sim_application.h"

namespace {
    struct ControlLine {
        // desc == nullptr: section header (or a blank spacer when key is empty).
        // otherwise: key column + description column.
        const char *key;
        const char *desc;
    };

    const ControlLine CONTROL_LINES[] = {
        { "Throttle & Engine", nullptr },
        { "Q / W / E / R", "Throttle 1% / 10% / 20% / 100%" },
        { "S", "Starter motor (hold)" },
        { "A", "Ignition on / off" },
        { "Up / Down", "Upshift / downshift" },
        { "Shift", "Depress clutch (hold)" },
        { "Y", "Hold clutch out" },
        { "Space", "Fine control (hold) / smooth clutch" },
        { "", nullptr },
        { "Dynamometer", nullptr },
        { "D", "Dyno enable / disable" },
        { "H", "Dyno hold" },
        { "G + scroll", "Set dyno speed" },
        { "", nullptr },
        { "Audio  (hold key + scroll wheel)", nullptr },
        { "Z / X / C", "Volume / convolution / high-freq gain" },
        { "V / B / N", "Low-freq noise / high-freq noise / sim. frequency" },
        { "", nullptr },
        { "View & Display", nullptr },
        { "Tab", "Cycle view (Dashboard / Engine / Split)" },
        { "F1", "This controls menu" },
        { "F5", "Console (compile errors)" },
        { "F", "Toggle fullscreen" },
        { "F4 / F2", "Rotate display" },
        { "F3", "Reset display rotation" },
        { "M / ,", "Render layer up / down" },
        { "", nullptr },
        { "Simulation & Application", nullptr },
        { "1 / 2 / 3 / 4 / 5", "Slow motion" },
        { "Enter", "Reload engine" },
        { "Insert", "Start / stop recording" },
        { "Esc", "Quit" },
    };
}

UiControls::UiControls() {
    /* void */
}

UiControls::~UiControls() {
    /* void */
}

void UiControls::render() {
    drawFrame(m_bounds, 2.0f, m_app->getForegroundColor(), m_app->getBackgroundColor());

    const Bounds inner = m_bounds.inset(20.0f);

    dbasic::TextRenderer *text = m_app->getTextRenderer();
    const ysVector headerColor = ysColor::linearToSrgb(m_app->getHightlight1Color());
    const ysVector keyColor = ysColor::linearToSrgb(m_app->getYellow());
    const ysVector descColor = ysColor::linearToSrgb(m_app->getForegroundColor());

    text->SetColor(headerColor);
    drawText("CONTROLS  (F1 to close)", inner, 26.0f, Bounds::tl);

    const float fontSize = 17.0f;
    const float lineHeight = 24.0f;
    const float descX = inner.left() + 230.0f;

    float lineY = inner.top() - 48.0f;
    for (const ControlLine &line : CONTROL_LINES) {
        if (line.desc == nullptr) {
            if (line.key[0] != '\0') {
                const Bounds b(inner.width(), lineHeight, { inner.left(), lineY }, Bounds::tl);
                text->SetColor(headerColor);
                drawText(line.key, b, 18.0f, Bounds::tl);
            }
        }
        else {
            const Bounds keyBounds(220.0f, lineHeight, { inner.left() + 10.0f, lineY }, Bounds::tl);
            text->SetColor(keyColor);
            drawText(line.key, keyBounds, fontSize, Bounds::tl);

            const Bounds descBounds(inner.width(), lineHeight, { descX, lineY }, Bounds::tl);
            text->SetColor(descColor);
            drawText(line.desc, descBounds, fontSize, Bounds::tl);
        }

        lineY -= lineHeight;
    }

    // Restore the frame-wide text color so nothing drawn afterwards inherits ours.
    text->SetColor(descColor);
}

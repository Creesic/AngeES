#include "../include/view_manager.h"

ViewManager::ViewManager() {
    m_current = 0;
}

ViewManager::~ViewManager() {
    /* void */
}

int ViewManager::addView(const std::string &name, const std::string &keyLabel, int shortcut) {
    View view;
    view.name = name;
    view.keyLabel = keyLabel;
    view.shortcut = shortcut;
    m_views.push_back(view);
    return (int)m_views.size() - 1;
}

void ViewManager::select(int index) {
    if (index >= 0 && index < (int)m_views.size()) {
        m_current = index;
    }
}

bool ViewManager::selectByShortcut(int shortcut) {
    for (int i = 0; i < (int)m_views.size(); ++i) {
        if (m_views[i].shortcut != 0 && m_views[i].shortcut == shortcut) {
            m_current = i;
            return true;
        }
    }
    return false;
}

void ViewManager::cycleNext() {
    if (m_views.empty()) return;
    m_current = (m_current + 1) % (int)m_views.size();
}

std::string ViewManager::tabLabel(const View &view) {
    if (view.keyLabel.empty()) return view.name;
    return view.name + " [" + view.keyLabel + "]";
}

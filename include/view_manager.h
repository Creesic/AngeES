#ifndef ATG_ENGINE_SIM_VIEW_MANAGER_H
#define ATG_ENGINE_SIM_VIEW_MANAGER_H

#include <string>
#include <vector>

class ViewManager {
    public:
        struct View {
            std::string name;
            std::string keyLabel;   // e.g. "F5"; empty means no shortcut hint
            int shortcut;           // key code; 0 means no shortcut
        };

    public:
        ViewManager();
        ~ViewManager();

        int addView(const std::string &name, const std::string &keyLabel, int shortcut);

        int getCurrentIndex() const { return m_current; }
        void select(int index);
        bool selectByShortcut(int shortcut);
        void cycleNext();

        int getViewCount() const { return (int)m_views.size(); }
        const View &getView(int index) const { return m_views[index]; }

        static std::string tabLabel(const View &view);

    private:
        std::vector<View> m_views;
        int m_current;
};

#endif /* ATG_ENGINE_SIM_VIEW_MANAGER_H */

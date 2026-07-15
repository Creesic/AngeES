#ifndef ATG_ENGINE_SIM_PLATFORM_FILE_DIALOG_H
#define ATG_ENGINE_SIM_PLATFORM_FILE_DIALOG_H

#include <string>

namespace PlatformFileDialog {
    // Opens a native "open file" dialog. Returns the selected absolute path,
    // or an empty string if the user cancelled (or the platform is unsupported).
    //   title         - window title, e.g. "Load Engine"
    //   filterName    - human label,  e.g. "Engine scripts (*.mr)"
    //   filterPattern - glob pattern, e.g. "*.mr"
    std::string openFile(const char *title, const char *filterName, const char *filterPattern);
}

#endif /* ATG_ENGINE_SIM_PLATFORM_FILE_DIALOG_H */

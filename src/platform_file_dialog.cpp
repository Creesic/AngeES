#include "../include/platform_file_dialog.h"

#if defined(_WIN32)

#include <Windows.h>
#include <commdlg.h>
#include <cstdio>
#include <cstring>

std::string PlatformFileDialog::openFile(
        const char *title, const char *filterName, const char *filterPattern) {
    // COMDLG32 filter format is a double-null-terminated pair list:
    //   "<name>\0<pattern>\0\0". Build it with explicit embedded nulls.
    char filter[128];
    int n = 0;
    n += std::snprintf(filter + n, sizeof(filter) - n, "%s", filterName) + 1;
    n += std::snprintf(filter + n, sizeof(filter) - n, "%s", filterPattern) + 1;
    filter[n] = '\0';

    char fileName[MAX_PATH] = "";

    OPENFILENAMEA ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = title;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR;

    if (GetOpenFileNameA(&ofn)) {
        return std::string(fileName);
    }

    return std::string();
}

#endif /* _WIN32 */

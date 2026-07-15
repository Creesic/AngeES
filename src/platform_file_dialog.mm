#include "../include/platform_file_dialog.h"

#if defined(__APPLE__)

#import <AppKit/AppKit.h>

std::string PlatformFileDialog::openFile(
        const char *title, const char *filterName, const char *filterPattern) {
    (void)filterName;

    @autoreleasepool {
        NSOpenPanel *panel = [NSOpenPanel openPanel];
        [panel setCanChooseFiles:YES];
        [panel setCanChooseDirectories:NO];
        [panel setAllowsMultipleSelection:NO];
        if (title != nullptr) {
            [panel setTitle:[NSString stringWithUTF8String:title]];
        }

        // filterPattern like "*.mr" -> allowed extension "mr".
        NSString *pattern = [NSString stringWithUTF8String:filterPattern];
        NSString *ext = [pattern pathExtension];
        if ([ext length] > 0) {
            [panel setAllowedFileTypes:@[ ext ]];
        }

        if ([panel runModal] == NSModalResponseOK) {
            NSURL *url = [[panel URLs] firstObject];
            if (url != nil) {
                return std::string([[url path] UTF8String]);
            }
        }
    }

    return std::string();
}

#endif /* __APPLE__ */

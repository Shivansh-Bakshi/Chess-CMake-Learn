#ifndef CH_WINCOLORUTILS_H
#define CH_WINCOLORUTILS_H

#include <windows.h>

namespace ch {
    namespace utils {
        class WinColorUtils {
            CONSOLE_SCREEN_BUFFER_INFO Info;
            HANDLE hConsole;
            WORD Attributes;

            public:

            WinColorUtils() 
            {
                hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                GetConsoleScreenBufferInfo(hConsole, &Info);
                Attributes = Info.wAttributes;
            }

            void setSelectedColor() 
            {
                SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
            }

            void resetColor()
            {
                SetConsoleTextAttribute(hConsole, Attributes);
            }
        };
    }
}

#endif
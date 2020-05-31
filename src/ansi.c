/*This code has to be used to set ENABLE_VIRTUAL_TERMINAL_PROCESSING for the console when using MINGW,
otherwise the ANSI escape codes aren't working. This is code we found online, because we had to choose
between doing this or scraping every display function we had so far and start over.*/

#ifdef _WIN32
#include <windows.h>
#endif

#include <stdio.h>
#include "ansi.h"

#ifdef _WIN32
static HANDLE stdoutHandle;
static DWORD outModeInit;

void setupConsole() {
    DWORD outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if(stdoutHandle == INVALID_HANDLE_VALUE) {
        exit(GetLastError());
    }
    if(!GetConsoleMode(stdoutHandle, &outMode)) {
        exit(GetLastError());
    }
    outModeInit = outMode;
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; //Enable ANSI escape codes
    if(!SetConsoleMode(stdoutHandle, outMode)) {
        exit(GetLastError());
    }
}

void restoreConsole() {
    printf("\x1b[0m"); //Reset colors
    if(!SetConsoleMode(stdoutHandle, outModeInit)) { //Reset console mode
        exit(GetLastError());
    }
}
#else
void setupConsole() {}

void restoreConsole() {
    printf("\x1b[0m"); //Reset colors
}
#endif
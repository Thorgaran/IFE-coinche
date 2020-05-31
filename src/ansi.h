#ifndef ANSI_H
#define ANSI_H

/*If using MINGW, set ENABLE_VIRTUAL_TERMINAL_PROCESSING. Otherwise, do nothing
*/
void setupConsole();

/*Reset colors. If using MINGW, reset ENABLE_VIRTUAL_TERMINAL_PROCESSING
*/
void restoreConsole();

#endif // ANSI_H

#include "../include/editor.h"
#include "../include/terminal.h"

struct editorConfig E;

void initEditor() {
    if (getWindowSize(&E.screenrows, &E.screencols) == -1)
        die("getWindowSize");
}
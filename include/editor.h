#ifndef EDITOR_H
#define EDITOR_H

#include <termios.h>

struct editorConfig {
    int screenrows;
    int screencols;
    struct termios orig_termios;
};

extern struct editorConfig E;

void initEditor(void);

#endif
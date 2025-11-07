#ifndef TERMINAL_H
#define TERMINAL_H

#include <termio.h>

void enableRawMode(struct termios *orig_termios);
void disableRawMode(struct termios *orig_termios);
void die(const char *s);
char editorReadKey();
int getWindowSize(int *rows, int *cols);
int getCursorPosition(int *rows, int *cols);

#endif
#include "../include/output.h"
#include "../include/editor.h"
#include <unistd.h>

void editorRefreshScreen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    editorDrawRows();
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void editorDrawRows()
{
    int i;
    for (i = 0; i < E.screenrows; i++)
    {
        write(STDOUT_FILENO, "~", 1);

        if (i < E.screenrows - 1)
        {
            write(STDOUT_FILENO, "\r\n", 2);
        }
    }

    
    
    
}
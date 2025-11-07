#include "../include/terminal.h"
#include "../include/input.h"
#include "../include/output.h"
#include "../include/editor.h"
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main()
{
	enableRawMode(&E.orig_termios);
    initEditor();

	while (1)
	{	
        editorRefreshScreen();
        editorProcessKeypress();
	}
	
	return 0;
}

#include "../include/terminal.h"
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <ctype.h>

static struct termios *saved_termios = NULL;

static void disableRawModeWrapper(void) {
    if (saved_termios)
        disableRawMode(saved_termios);
}

void die(const char *s)
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
	perror(s);
	exit(1);
}

void disableRawMode(struct termios *orig_termios)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, orig_termios) == -1)
	{
		die("tcsetattr");
	}
	
}

void enableRawMode(struct termios *orig_termios)
{
	if (tcgetattr(STDIN_FILENO, orig_termios) == -1)
	{
		die("tcgetattr");
	}
	
	saved_termios = orig_termios;
    atexit(disableRawModeWrapper);

	struct termios raw = *orig_termios;

	//BRKINT, INPCK, ISTRIP, and CS8 are probably tuned off in modern
	//Terminals but due to tradition of raw mode we turn off these again
	raw.c_iflag &= ~(IXON | ICRNL | BRKINT | INPCK | ISTRIP);
	raw.c_oflag &= ~(OPOST);
	raw.c_cflag |= (CS8);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
	raw.c_cc[VMIN] = 0;
	raw.c_cc[VTIME] = 1;
	
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
	{
		die("tcsetattr");
	}
	
	
}

char editorReadKey()
{
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if (nread == -1 && errno != EAGAIN)
        {
            die("read");
        }
        
    }
    
    return c;
}

int getWindowSize(int *rows, int *cols)
{
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
    {
        if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
        {
            return -1;
        }
        return getCursorPosition(rows, cols);
        
        
    }
    else
    {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
    
}

int getCursorPosition(int *rows, int *cols)
{
    char buf[32];
    unsigned int i = 0;

    if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
    {
        return -1;
    }

    while (i < sizeof(buf) -1)
    {
        if (read(STDIN_FILENO, &buf[i], 1) != 1)
        {
            break;;
        }

        if (buf[i] == 'R')
        {
            break;;
        }
        i++;
    }

    buf[i] = '\0';
    if (buf[0] != '\x1b' || buf[1] != '[')
    {
        return -1;
    }

    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
    {
        return -1;
    }
    
    

    editorReadKey();

    return -1;
    
    
}


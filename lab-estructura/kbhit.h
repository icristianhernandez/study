#ifndef KBHIT_H
#define KBHIT_H

#ifdef _WIN32
#include <conio.h>

int _kbhit() { return _kbhit(); }

#else // Linux
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>

inline int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN, &readfds);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 0;

    int ret = select(STDIN + 1, &readfds, NULL, NULL, &tv);

    return ret > 0 && FD_ISSET(STDIN, &readfds);
}

#endif // _WIN32

#endif // KBHIT_H

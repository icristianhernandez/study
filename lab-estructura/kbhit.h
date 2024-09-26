#pragma once

#ifndef KBHIT_H
#define KBHIT_H

#ifdef _WIN32
#include <conio.h>
#else // Linux
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include <unistd.h>
#endif

#ifdef _WIN32
inline int _kbhit() { return kbhit(); }
#else
inline int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (!initialized) {
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

    timeval tv = {0, 0};

    int flags = fcntl(STDIN, F_GETFL, 0);
    fcntl(STDIN, F_SETFL, flags | O_NONBLOCK);

    int ret = select(STDIN + 1, &readfds, NULL, NULL, &tv);

    fcntl(STDIN, F_SETFL, flags); // Restore original flags

    return ret > 0 && FD_ISSET(STDIN, &readfds);
}
#endif // _WIN32

#endif // KBHIT_H

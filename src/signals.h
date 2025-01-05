#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "./banners.h"


void __display_signal_help() {
    printf(
        "\n" HINT_BANNER "Online docs for signal errors:\n\
 \x1b[2m·\x1b[0m Wikipedia: \x1b[0;4;34mhttps://en.wikipedia.org/wiki/Signal_(IPC)#POSIX_signals\x1b[0m\n\
 \x1b[2m·\x1b[0m GNU: \x1b[0;4;34mhttps://www.gnu.org/software/libc/manual/html_node/Standard-Signals.html\x1b[0m\n\
 \x1b[2m·\x1b[0m Linux Man: \x1b[0;4;34mhttps://man7.org/linux/man-pages/man7/signal.7.html\x1b[0m\n"
    );
}

// SIGHUP: 1	Hangup
void sighup_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mHangup signal received. \x1b[30mThis can occur when the terminal\nthat started the process is closed or disconnected.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGINT: 2	Interactive attention signal.
void sigint_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mInteractive attention  signal received.  \x1b[30mThis can occur when\nthe user presses Ctrl+C in the terminal where the process is\nrunning.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGQUIT: 3	Quit.
void sigquit_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mQuit signal received. \x1b[30mThis can occur when the user presses\nCtrl+\\ in the terminal where the process is running.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGILL: 4	Illegal instruction.
void sigill_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mIllegal instruction signal received. \x1b[30mThis can occur when the\nprocess  attempts  to  execute    an  invalid   or undefined\ninstruction.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGTRAP: 5	Trace/breakpoint trap.
void sigtrap_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mTrace/breakpoint trap signal received. \x1b[30mThis can occur when\nthe process hits a breakpoint set by a debugger.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGABRT: 6	Abnormal termination.
void sigabrt_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mAbnormal termination signal received. \x1b[30mThis can occur when\nthe process  is terminated  abnormally,  such as  when it\nencounters an unrecoverable error.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGFPE: 8	Erroneous arithmetic operation.
void sigfpe_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mErroneous  arithmetic operation  signal  received. \x1b[30mThis can\noccur  when the process  attempts  to  perform   an invalid\narithmetic operation.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGKILL: 9	Killed.
// The signals SIGKILL and SIGSTOP cannot be caught, blocked, or ignored.
// void sigkill_handler(int signal);

// SIGSEGV: 11	Invalid access to storage.
void sigsegv_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mInvalid access  to storage  signal  received. \x1b[30mThis can occur\nwhen the process attempts to access  memory  that it  is not\nallowed to access.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGPIPE: 13	Broken pipe.
void sigpipe_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mBroken pipe signal received. \x1b[30mThis can occur when the process\nwrites to a pipe that has been closed by the other end.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGALRM: 14	Alarm clock.
void sigalrm_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mAlarm clock signal received. \x1b[30mThis can occur when a timer set\nby the process expires.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

// SIGTERM: 15	Termination request.
void sigterm_handler(int signal) {
    printf("\n" ERROR_BANNER "\x1b[31mTermination request signal received. \x1b[30mThis can occur when the\nprocess is requested to terminate cleanly.\x1b[0m\n");
    __display_signal_help();
    exit(signal);
}

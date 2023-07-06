#include "common.h"

#include <stdio.h>

bool register_sig(void (*callback)(int))
{
    int signals[] = {SIGHUP, SIGINT, SIGSEGV};
    struct sigaction act;
    act.sa_handler = callback;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    for (int sig : signals) {
        if (sigaction(sig, &act, nullptr)) {
            printf("信号注册失败：%d\n", sig);
            return false;
        }
    }
    return true;
}
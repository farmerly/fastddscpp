#ifndef _COMMON_H_H_H
#define _COMMON_H_H_H

#include <signal.h>

// 注册信号处理回调函数
bool register_sig(void (*callback)(int));

#endif // _COMMON_H_H_H
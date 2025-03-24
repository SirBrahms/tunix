#ifndef __PUSH_HEADER__
#define __PUSH_HEADER__

#include <stddef.h>

/* Kernel Internal User Shell */
char current_cmd[128];
size_t cmd_index = 0;

int interpret();
void KIS();
void ls();
void isysr();
void cd();
void cat();

#endif

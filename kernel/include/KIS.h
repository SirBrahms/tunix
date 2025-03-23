#ifndef __PUSH_HEADER__
#define __PUSH_HEADER__

#include <stddef.h>

/* Kernel Internal User Shell */
char current_cmd[128];
size_t cmd_index = 0;

void interpret();
void p_main();
void ls();
void cat();
void isysr();

#endif


#ifndef COMMANDS_H
#define COMMANDS_H
#include "std_headers.h"
// using static global [] of cmds instead of copying from initial_cmds to dynamic array char**cmd_list (old implementation - old_main_using_dynamic_size_of_array_practice_.c)
const char *initial_cmds[] = {"-h","-help", "-v", "--version", "-ef", "-df"};
const size_t array_size = sizeof(initial_cmds) / sizeof(initial_cmds[0]);
/************************************************************************/
#endif

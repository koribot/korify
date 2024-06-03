#include "commands.h"
#include "is_valid_command.h"
bool is_valid_command(char *argv)
{
	for (size_t b = 0; b < array_size; b++)
	{
		if (strcmp(argv, initial_cmds[b]) == 0)
		{
			return true;
		}
	}
	return false;
}

#include "commands.h"
#include "isValidCommand.h"
/// @brief Validate input commands
/// @param argv
/// @return boolean
bool isValidCommand(char *argv)
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

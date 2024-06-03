#include "is_valid_path.h"
bool is_valid_path(const char *path)
{
	return access(path, F_OK) != -1;
}

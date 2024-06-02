
#include "getChar_input_and_convert_password_characters_to_int.h"
/// @brief get user input (encryption string) and turns it to int
/// @param password - expects a pointer to pointer to character char **password, pass with &password
/// @param size  - initial size of the password - pass by value
/// @param getChar - pass the getChar without * or & or ()
/// @param integer_value_of_password - int, pass it with &integer_value_of_password
/// @return returns 0 if success otherwise 1
int getChar_input_and_convert_password_characters_to_int(char **password, int size, int (*getcharfn)(void), int *integer_value_of_password)
{
	int len = 0;
	char character = getcharfn();
	char *temp;
	*password = malloc(size * sizeof(char));
	if (password == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		return 1;
	}
	// Todo: Separate this store al the values of characters first then calculate size so we can accurately allocate memory
	if (character == '\n')
	{
		printf("Input is empty\n");
		return 1;
	}
	while ((character) != '\n' && character != EOF)
	{
		if (len + 1 >= size)
		{
			temp = realloc(*password, size * sizeof(char));
			if (temp == NULL)
			{
				fprintf(stderr, "Memory reallocation failed\n");
				free(*password);
				exit(1);
				return 1;
			}
			*password = temp;
		}
		(*password)[len++] = character;
		character = getcharfn();
	}
	(*password)[len] = '\0';

	*integer_value_of_password = 0;
	for (int i = 0; i < len; i++)
	{
		*integer_value_of_password += (int)(*password)[i];
	}
	// printf("%i\n", *integer_value_of_password);
	// printf("password : %s\n", *password);
	free(*password);
	*password = NULL; // Prevent dangling pointer
	return 0;
}

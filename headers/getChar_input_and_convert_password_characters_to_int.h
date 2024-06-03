#ifndef GETCHAR_INPUT_AND_CONVERT_PASSWORD_CHARACTERS_TO_INT_H
#define GETCHAR_INPUT_AND_CONVERT_PASSWORD_CHARACTERS_TO_INT_H
#include "std_headers.h"
/// @brief get user input (encryption string) and turns it to int
/// @param char**password - expects a pointer to pointer to character char **password, pass with &password
/// @param size  - initial size of the password - pass by value
/// @param int(*getcharfn)(void) - pass the getChar without * or & or ()
/// @param int*integer_value_of_password - int, pass it with &integer_value_of_password
/// @return returns 0 if success otherwise 1
int getChar_input_and_convert_password_characters_to_int(char **password, int size, int (*getcharfn)(void), int *integer_value_of_password);
#endif 

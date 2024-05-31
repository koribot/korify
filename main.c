#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define PASSWORD_INITIAL_SIZE 100

// using static global [] of cmds instead of copying from initial_cmds to dynamic array char**cmd_list (old implementation - old_main_using_dynamic_size_of_array_practice_.c)
const char *initial_cmds[] = {"-help", "-v", "--version", "-ef", "-df"};
const size_t array_size = sizeof(initial_cmds) / sizeof(initial_cmds[0]);
/************************************************************************/

/// @brief Validate input commands
/// @param argv
/// @return boolean
bool isValid(char *argv)
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

bool isValidPath(const char *path)
{
    if (access(path, F_OK) != -1)
    {
        return true; // Path exists
    }
    else
    {
        return false; // Path does not exist or is invalid
    }
}

/// @brief get user input (encryption string) and turns it to int
/// @param password - expects a pointer to pointer to character char **password, pass with &password
/// @param size  - initial size of the password - pass by value
/// @param getChar - pass the getChar without * or & or ()
/// @param integer_value_of_password - int, pass it with &integer_value_of_password
/// @return returns 0 if success otherwise 1
int getChar_input_and_convert_password_characters_to_int(char **password, int size, int (*getcharfn)(void), int *integer_value_of_password)
{
    int len = 0;
    char character;
    char *temp;
    *password = malloc(size * sizeof(char));
    if (password == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    // Todo: Separate this store al the values of characters first then calculate size so we can accurately allocate memory
    while ((character = getcharfn()) != '\n' && character != EOF)
    {
        if (len + 1 >= size)
        {
            temp = realloc(*password, size * sizeof(char));
            if (temp == NULL)
            {
                fprintf(stderr, "Memory reallocation failed\n");
                free(temp);
                free(*password);
                exit(1);
                return 1;
            }
            *password = temp;
        }
        (*password)[len++] = character;
    }
    (*password)[len] = '\0';

    *integer_value_of_password = 0;
    for (int i = 0; i < len; i++)
    {
        *integer_value_of_password += (int)(*password)[i];
    }
    // printf("%i\n", *integer_value_of_password);
    // printf("password : %s\n", *password);
    if (*password != NULL)
    {
        free(*password);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        for (int x = 1; x < argc; x++)
        {
            if (isValid(argv[x]))
            {
                // printf("Command is valid: %s\n", argv[x]);
                if (strcmp(argv[x], "-ef") == 0)
                {
                    if (argv[x + 1] && strlen(argv[x + 1]) > 2)
                    {
                        if (isValidPath(argv[x + 1]))
                        {
                            FILE *file = fopen(argv[x + 1], "r");
                            FILE *outputFile = fopen("encrypted.txt", "w");
                            FILE *file2 = fopen("encrypted.txt", "r");
                            FILE *file3 = fopen("encrypted.txt", "r");
                            if (file == NULL || outputFile == NULL)
                            {
                                perror("Error opening file");
                                return EXIT_FAILURE;
                            }
                            else
                            {
                                int integer_value_of_passowrd;
                                char *password;
                                printf("File successfully loaded \n");
                                puts("------------------------------");
                                printf("Enter your encryption string: ");
                                int result = getChar_input_and_convert_password_characters_to_int(&password, PASSWORD_INITIAL_SIZE, getchar, &integer_value_of_passowrd);
                                puts("------------------------------");
                                if (result == 0)
                                {
                                    char ch;
                                    while ((ch = fgetc(file)) != EOF)
                                    {

                                        if (ch != '\n')
                                        {
                                            ch = (ch + integer_value_of_passowrd) % 95 + 32;
                                            fputc(ch, outputFile);
                                        }
                                        else
                                        {
                                            fputc(0, outputFile);
                                        }
                                        // printf("%c", ch+integer_value_of_passowrd);
                                    }
                                    printf("Encryption success \n");
                                }
                                puts("--------------");
                                fclose(outputFile);
                                if (fclose(file) != 0)
                                {
                                    perror("Error closing file");
                                    return EXIT_FAILURE;
                                }
                                if (file2 == NULL)
                                {
                                    printf("Cant open");
                                }
                                else
                                {
                                    char ch2;
                                    int decrypted_val;
                                    FILE *decryptedFile = fopen("decrypted.txt", "w");
                                    if (!decryptedFile)
                                    {
                                        perror("Error opening decrypted file");
                                        return EXIT_FAILURE;
                                    }
                                    while ((ch2 = fgetc(file3)) != EOF)
                                    {
                                        // ch2 = (ch2 - integer_value_of_passowrd - 32 + 95) % 95 + 32;
                                        decrypted_val = ch2 - 32 - integer_value_of_passowrd;
                                        while (decrypted_val < 0)
                                        {
                                            decrypted_val += 95; // Ensure the result is positive
                                        }

                                        if (ch2 == 0)
                                        {
                                            // putchar('\n');
                                            fputc('\n', decryptedFile);
                                        }
                                        else
                                        {
                                            char decrypted_ch = decrypted_val < 32 ? decrypted_val + 95 : decrypted_val < 127 ? decrypted_val
                                                                                                                              : decrypted_val - 95;
                                            // putchar((char)(decrypted_ch));
                                            fputc(decrypted_ch, decryptedFile);
                                        }
                                    }
                                    fclose(decryptedFile);
                                }

                                puts("------------------------");
                            }
                            fclose(file);
                            return EXIT_SUCCESS;
                        }
                        else
                        {
                            printf("Invalid or path does not exist: %s\n", argv[x + 1]);
                            break;
                        }
                        break;
                    }
                    else
                    {
                        printf("-gf (Get file) needs file directory");
                        break;
                    }
                }
            }
            else
            {
                printf("Invalid Command: %s\n", argv[x]);
                break;
                // Todo:
            }
        }
    }
    else
    {
        printf("No command is passed. Try using kori -help.\n");
        return 1;
    }

    return 0;
}

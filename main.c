#include "std_headers.h"
#include "encrypt.h"
#include "getChar_input_and_convert_password_characters_to_int.h"
#include "isValidCommand.h"


#define PASSWORD_INITIAL_SIZE 100

// not really checking if the path is valid, need to implement bettter way - research
bool isValidPath(const char *path)
{
	if (access(path, F_OK) != -1)
	{
		return true;
	}
	else
	{

		return false;
	}
}

// we need to use this in future
void str_to_int(char **_password_string, int *_int)
{
	for (int i = 0; i < strlen(*_password_string); i++)
	{
		*_int += (int)(*_password_string)[i];
	}
}

int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("No command is passed. Try using kori -help.\n");
		return 1;
	}

	for (int x = 1; x < argc; x++)
	{
		if (!isValidCommand(argv[x]))
		{
			printf("Invalid Command: %s\n", argv[x]);
			break;
		}

		// -ef command
		if (strcmp(argv[x], "-ef") == 0)
		{

			if (!(argv[x + 1] && strlen(argv[x + 1]) > 2))
			{
				printf("-gf (Get file) needs file directory");
				break;
			}

			if (!isValidPath(argv[x + 1]))
			{
				printf("Invalid or path does not exist: %s\n", argv[x + 1]);
				break;
			}

			if (!(argv[x + 2]))
			{
				printf("You need to provide output directory \n");
				printf("kori -ef %s (your encrypted_output_file path) \n", argv[x + 1]);
				printf("use . to specify current directory");
				break;
			}
			FILE *file = fopen(argv[x + 1], "r");
			if (file == NULL)
			{
				perror("Error opening file");
				return EXIT_FAILURE;
			}
			// char *default_file_name = "encrypted.txt";
			// char filename[1024];
			// sprintf(filename, "%s\\%s", argv[x+2], default_file_name);
			FILE *encrypted_output_file = fopen(argv[x + 2], "w");

			if (encrypted_output_file == NULL)
			{
				perror("| Error opening file -> ");
				printf("| encrypted_output_file path %s \n", argv[x + 2]);
				printf("| It does not automatically create folders but it does create files \n"); // need to have a function to create directory if not existing
				break;
				return EXIT_FAILURE;
			}

			int integer_value_of_passowrd;
			char *password;
			puts("------------------------------");
			printf("| File successfully loaded |\n");
			puts("------------------------------");

			puts("");
			printf("Enter your encryption string: ");
			int result = getChar_input_and_convert_password_characters_to_int(&password, PASSWORD_INITIAL_SIZE, getchar, &integer_value_of_passowrd);
			puts("------------------------------");
			if (result == 0)
			{
				int is_encryption_sucess = encrypt(file, &integer_value_of_passowrd, encrypted_output_file);
				fclose(encrypted_output_file);

				if (is_encryption_sucess == 1)
				{
					printf("Something went wrong check encrypt(): \n");
					break;
				}

				printf("| ** Encryption successful ** |\n");
				puts("------------------------------");
				puts("--------------------------------------------");
				printf("| Encrypted output file ->: %s |\n", argv[x + 2]);
				puts("--------------------------------------------");
			}
			if (fclose(file) != 0)
			{
				perror("Error closing file");
				return EXIT_FAILURE;
			}
			fclose(file);
			return EXIT_SUCCESS;
		}

		if (strcmp(argv[x], "-df") == 0)
		{
			if (!(argv[x + 1] && strlen(argv[x + 1]) > 2))
			{
				printf("-df (decrypt file) needs file directory");
				break;
			}
			if (!isValidPath(argv[x + 1]))
			{
				printf("Invalid or path does not exist: %s\n", argv[x + 1]);
				break;
		   }

			if (!(argv[x + 2]))
			{
				printf("You need to provide output directory \n");
				printf("kori -df %s (your encrypted_output_file path) \n", argv[x + 1]);
				printf("use . to specify current directory");
				break;
			}

			FILE *encrypted_source_file = fopen(argv[x + 1], "r");
			if (!encrypted_source_file)
			{
				perror("Error opening decrypted file");
				return EXIT_FAILURE;
			}
			puts("------------------------------");
			printf("| File successfully loaded |\n");
			puts("------------------------------");

			puts("");
			int _integer_value_of_password;
			char *_password;
			printf("Enter decrypting string: ");
			int result = getChar_input_and_convert_password_characters_to_int(&_password, PASSWORD_INITIAL_SIZE, getchar, &_integer_value_of_password);

			char ch2;
			int decrypted_val;
			FILE *decrypted_output_file = fopen(argv[x+2], "w");
			while ((ch2 = fgetc(encrypted_source_file)) != EOF)
			{
				// ch2 = (ch2 - integer_value_of_passowrd - 32 + 95) % 95 + 32;
				// printf("%c\n", ch2);
				decrypted_val = ch2 - 32 - _integer_value_of_password;
				while (decrypted_val < 0)
				{
					decrypted_val += 95; // Ensure the result is positive
				}

				if (ch2 == 0)
				{
					// putchar('\n');
					fputc('\n', decrypted_output_file);
					// printf("\n");
					continue;
				}
				
				if(ch2 == 9){
					fputc('\t', decrypted_output_file);
					continue;
				}
	
					char decrypted_ch = decrypted_val < 32 ? decrypted_val + 95 : decrypted_val < 127 ? decrypted_val
																																 					: decrypted_val - 95;
					// putchar((char)(decrypted_ch));
					fputc(decrypted_ch, decrypted_output_file);
				// printf("%c", decrypted_ch);
				
			}
			puts("");
			puts("---------------------------");
			printf("| Successfully Decrypted |\n");
			puts("---------------------------");
			fclose(decrypted_output_file);
			break;
		}
	}

	return 0;
}

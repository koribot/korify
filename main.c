#include "std_headers.h"
#include "encrypt.h"
#include "decrypt.h"
#include "getChar_input_and_convert_password_characters_to_int.h"
#include "isValidCommand.h"

#define PASSWORD_INITIAL_SIZE 100
#define KORIFY_CURRENT_VERSION "0.0.0"

// Todo: this is not actually checking if the path is valid
bool isValidPath(const char *path)
{
	return access(path, F_OK) != -1;
}

// This is not in used
void str_to_int(const char *_password_string, int *_int)
{
	for (int i = 0; i < strlen(_password_string); i++)
	{
		*_int += (int)_password_string[i];
	}
}

void print_korify_help_options(){
		printf("\nKorify Commands:\n\n");
		printf("- Help (-h)(-help):\n\n");
		printf("- Check korify version (-v)(-version):\n\n");
		printf("- Encrypt File (-ef):\n");
		printf("  Usage: ./kori -ef \"path to your source file\" \"path to your encrypted output file\"\n");
		printf("  Example: ./kori -ef main.txt encrypted.txt\n\n");
		printf("- Decrypt File (-df):\n");
		printf("  Usage: ./kori -df \"path to your encrypted source file\" \"path to your decrypted output file\"\n");
		printf("  Example: ./kori -df encrypted.txt decrypted.txt\n\n");
}


int main(int argc, char *argv[])
{
	if (argc <= 1)
	{
		printf("No command is passed. Try using kori -ef to encrypt file and -df to decrypt file.\n");
		print_korify_help_options();
		return 1;
	}

	for (int x = 1; x < argc; x++)
	{
		if (!isValidCommand(argv[x]))
		{
			printf("Invalid Command: %s\n", argv[x]);
			break;
		}

		if (strcmp(argv[x], "-ef") == 0)
		{
			// Handling encryption command
			if (argc < x + 3)
			{
				printf("-ef (Encrypt file) needs file path and output directory.\n");
				break;
			}

			if (!isValidPath(argv[x + 1]))
			{
				printf("Invalid or non-existent file path: %s\n", argv[x + 1]);
				break;
			}

			FILE *file = fopen(argv[x + 1], "r");
			if (!file)
			{
				perror("Error opening file");
				return EXIT_FAILURE;
			}

			char *password;
			int integer_value_of_password = 0;
			puts("------------------------------");
			printf("| File successfully loaded |\n");
			puts("------------------------------\n");

			printf("Enter your encryption string: ");
			int result = getChar_input_and_convert_password_characters_to_int(&password, PASSWORD_INITIAL_SIZE, getchar, &integer_value_of_password);
			puts("------------------------------");

			if (result == 1)
			{
				fclose(file);
				printf("Error getting encryption string.\n");
				return EXIT_FAILURE;
			}

			FILE *encrypted_output_file = fopen(argv[x + 2], "w");
			if (!encrypted_output_file)
			{
				perror("Error opening output file");
				fclose(encrypted_output_file);
				fclose(file);
				return EXIT_FAILURE;
			}

			int is_encryption_success = encrypt(file, &integer_value_of_password, encrypted_output_file, "");
			if (is_encryption_success == 1)
			{
				printf("Encryption failed.\n");
				fclose(encrypted_output_file);
				fclose(file);
				return EXIT_FAILURE;
			}

			printf("| ** Encryption successful ** |\n");
			puts("------------------------------");
			printf("| Encrypted output file: %s |\n", argv[x + 2]);
			puts("------------------------------");

			fclose(encrypted_output_file);
			fclose(file);
			return EXIT_SUCCESS;
		}

		if (strcmp(argv[x], "-df") == 0)
		{
			// Handling decryption command
			if (argc < x + 3)
			{
				printf("-df (Decrypt file) needs file path and output directory.\n");
				break;
			}

			if (!isValidPath(argv[x + 1]))
			{
				printf("Invalid or non-existent file path: %s\n", argv[x + 1]);
				break;
			}

			FILE *encrypted_source_file = fopen(argv[x + 1], "r");
			if (!encrypted_source_file)
			{
				perror("Error opening encrypted file");
				return EXIT_FAILURE;
			}

			char *password;
			int integer_value_of_password = 0;
			puts("------------------------------");
			printf("| File successfully loaded |\n");
			puts("------------------------------\n");

			printf("Enter your decryption string: ");
			int result = getChar_input_and_convert_password_characters_to_int(&password, PASSWORD_INITIAL_SIZE, getchar, &integer_value_of_password);
			puts("------------------------------");

			if (result == 1)
			{
				fclose(encrypted_source_file);
				printf("Error getting decryption string.\n");
				return EXIT_FAILURE;
			}

			FILE *decrypted_output_file = fopen(argv[x + 2], "w");
			if (!decrypted_output_file)
			{
				perror("Error opening output file");
				fclose(encrypted_source_file);
				return EXIT_FAILURE;
			}

			int is_decryption_success = decrypt(encrypted_source_file, &integer_value_of_password, decrypted_output_file, "");
			if (is_decryption_success == 1)
			{
				printf("Decryption failed.\n");
				fclose(decrypted_output_file);
				fclose(encrypted_source_file);
				return EXIT_FAILURE;
			}

			printf("| ** Decryption successful ** |\n");
			puts("------------------------------");
			printf("| Decrypted output file: %s |\n", argv[x + 2]);
			puts("------------------------------");

			fclose(decrypted_output_file);
			fclose(encrypted_source_file);
			return EXIT_SUCCESS;
		}

		if(strcmp(argv[x], "-h") == 0 || strcmp(argv[x], "-help") == 0){
			print_korify_help_options();
			break;
		}
		if(strcmp(argv[x], "-v") == 0 || strcmp(argv[x], "-version") == 0){
			printf("korify version -> %s\n", KORIFY_CURRENT_VERSION);
			break;
		}
	}

	return 0;
}

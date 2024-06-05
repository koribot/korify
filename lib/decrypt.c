#include "decrypt.h"

int decrypt(FILE *encrypted_source_file, int *integer_value_of_password, FILE *decrypted_output_file, char *mode)
{
	// Todo: figure out how to use variad -> for now use fixed arguments
	// va_list args;
	// va_start(args, decrypted_output_file);
	// char *testprint = va_arg(args, char *) ? "no debug" : "debug";
	// printf("Hello: %c\n", testprint);
	char ch2;
	int decrypted_val;
	// if(strcmp(testprint, "")==0){
	// 	printf("hey");
	// }
	while ((ch2 = fgetc(encrypted_source_file)) != EOF)
	{
		// ch2 = (ch2 - integer_value_of_passowrd - 32 + 95) % 95 + 32;
		// printf("%c\n", ch2);

		// this will show the ch prior to decrypting
		if (strcmp(mode, "debug-show-orig") == 0)
		{
			printf("%c", ch2);
		}
		decrypted_val = ch2 - 32 - *integer_value_of_password;
		while (decrypted_val < 0)
		{
			decrypted_val += 95;
		}

		if (ch2 == 0)
		{
			// putchar('\n');
			fputc('\n', decrypted_output_file);
			if (strcmp(mode, "debug") == 0 || strcmp(mode, "debug-show-orig") == 0)
			{
				printf("\n");
			}
			continue;
		}

		if (ch2 == 9)
		{
			fputc('\t', decrypted_output_file);
			if (strcmp(mode, "debug") == 0 || strcmp(mode, "debug-show-orig") == 0)
			{
				printf("\t");
			}
			continue;
		}

		char decrypted_ch = decrypted_val < 32 ? decrypted_val + 95 : decrypted_val < 127 ? decrypted_val
																																		: decrypted_val - 95;
		// putchar((char)(decrypted_ch));
		fputc(decrypted_ch, decrypted_output_file);
		// printf("%c", decrypted_ch);

		if (strcmp(mode, "debug") == 0)
		{
			printf("%c", decrypted_ch);
		}
	}
	// va_end(args);
	return 0;
}

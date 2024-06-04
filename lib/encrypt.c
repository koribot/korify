#include "encrypt.h"
int encrypt(FILE *file, int *integer_value_of_passowrd, FILE *encrypted_output_file, char *mode)
{
	// Todo: figure out how to use variad -> for now use fixed arguments
	// va_list args;
	// va_start(args, decrypted_output_file);
	// char *testprint = va_arg(args, char *) ? "no debug" : "debug";
	// printf("Hello: %c\n", testprint);
	// char *testprint;
	// if (va_arg(args, char *) == NULL) {
	// 	testprint = "no debug";
	// } else {
	// 	testprint = va_arg(args, char *);
	// }

	char ch;
	while ((ch = fgetc(file)) != EOF)
	{

		if (ch == '\n')
		{
			if (strcmp(mode, "debug") == 0)
			{
				printf("\n");
			}
			fputc(0, encrypted_output_file);
			continue;
		}
		if (ch == '\t')
		{
			if (strcmp(mode, "debug") == 0)
			{
				printf("\t");
			}
			fputc(9, encrypted_output_file);
			continue;
		}
		ch = (ch + *integer_value_of_passowrd) % 95 + 32;
		fputc(ch, encrypted_output_file);

		if (strcmp(mode, "debug") == 0)
		{
			printf("%c", ch);
		}
	}
	// va_end(args);
	return 0;
}

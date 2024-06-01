#include "encrypt.h"
int encrypt(struct _iobuf *file, int *integer_value_of_passowrd, struct _iobuf *encrypted_output_file, ...)
{
	va_list args;
	va_start(args, encrypted_output_file);
	char *testprint = va_arg(args, char *);

	char ch;
	while ((ch = fgetc(file)) != EOF)
	{

		if (ch == '\n')
		{
      fputc(0, encrypted_output_file);
      continue;
		}
    if(ch == '\t'){
      fputc(9, encrypted_output_file);
      continue;
    }
  	  ch = (ch + *integer_value_of_passowrd) % 95 + 32;
			fputc(ch, encrypted_output_file);

			if (strcmp(testprint, "print") == 0)
			{
				printf("%c", ch);
			}
		
		
	}
	va_end(args);
	return 0;
}

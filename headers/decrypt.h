#ifndef DECRYPT_H
#define DECRYPT_H
#include "std_headers.h"
int decrypt(struct _iobuf *file, int *integer_value_of_passowrd, struct _iobuf *encrypted_output_file, char *mode);
#endif 

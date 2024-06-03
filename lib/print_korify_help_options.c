#include "print_korify_help_options.h"
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
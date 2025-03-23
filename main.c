//------------------------------------------------------------------------------------------
// Конвертер ASCII Hex <-> Bin
// Мазаев М.И., 2025г.
//------------------------------------------------------------------------------------------
#include <stdint.h> 
#include <stdio.h>
#include <stdlib.h>

typedef enum 
{
    ERR_INVALID_NUMBER_OF_PARAMETERS,
    ERR_INVALID_PARAMETERS
} ERROR_Status;

void printMenu()
{
    printf("");
}

uint32_t convHexTobin(FILE *input, FILE *output)
{
    unsigned char byte;
    char hex[3];
    while (fscanf(input, "%2s", hex) == 1) {
        byte = (unsigned char)strtol(hex, NULL, 16);
        fwrite(&byte, sizeof(byte), 1, output);
    }
    return 0;
}

uint32_t convBinToHex(FILE *input, FILE *output)
{
    char bin = fgetc(input);
    while (bin != EOF) {
        fprintf(output, "%x", bin);
        bin = fgetc(input);
    }
}

int main(int argc, char *argv[])
{
    if (argc<2 || argc > 3) return ERR_INVALID_NUMBER_OF_PARAMETERS;
    
    if (strcmp(argv[1], "--help") || strcmp(argv[1], "-h"))
        printMenu();
    else if (strcmp(argv[1], "--HexToBin"))
            {
                FILE * input = fopen(argv[2], "rb");
                char outputFile = argv[2];
                strcat(argv[2], ".bin"); 
                FILE * output = fopen(output, "w"); 
                convHexTobin(input, output);
            }
    else if (strcmp(argv[1], "--BinToHex"))
            convBinToHex(argv[2]);
    else 
        {
            printf("ERROR");
            exit(EXIT_FAILURE);
        }
    // считывание аргументов из вызова
    // выбор конвертора на основе switch
    // работа конвертора
    return 0;
}
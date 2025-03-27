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

uint32_t convHexTobin(const char *inFile)
{

    FILE *input = fopen(inFile, "r");
    if (input == NULL)
        perror("Failed to open input file:");

    char outFile[sizeof(inFile) + 4];
    strcat(outFile, inFile);
    strcat(outFile, ".bin");
    FILE *output = fopen(outFile, "wb");
    if (input == NULL)
        perror("Failed to open output file:");

    unsigned char byte;
    char hex[3];
    hex[2] = '\0';
    hex[0] = fgetc(input);
    while (hex[0] != EOF)
    {
        if ((hex[0] < '0' || hex[0] > '9') && (hex[0] < 'a' || hex[0] > 'f') && (hex[0] < 'a' || hex[0] > 'f'))
        {
            hex[1] = fgetc(input);
            byte = (unsigned char)strtol(hex, NULL, 16);
            fwrite(&byte, sizeof(byte), 1, output);
        }
    }
    return 0;
}

uint32_t convBinToHex(const char *inFile)
{
    FILE *input = fopen(inFile, "rb");
    char outFile[sizeof(inFile) + 4];
    strcat(outFile, inFile);
    strcat(outFile, ".hex");
    FILE *output = fopen(outFile, "w");

    unsigned char byte;
    fread(&byte, sizeof(byte), 1, input);
    while (byte != EOF)
    {
        fprintf(output, "%02X", byte & 0xFF);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        printf("ERROR");
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "--help") || strcmp(argv[1], "-h"))
        printMenu();
    else if (strcmp(argv[1], "--HexToBin"))
        convHexTobin(argv[2]);
    else if (strcmp(argv[1], "--BinToHex"))
        convBinToHex(argv[2]);
    else
    {
        printf("Error: Invalid parameter\nTo get help use -h or --help");
        exit(EXIT_FAILURE);
    }
    return 0;
}
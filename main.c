//------------------------------------------------------------------------------------------
// Конвертер ASCII Hex <-> Bin
// Мазаев М.И., 2025г.
//------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printMenu()
{
    printf("HEX <-> BIN converter\n");
    printf("<util_name> [OPTION] [FILE]\n");
    printf(" -h --help\t-  get help on using the utility\n");
    printf(" --HexToBin\t-  convert HEX file to BIN file. After the parameter comes the /path/to/the/file/with/the/*.hex\n");
    printf(" --BinToHex\t-  convert BIN file to HEX file. After the parameter comes the /path/to/the/file/with/the/*.bin\n");
}

void convHexTobin(const char *inFile)
{

    FILE *input = fopen(inFile, "r");
    if (input == NULL)
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    char outFile[FILENAME_MAX] = {0};
    strcat(outFile, inFile);
    strcat(outFile, ".bin");
    FILE *output = fopen(outFile, "wb");
    if (output == NULL)
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    char hex[3];
    hex[2] = '\0';
    hex[0] = fgetc(input);
    while (hex[0] != EOF)
    {
        if ((hex[0] > '0' && hex[0] < '9') || (hex[0] > 'a' && hex[0] < 'f') || (hex[0] > 'A' && hex[0] < 'F'))
        {
            hex[1] = fgetc(input);
            if ((hex[1] > '0' && hex[1] < '9') || (hex[1] > 'a' && hex[1] < 'f') || (hex[1] > 'A' && hex[0] < 'F'))
            {
                unsigned char byte = (unsigned char)strtol(hex, NULL, 16);
                fwrite(&byte, sizeof(byte), 1, output);
            }
        }
        hex[0] = fgetc(input);
    }

    fclose(input);
    fclose(output);
}

void convBinToHex(const char *inFile)
{
    FILE *input = fopen(inFile, "rb");
    if (input == NULL)
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    char outFile[FILENAME_MAX] = {0};
    strcat(outFile, inFile);
    strcat(outFile, ".hex");
    FILE *output = fopen(outFile, "w");
    if (output == NULL)
    {
        perror("Failed to open input file");
        exit(EXIT_FAILURE);
    }

    int byte = fgetc(input);
    while (byte != EOF)
    {
        fprintf(output, "%02X", byte);
        byte = fgetc(input);
    }

    fclose(input);
    fclose(output);
}

void main(int argc, char *argv[])
{
    if (argc < 2 || argc > 3)
    {
        printf("Error: Invalid number of parameters\nTo get help use -h or --help");
        exit(EXIT_FAILURE);
    }

    if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h"))
        printMenu();
    else if (!strcmp(argv[1], "--HexToBin") && (strstr(argv[2], ".hex") - argv[2] == strlen(argv[2]) - 4))
    {
        convHexTobin(argv[2]);
        printf("Conversion completed\n");
    }
    else if (!strcmp(argv[1], "--BinToHex") && (strstr(argv[2], ".bin") - argv[2] == strlen(argv[2]) - 4))
    {
        convBinToHex(argv[2]);
        printf("Conversion completed\n");
    }
    else
    {
        printf("Error: Invalid parameter\nTo get help use -h or --help");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
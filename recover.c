#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// getfile size function head
int getFileSize(FILE *file);
const int BYTE = 512;
// defining the numbers to which the first three digits need to equal
const unsigned char BYTE1 = 255;
const unsigned char BYTE2 = 216;

// first three bytes 0xff, 0xd8, 0xff, last byte 0xe0,0xe1,... 0xef
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    // buffer = (int*)(malloc(sizeof(int)* size));
    int counter = 0;
    // open memory card
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Error opening file");
        return 1;
    }
    char *files;
    FILE *IMG = NULL;
    // Seek to the end of the file
    int size = getFileSize(f);
    unsigned char buffer[BYTE];
    bool new = false;
    memset(buffer, 0, BYTE);
    // read 512 bytes into a buffer ? maybe malloc?
    while (fread(buffer, sizeof(char), BYTE, f) == BYTE)
    {
        // switch statement to determine if its the start of a new file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            new = true;
        }
        if (new == true)
        {
            if (counter > 0)
            {
                fclose(IMG);
            }
            // make a new file
            files = malloc(sizeof(char) * 8);
            sprintf(files, "%03i.jpg", counter);
            if (files == NULL)
            {
                return 1;
            }
            // open the file
            IMG = fopen(files, "w");
            free(files);
            // check if file was succesfully opened
            if (IMG == NULL)
            {
                printf("New image file failed to open");
                return 1;
            }
            new = false;
            // increment a new
            counter++;
        }

        if (IMG != NULL)
        {
            fwrite(buffer, sizeof(unsigned char), BYTE, IMG);
        }
    }

    // if start of new jpeg copy to sprintf
    //       if first jpeg copy to jpeg file
    //       else close previous jpeg and make new sprintf
    // else already found jpeg
    //   keep reading
    // close any remaing files

    // need to figure out memory size
    fclose(f);
    fclose(IMG);
}

// function to get file size
int getFileSize(FILE *file)
{
    fseek(file, 0, SEEK_END);
    // Get the current file position (which is the size)
    int size = ftell(file);
    rewind(file);
    return size;
}

#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    string plain;
if (argv[1] == NULL)
{
    printf("Usage: ./caesar key\n");
    return 1;
}
    //if key is a positive integer continue
    int x = 0;

    while (x < argc)
    {
        for (int i = 0; i < argc; i++)
        {
            int n = strlen(argv[i]);
            if (isalpha(argv[x][i]))
        {
            printf("Usage: ./caesar key\n");
            x += argc + x;
            return 1;
        }
           if ((argv[x][i]) == ' ')
           {
            printf("Usage: ./caesar key\n");
            x += argc + x;
            return 1;
           }
        }
        x++;
    }

        for (int i = 0, n= strlen(argv[1]); i < n; i++)
        {
        if (isdigit(argv[1][i]))
            {
                plain = get_string("plaintext: ");
                i = n+= i;
            }
            else
    {
        printf("Usage: ./caesar key\n");
        return 1;
         }
        }

    //reprompt the main question
    if (argc > 2 || argc == 0 || argc == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // converts this numeric string into an int value key
int key = atoi(argv[1]);
// sets a loop to change the characters in the OT based on the key value
while (key > 26)
{
    key -= 26;
}
for (int i = 0, k = key, n = strlen(plain); i < n; i++)
{
if (i == 0)
{
    printf("ciphertext: ");
}
    char lower = tolower(plain[i]);
    char upper = toupper(plain[i]);
// if it isnt a punctuation or etc change according to key
    if (isalpha(plain[i]))
    {
        char letter = plain[i];
        if (letter == lower)
        {
                char print = plain[i] + k;
            if (print >= 97 && 122 >= print)
         {
            printf("%c", print);
            }
            else if (print <= 97 || 122 <= print)
            {
                printf("%c", print - 26);
            }
        }
        if (letter == upper)
        {
        char print = plain[i] + k;
            if (print >= 65 && 90 >= print)
         {
            printf("%c", print);
            }
            else if (print <= 65 || 90 <= print)
            {
                printf("%c", print - 26);
            }
        }
    }
    // else print out just spaces or whatever was there originally
    else if (plain[i] == ' ')
    {
         printf(" ");
    }
    else
    {
         printf("%c", plain[i]);
    }


}
printf("\n");
}



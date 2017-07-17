#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    //make sure user only entered command line and 1 arugment
    if (argc != 2)
    {
        printf("Try again\n");
        return 1;
    }
    
    //put key into int k
    int k = atoi(argv[1]);
    
    //check that int is not negative
    if (k < 0)
    {
        printf("Try again\n");
        return 1;
    }
    else
    {
        //get code from user to encrypt
        printf("plaintext: ");
        string code = get_string ();
        
        printf("ciphertext: ");
        for (int i = 0, n = strlen(code); i < n; i++)
            {
                
                //check if characters in string are upper or lower case and convert
                if islower(code[i])
                    printf("%c", (((code[i] + k) - 97) % 26) + 97);
                else if isupper(code[i])
					printf("%c", (((code[i] + k) -65) % 26) + 65);
                //checking if characters are neither, then printing its value if neither
                else
					printf("%c", code[i]);
                
            }
			printf("\n");
			return 0;
    }
}
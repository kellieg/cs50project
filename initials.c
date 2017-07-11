#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //getting name from user
    string s = get_string();
    
    //print the first initial from the name with uppercase
    printf("%c", toupper(s[0]));
    
    //Finding the second or last initial and printing with uppercase
    for(int i = 0, n = strlen(s); i < n; i++)
    {
        if(s[i] == ' ' && s[i + 1] != '\0')
        printf("%c", toupper(s[i + 1]));
        i++;
    }
    //finding if there is a 3rd initial to print and printing with uppercase
    for(int j = 1, n = strlen(s); j < n; j++)
    {
        if(s[j] == ' ' && s[j + 1] != '\0')
        printf("%c", toupper(s[j + 1]));
        j++;
    }
  printf("\n");
}

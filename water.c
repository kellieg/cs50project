#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Minutes: ");
    int minutes = get_int();
    if (minutes < 0)
    {
        printf("Negative number, retry\n");
         
    }
    else
    printf("Bottles: %i \n", minutes * 12);
}
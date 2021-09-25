#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("View the available list of case studies \n");
        printf("View the content of a file on the terminal\n");
        printf("Download an available case study\n");
        
    }

    if (argc == 2)
    {
        printf("The argument supplied is %s\n", argv[1]);
    }
    else if (argc > 2)
    {
        printf("Too many arguments supplied.\n");
    }
    else
    {
        printf("One argument expected.\n");
    }
    printf("argc %d \n", argc);
}
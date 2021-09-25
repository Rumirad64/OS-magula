#include <stdio.h>
#include <string.h>

char shared_location[] = "shared folder/";

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("View the available list of case studies  :   viewall\n");
        printf("Upload a new case study                  :   upload <filename>\n");
        printf("Download an available case study         :   download <filename>\n");
        printf("Delete a case study                      :   delete <filename>\n");
        return 0;
    }

    if (argc == 2) //? Single argument provided
    {
        printf("Single argument provided \n");
        printf("argument -> %s \n", argv[1]);
        if (strcmpi(argv[1], "viewall") == 0) //! Viewall function
        {
            puts("In viewall");
            FILE *file_pointer;
            file_pointer = fopen(strcat(shared_location, "lock"), "w+");
            fprintf(file_pointer, "This is testing for fprintf...\n");
            fclose(file_pointer);
        }
    }
    else if (argc == 3) //? Two argument provided
    {
        printf("Two argument provided \n");
        printf("argument -> %s , %s \n", argv[1] , argv[2]);
        if (strcmpi(argv[1], "download") == 0) //! Download function
        {
            puts("In download");
            FILE *file_pointer;
            file_pointer = fopen(strcat(shared_location, "lock"), "w+");
            fprintf(file_pointer, "This is testing for fprintf...\n");
            fclose(file_pointer);
        }
    }

    printf("argc %d \n", argc);
}
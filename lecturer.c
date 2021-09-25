#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>

bool IsOccupied();

char shared_location[] = "shared folder/";

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("View the available list of case studies  :   viewall\n");
        printf("Upload a new case study                  :   upload <filename>\n");
        printf("Download an available case study         :   download <filename>\n");
        printf("Delete a case study                      :   delete <filename>\n");
        IsOccupied();
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
        printf("argument -> %s , %s \n", argv[1], argv[2]);
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

bool IsOccupied()
{
    FILE *file_pointer;
    char msg[20];
    file_pointer = fopen("shared folder/lock", "r");
    fscanf(file_pointer, "%s", msg);
    printf("Lock status ->  %s \n", msg);
    fclose(file_pointer);
    if (strcmp(msg, "occupied") == 0)
    {
        return true;
    }
    else if (strcmp(msg, "available") == 0)
    {
        return false;
    }
    else
    {
        printf("lock file corrupted \n");
        return true;
    }
}
void viewAll()
{
    DIR *d;
    struct dirent *dir;
    char path[1000] = "shared folder/contents/";
    d = opendir(path);
    char full_path[1000];
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //Condition to check regular file.
            if (dir->d_type == DT_REG)
            {
                full_path[0] = '\0';
                strcat(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, dir->d_name);
                printf("%s\n", full_path);
            }
        }
        closedir(d);
    }
}
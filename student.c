#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>

bool IsOccupied();
void viewAll();
void download(char filename[]);
void view_on_terminal(char filename[]);
void acquireLock();
void releaseLock();
char shared_location[] = "shared folder/";

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("View the available list of case studies     :   viewall\n");
        printf("View the content of a file on the terminal  :   view <filename>\n");
        printf("Download an available case study            :   download <filename>\n");
        return 0;
    }

    if (argc == 2) //? Single argument provided
    {
        printf("Single argument provided \n");
        printf("argument -> %s \n", argv[1]);
        if (strcmp(argv[1], "viewall") == 0) //! Viewall function
        {
            puts("In viewall");
            if(IsOccupied())
			{
				puts("Cant access directory ! Someone is using it \n");
			}
			else{
				acquireLock();
				viewAll();
				releaseLock();
			}
        }
    }
    else if (argc == 3) //? Two argument provided
    {
        printf("Two argument provided \n");
        printf("argument -> %s , %s \n", argv[1], argv[2]);
        if (strcmp(argv[1], "download") == 0) //! Download function
        {
            puts("In download");
            if(IsOccupied())
			{
				puts("Cant access directory Someone is using it \n");
			}
			else{
				acquireLock();
				download(argv[2]);
				releaseLock();
			}
        }

		if (strcmp(argv[1], "view") == 0) //! View function
        {
            puts("In view <filename> ");
            if(IsOccupied())
			{
				puts("Cant access directory Someone is using it \n");
			}
			else{
				acquireLock();
				view_on_terminal(argv[2]);
				releaseLock();
			}
        }
    }
}

bool IsOccupied(){
    FILE *file_pointer;
    char msg[20];
    file_pointer = fopen("shared folder/lock", "r");
    fscanf(file_pointer, "%s", msg);
    printf("Lock status ->  %s \n", msg);
    fclose(file_pointer);
    if (strcmp(msg, "occupied") == 0){
        return true;
    }
    else if (strcmp(msg, "available") == 0){
        return false;
    }
    else{
        printf("lock file corrupted \n");
        return true;
    }
}
void viewAll(){
    DIR *d;
    struct dirent *dir;
    char path[1000] = "shared folder/contents/";
    d = opendir(path);
    char full_path[1000];
    if (d){
        while ((dir = readdir(d)) != NULL){
            //Condition to check regular file.
            if (dir->d_type == DT_REG){
                full_path[0] = '\0';
                strcat(full_path, dir->d_name);
                printf("%s\n", full_path);
            }
        }
        closedir(d);
    }
}

void view_on_terminal(char filename[])
{
	char path[] = "shared folder/contents/";
	strcat(path , filename);
	execl("/bin/cat" ,"cat" , path , (char *)0);
}

void download(char filename[])
{
	printf("Downloading file -> %s \n", filename);
	char path[] = "shared folder/contents/";
	strcat(path , filename);
	execl("/bin/cp", "-i", "-p",path , filename, (char *)0);
	printf("Downloaded file -> %s \n", filename);
}

void acquireLock(){
	FILE *file_pointer1;
    file_pointer1 = fopen("shared folder/lock", "w");
    fprintf(file_pointer1,"%s","occupied");
    printf("Lock acquired \n");
    fclose(file_pointer1);
    
}

void releaseLock(){
	FILE *file_pointer2;
    file_pointer2 = fopen("shared folder/lock", "w");
    fprintf(file_pointer2,"%s","available");
    printf("Lock released \n");
    fclose(file_pointer2);
    
}
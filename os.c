#include <stdio.h>
#include <stdlib.h> // For exit()
#include <pthread.h>
#include <stdbool.h>
#define NUM_THREADS 5

int rownumber = 1;
volatile bool Isreading = false;  //To check a thread is reading or not
volatile bool keepreading = true; // to check a thread reached end of the file
FILE *file;                       //dataset and ouput files as global file pointers
FILE *outfile;

void *readfile(void *threadid)
{
  long tid;
  tid = (long)threadid;
  int a, b, c = 0;    
          // to store 3 int from file
  while (keepreading == true) //keep checking someone reached end of the file
  {
    if (keepreading == false) //if end of the file,  terminate thread
    {
      pthread_exit(NULL);
    }

    if (Isreading) // if a thread is currently reading jump to beginning
    {
      continue; //jump to beginning
    }
    else //if file is free to read
    {
      if (!feof(file)) //working thread is checking end of the or not
      {
        Isreading = true; //to flag a thread is reading the file to others
        //start of critical section
        //read file and compute avg and print to output file
        fscanf(file, "%d,%d,%d", &a, &b, &c);
        printf("%d %d %d \n ", a, b, c);
        double avg = (a + b + c) / 3.0;

        fprintf(outfile, "%d %d %d \t AVG -> %f  \n", a, b, c, avg);
        //end of critical section
        Isreading = false;
        continue;
      }
      else //if working thread detect end of the file
      {
        puts("file end");
        keepreading = false; //flag to others , file is over
        Isreading = false;
        fclose(file); //close the file and exit
        break;
      }
    }
  }
}

int main()
{
  file = fopen("dataset.txt", "r"); //opening files
  outfile = fopen("output.txt", "a");

  pthread_t threads[NUM_THREADS];

  int i;
  for (i = 0; i < NUM_THREADS; i++)
  { //thread creation
    printf("main() : creating thread, -> %d \n", i);
    pthread_create(&threads[i], NULL, readfile, (void *)i);
  }
  i = 0;
  for (i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(threads[i], NULL); //wait all threads to finish their work
  }
  return 0;
}

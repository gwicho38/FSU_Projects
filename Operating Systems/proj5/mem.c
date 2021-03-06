/*                       compile with:                                  */
/* gcc -std=c99 -Wall -Wextra -D_XOPEN_SOURCE=700 -o trans trans.c -lrt */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>

#define PARENT_READ_END      0
#define PARENT_WRITE_END     1
#define CHILD_READ_END       0
#define CHILD_WRITE_END      1
#define BUFFER_SIZE          25

int main(int argc, char *argv[]){

  const int SIZE = 4096;
  const char *name = "bk15b_cop4610";
  int shm_fd;
  void *ptr;

  char buffer[4096];
  char read_msg[20];
  char write_msg[10];
  int var1 = -1;
  int var2;

  char astr[5], bstr[5];
  char finstr[25];
  int block_number = 1;
  int block_size = 0;
  int *message0 = "Studying ";

  if(argc < 3 || argc > 3 ){
    fprintf(stderr,"Wrong amount of command line arguments\n");
    exit(1);
  }

  /* open input file */
  FILE *fp = fopen(argv[1], "rb");

  if(fp == NULL){
    fprintf(stderr,"Error opening input file\n");
    exit(1);
  }

  /* open output file */
  FILE *wp = fopen(argv[2], "w");

  if(wp == NULL){
    fprintf(stderr,"Error opening output file\n");
    exit(1);
  }
 

  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "Fork failed");
    exit(1);
  }

  if (pid > 0) {  /* parent process */
    
    /* open the shared memory segment */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    
    /* configure the size of the shared memory segment */
    ftruncate(shm_fd,SIZE);

    /* now map the shared memory segment in the address space of the process  */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED){
      fprintf(stderr, "Parent: Map failed %s\n", strerror(errno));
      exit(1);
    }

      /* Write to the shared memory  */
      sprintf(ptr, "%s", message0);
      ptr += strlen(message0);

  }

  /* child process */
  else { 

    //    printf("CHILD PROCESS STARTED\n");
   
    /*read from shared memory*/
    
    /* open the shared memory segment */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
      fprintf(stderr,"shared memory failed\n");
    exit(1);
    }

    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
      printf("Child: Map failed\n");
    exit(-1);
    }

    sprintf(buffer, "%s", (char *)ptr);

    /*write to output file*/
    fwrite(buffer, 1, strlen(buffer)+1, wp);

      /* remove the shared memory segment */
      if (shm_unlink(name) == -1) {
        fprintf(stderr,"Error removing %s\n",name);
        exit(1);
      }
    }

  return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void getHeight(int *h){
  printf("Height (max. 10): ");
  scanf("%d",h);
  if(*h>10)
    *h = 10;
  printf("\n");
}

void createFileChild(int *pid){
  char filename[70];
  sprintf(filename, "/tmp/process_example/%d.txt", *pid);
  FILE *fp;
  fp = fopen(filename, "w+");
  fprintf(fp, "%d", rand()%100);
  fclose(fp);
}

void createFileParent(int *pid, int *childPid){
  char childFilename[70];
  sprintf(childFilename, "/tmp/process_example/%d.txt", *childPid);
  char filename[70];
  sprintf(filename, "/tmp/process_example/%d.txt", *pid);
  FILE *fp;
  fp = fopen(childFilename, "r");
  int c;
  fscanf(fp, "%d", &c);
  fclose(fp);
  printf("child:%d\n",c);
  int p = 0;
  if(access(filename, F_OK) != -1){
    fp = fopen(filename, "r");
    fscanf(fp, "%d", &p);
    fclose(fp);
  }
  printf("parent:%d\n",p);
  fp = fopen(filename, "w");
  fprintf(fp, "%d", c+p);
  fclose(fp);
  printf("parent + child:%d\n",c+p);
  printf("==================\n");
}

void createProcess(){
  pid_t pid;
  pid = fork();
  if(pid>0){
    // parent
    wait(NULL);
    int _pid = getpid();
    //printf("PARENT---%d child_pid:%d\n", _pid, pid);
    createFileParent(&_pid, &pid);
  }else if(pid==0){
    // child
    int _pid = getpid();
    //printf("CHILD---%d\n", _pid);
    createFileChild(&_pid);
  }else{
    // error
  }
}

int main(){
  time_t t;
  srand((unsigned)time(&t));
  int h;
  getHeight(&h);
  for(;h>=0;h--){
    //printf("%d", h);
    createProcess();
  }
}

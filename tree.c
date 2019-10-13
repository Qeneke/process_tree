#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void getHeight(int *h){
  printf("Height: ");
  scanf("%d",h);
  printf("\n");
}

void createFileChild(int *pid){
  char filename[70];
  sprintf(filename, "/tmp/process_example/%d_child.txt", *pid);
  FILE *fp;
  fp = fopen(filename, "w+");
  fprintf(fp, "%d", rand()%50);
  fclose(fp);
}

void createFileParent(int *pid, int *childPid){
  char childFilename[70];
  sprintf(childFilename, "/tmp/process_example/%d_child.txt", *childPid);
  char filename[70];
  sprintf(filename, "/tmp/process_example/%d_parent.txt", *pid);
  FILE *fp;
  fp = fopen(childFilename, "r");
  int c;
  fscanf(fp, "%d", &c);
  fclose(fp);
  int p = 0;
  if(access(filename, F_OK) != -1){
    fp = fopen(filename, "r");
    fscanf(fp, "%d", &p);
    fclose(fp);
  }
  fp = fopen(filename, "w");
  fprintf(fp, "%d", c+p);
  fclose(fp);
}

void createProcess(){
  pid_t pid;
  pid = fork();
  if(pid>0){
    // parent
    wait(NULL);
    int _pid = getpid();
    printf("PARENT---%d child_pid:%d\n", _pid, pid);
    createFileParent(&_pid, &pid);
  }else if(pid==0){
    // child
    wait(NULL);
    int _pid = getpid();
    printf("CHILD---%d\n", _pid);
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
  for(;h>0;h--){
    printf("%d", h);
    createProcess();
  }
}

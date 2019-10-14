/* thanks, sadi evren seker (http://sadievrenseker.com) */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void getHeight(int *h)
{
  printf("Height (max. 12): ");
  scanf("%d", h);
  if (*h > 12)
    *h = 12;
  printf("\n");
}

void leaf()
{
  char filename[15];
  sprintf(filename, "%d.tmp", getpid());
  FILE *fp = fopen(filename, "w");
  srand(getpid());
  fprintf(fp, "%d", rand() % 100);
  fclose(fp);
}

int parent(int pid, int pid2)
{
  wait(NULL);
  char filename[15];
  sprintf(filename, "%d.tmp", pid);
  char filename2[15];
  sprintf(filename2, "%d.tmp", pid2);
  char filename3[15];
  sprintf(filename3, "%d.tmp", getpid());
  FILE *fp1, *fp2, *fp3;
  fp1 = fopen(filename, "r");
  fp2 = fopen(filename2, "r");
  int left, right;
  fscanf(fp1, "%d", &left);
  fscanf(fp2, "%d", &right);
  fclose(fp1);
  fclose(fp2);
  fp3 = fopen(filename3, "w");
  fprintf(fp3, "%d", left + right);
  fclose(fp3);
  printf("parent(%d): %d, left(%d): %d, right(%d): %d\n", getpid(), left + right, pid, left, pid2, right);
}

void create_tree(int height)
{
  if (height == 0)
  {
    leaf();
    return;
  }
  int pid = fork();
  if (pid > 0)
  {
    int pid2 = fork();
    if (pid2 > 0)
    {
      //parent
      wait(NULL);
      printf("parent: %d, c1: %d, c2: %d\n", getpid(), pid, pid2);
      fflush(stdout);
      parent(pid, pid2);
    }
    else if (pid2 == 0)
    {
      // child1
      create_tree(--height);
    }
  }
  else if (pid == 0)
  {
    // child2
    create_tree(--height);
  }
}

int main()
{
  int h;
  getHeight(&h);
  create_tree(h);
}

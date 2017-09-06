#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
int main()
{
  pid_t fpid;
  int *pi;
  int count;
  int *pmmapprivate,*pmmapshared;
  pi = (int *)malloc(sizeof(int));
  if(!pi)
  {
    printf("can't malloc\n");
    return 0;
  }
  pmmapprivate = (int *)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_PRIVATE,-1,0);
  if(pmmapprivate<=0)
  {
	free(pi);
	printf("can't mmap private\n");
	return 0;
  }
  pmmapshared = (int *)mmap(NULL,4096,PROT_READ|PROT_WRITE,MAP_ANONYMOUS|MAP_SHARED,-1,0);
  if(pmmapshared<=0)
  {
	free(pi);
	munmap(pmmapprivate,4096);
	printf("can't mmap shared\n");
	return 0;
  }
  count=0;
  *pi=222;
  *pmmapprivate=444;
  *pmmapshared=666;
  fpid = fork();
  if(fpid < 0)
	printf("fork failed\n");
  else if(fpid==0)
  {
	printf("child process, pid=%d\n",getpid());
	count=1;
	*pi=333;
	*pmmapprivate=555;
	*pmmapshared=777;
	printf("c:count=%d,*pi=%d,*pmmappri=%d,*pmmapsha=%d\n",count,*pi,*pmmapprivate,*pmmapshared);
  }
  else{
	wait(NULL);
	printf("parent process,pid=%d\n",getpid());
	printf("p:count=%d,*pi=%d,*pmmappri=%d,*pmmapsha=%d\n",count,*pi,*pmmapprivate,*pmmapshared);

  }
  free(pi);
  munmap(pmmapprivate,4096);
  munmap(pmmapshared,4096);
 
  return 0;

}

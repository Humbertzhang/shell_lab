#include "csapp.c"

int main()
{
    pid_t pid;
    
    if((pid=Fork())==0)
    {
        printf("Kill!\n");
        Kill(pid,SIGKILL);
        printf("control should never reach here!\n");
        exit(0);
    }
    
    Pause();
    printf("I am parent and i won't be printed.\n");
    exit(0);
}

#include "csapp.c"

int main()
{
    pid_t pid;
    if((pid=Fork())==0){
        printf("In child: %d\n",pid);
        exit(0);
    }else{
        printf("In Father: %d\n",pid);
        sleep(1000);
    }
}

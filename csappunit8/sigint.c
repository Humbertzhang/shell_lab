#include "csapp.c"

void sigint_handler(int sig)
{
    printf("Caught SIGINT!\n");
    exit(0);
}
int main()
{
    /* Install the SIGINT handler */
    /* Let SIGINT signal redirect to sigint_handler function */
    if(signal(SIGINT,sigint_handler)==SIG_ERR)
        unix_error("signal error\n");

    pause();
    
    return 0;
}

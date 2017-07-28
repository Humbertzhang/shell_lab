#include "csapp.c"


unsigned int snooze(unsigned int secs)
{
    unsigned int count = sleep(secs);
    printf("\nSlept for %d of %d secs\n",secs-count,secs);
    return count;
}

void sigint_handler(int sig)
{
    Sio_puts("Caught SIGINT!\n");
    return;
}

int main(int argc,char *argv[])
{
    unsigned int sec = 0;
    if(argc == 2){
        sec = atoi(argv[1]);
    }

    if(signal(SIGINT,sigint_handler)==SIG_ERR)
        unix_error("signal error\n");

    snooze(sec);
    exit(0);
}
/* 在　ctrl + c时，调用signal函数，因为默认行为改成了sigint_handler，所以调用sigint_handler函数，直接返回，返回到signal后，开始停止snooze.
首先停止sleep函数，返回还剩多长sleep时间给count,然后print信息，return,停止进程,回到main函数，继续进行完剩下的再停止．
故停止只是立刻停止了sleep函数，sleep之后的还会进行
可能是因为在按ctrl+c时正好是sleep函数在进程中运行，故直接停止的sleep
*/


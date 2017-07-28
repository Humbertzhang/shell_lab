#include <csapp.h>

int main(int argc,char *argv[],char *envp[])
{
    int i=0;
    printf("\nCommand Line Argument:\n");
    for(i;i<argc;i++)
        printf("argv[%d]:%s\n",i+1,argv[i]);
    printf("\nEnvironment Variables:\n");
    for(i=0;envp[i]!=NULL;i++)
        printf("envp[%d]:%s\n",i+1,envp[i]);
    return 0;
}

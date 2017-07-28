#include "csapp.c"

#define MAXARGS 128

void eval(char *cmdline);
int parseline(char *buf,char **argv);
int builtin_command(char **argv);

int main()
{
    char cmdline[MAXLINE];

    while(1)
    {
        /* Read */
        printf(">");
        Fgets(cmdline,MAXLINE,stdin);
        if(feof(stdin))
            exit(0);

        /* Evaluate */
        eval(cmdline);
    }
    
}

/* eval - Evaluate a command line */

void eval(char *cmdline)
{
    char *argv[MAXARGS];
    char buf[MAXARGS];
    int bg; /* Check should the job run in background Or not */ 
    pid_t pid;

    strcpy(buf,cmdline);
    bg = parseline(buf,argv);
    if(argv[0] == NULL)   /*Ingore empty lines */
        return;  

    if(!builtin_command(argv)){

        if(pid = Fork()==0){   /*Let child process run user job */
            if(execve(argv[0],argv,environ) < 0){
                printf("%s:Command Not Found.\n",argv[0]);
                exit(0);
            }
        }
        
        if(!bg){
            int status;
            if(waitpid(pid,&status,0)<0)
                unix_error("waitfg:waitpid error");
        }
        else
            printf("%d %s",pid,cmdline);
        
    }
    
    return;

}

/* if first arg is a builtin command, run it and return True */
int builtin_command(char **argv)
{
    if(!strcmp(argv[0],"quit"))
        exit(0);
    if(!strcmp(argv[0],"&"))
        return 1;
    
    return 0;
}


/* parseline - Parse the command line and build the argv array */
int parseline(char *buf,char **argv)
{
    char *delim;
    int argc;
    int bg;

    buf[strlen(buf) - 1] = ' ';  /* Replace trailing '\n' with space */
    while(*buf && (*buf == ' ')) /* Ignore leading space */
        buf++;
    /* Build the argv list */
    argc = 0;
    while((delim = strchr(buf,' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while(*buf && (*buf == ' ')) /*Ignore space */
            buf++;
    }

    argv[argc] = NULL;

    if(argc == 0) /* Ignore blank line */
        return 1;

    /*check if job should run in background */
    if((bg = (*argv[argc-1] == '&'))!=0)
        argv[--argc] = NULL;

    return bg;
}















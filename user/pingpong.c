#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
mian(int argc, char *argv[]){
    int p1[2], p2[2];
    // creat  pipes
    int rc1 = pipe(p1);     // parent -> child
    int rc2 = pipe(p2);     // child ->parent
    
    if(rc1 < 0 || rc2 < 0){
        printf("pipe ERROR!\n");
        exit(-1);
    }

    int pid = fork();
    char buf[20];

    if(pid < 0){
            printf("fork ERROR!\n");
            exit(-1);
        }
        else if(pid == 0){    // child

            close(p1[1]);   // parent -> child
            read(p1[0], buf, sizeof(buf));

            close(p2[0]);   // child ->parent
            write(p2[1],"pong", 4);

            printf("%d: received %s\n", getpid(), buf);

            exit(0);
        }
        else{   // parent

            close(p1[0]);   // parent -> child
            write(p1[1],"ping", 4);
            
            close(p2[1]);   // child ->parent
            read(p2[0],buf, sizeof(buf));

            wait(0);    // wait for child process
            printf("%d: received %s\n", getpid(), buf);

            exit(0);
            
        }

    exit(0);
}
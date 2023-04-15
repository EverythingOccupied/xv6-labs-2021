#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[]){
    // when the number of parameters(argv) is wrong, printf the error message
    if(argc !=2 ){
        printf("Error: please usage sleep <times>\n");
        exit(1);
    }
    sleep(atoi(argv[1]));
    exit(0);
}
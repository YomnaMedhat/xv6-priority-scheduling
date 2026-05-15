#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main()
{
    int pid = fork();

    if(pid < 0){
        printf("fork failed\n");
        exit(1);
    }

    setpriority(getpid(), 5);

    if(pid == 0){
        setpriority(getpid(), 5);

        for(int i = 0; i < 20; i++){
            printf("Child process iteration %d\n", i);
        }

        exit(0);
    }

    for(int i = 0; i < 20; i++){
        printf("Parent process iteration %d\n", i);
    }

    wait(0);

    printf("priority_same test finished\n");

    exit(0);
}

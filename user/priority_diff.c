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

    if(pid == 0){
        // HIGH priority child
        setpriority(getpid(), 8);

        for(int i = 0; i < 20; i++){
            printf("[HIGH] pid=%d iteration=%d\n", getpid(), i);
        }

        exit(0);
    }

    // LOW priority parent
    setpriority(getpid(), 2);

    for(int i = 0; i < 20; i++){
        printf("[LOW] pid=%d iteration=%d\n", getpid(), i);
    }

    wait(0);

    printf("priority_diff test finished\n");
    exit(0);
}

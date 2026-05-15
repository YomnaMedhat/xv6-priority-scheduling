#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main()
{
    int r1, r2, r3, r4;

    r1 = setpriority(getpid(), -5);
    printf("Setting negative priority returned: %d\n", r1);

    r2 = setpriority(getpid(), 100);
    printf("Setting very high priority returned: %d\n", r2);

    r3 = setpriority(9999, 5);
    printf("Setting priority for invalid pid returned: %d\n", r3);

    r4 = setpriority(getpid(), 5);
    printf("Setting valid priority returned: %d\n", r4);

    printf("priority_edge test finished\n");

    exit(0);
}

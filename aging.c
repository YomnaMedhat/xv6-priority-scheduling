#include <stdio.h>

#define MAX 10

#define READY 0
#define RUNNING 1
#define FINISHED 2

#define MIN_PRIORITY 1
#define AGING_LIMIT 3

typedef struct {
    int pid;
    int priority;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int totalWait;
    int state;
} Process;

typedef struct {
    int pid;
} Gantt;

int n;
Gantt chart[100];
int gc = 0;

void addGantt(int pid) {
    chart[gc++].pid = pid;
}

void applyAging(Process p[]) {

    for (int i = 0; i < n; i++) {

        if (p[i].state == READY) {

            p[i].waitingTime++;
            p[i].totalWait++;

            if (p[i].waitingTime >= AGING_LIMIT) {

                int old = p[i].priority;

                p[i].priority--;

                if (p[i].priority < MIN_PRIORITY)
                    p[i].priority = MIN_PRIORITY;

                p[i].waitingTime = 0;

                printf("[AGING] P%d %d -> %d\n",
                       p[i].pid, old, p[i].priority);
            }

            if (p[i].totalWait >= 15) {
                printf("[STARVATION] P%d\n", p[i].pid);
            }
        }
    }
}

int pick(Process p[]) {

    int idx = -1;

    for (int i = 0; i < n; i++) {

        if (p[i].state != FINISHED) {

            if (idx == -1 ||
                p[i].priority < p[idx].priority)
                idx = i;
        }
    }

    return idx;
}

int allDone(Process p[]) {

    for (int i = 0; i < n; i++)
        if (p[i].state != FINISHED)
            return 0;

    return 1;
}

void printGantt() {

    printf("\n=== GANTT CHART ===\n");

    for (int i = 0; i < gc; i++) {
        printf("| P%d ", chart[i].pid);
    }

    printf("|\n");
}

int main() {

    Process p[MAX];

    n = 4;

    p[0] = (Process){1, 8, 10, 10, 0, 0, READY};
    p[1] = (Process){2, 5, 4, 4, 0, 0, READY};
    p[2] = (Process){3, 9, 7, 7, 0, 0, READY};
    p[3] = (Process){4, 3, 3, 3, 0, 0, READY};

    int clock = 0;
    int current = -1;

    printf("=== PRIORITY SCHEDULER WITH AGING + PREEMPTION ===\n");

    while (!allDone(p)) {

        printf("\nCLOCK %d\n", clock);

        applyAging(p);

        int next = pick(p);

        // Preemption check
        if (next != current) {
            current = next;
        }

        if (current == -1) {
            printf("No process\n");
            break;
        }

        printf("[RUNNING] P%d priority=%d\n",
               p[current].pid, p[current].priority);

        p[current].state = RUNNING;
        p[current].remainingTime--;

        addGantt(p[current].pid);

        if (p[current].remainingTime == 0) {

            p[current].state = FINISHED;
            printf("[FINISHED] P%d\n", p[current].pid);

            current = -1;
        } else {
            p[current].state = READY;
        }

        clock++;
    }

    printGantt();

    int sum = 0;

    printf("\n=== METRICS ===\n");

    for (int i = 0; i < n; i++) {
        printf("P%d wait=%d\n", p[i].pid, p[i].totalWait);
        sum += p[i].totalWait;
    }

    printf("AVG WAIT = %.2f\n", (float)sum / n);

    return 0;
}
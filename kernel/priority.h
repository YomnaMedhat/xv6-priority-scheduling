#ifndef PRIORITY_H
#define PRIORITY_H

#define PRIORITY_MIN 1
#define PRIORITY_MAX 10
#define DEFAULT_PRIORITY 5

int is_valid_priority(int priority);
int clamp_priority(int priority);
int is_higher_priority(int p1, int p2);
void update_priority(int *priority, int new_priority);

#endif

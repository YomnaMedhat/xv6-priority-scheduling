#include "types.h"
#include "priority.h"

int
is_valid_priority(int priority)
{
  return priority >= PRIORITY_MIN &&
         priority <= PRIORITY_MAX;
}

int
clamp_priority(int priority)
{
  if(priority < PRIORITY_MIN)
    return PRIORITY_MIN;

  if(priority > PRIORITY_MAX)
    return PRIORITY_MAX;

  return priority;
}

int
is_higher_priority(int p1, int p2)
{
  return p1 < p2;
}

void
update_priority(int *priority, int new_priority)
{
  *priority = clamp_priority(new_priority);
}

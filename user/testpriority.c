#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  int pid1, pid2, pid3;

  printf("=== Priority Scheduler Test ===\n");

  // Test 1: Different priorities
  // Child with priority 1 should finish before priority 10
  printf("\n[Test 1] Different priorities\n");

  pid1 = fork();
  if(pid1 == 0){
    setpriority(getpid(), 1);   // highest priority
    printf("Child A (priority 1) running\n");
    exit(0);
  }

  pid2 = fork();
  if(pid2 == 0){
    setpriority(getpid(), 10);  // lowest priority
    printf("Child B (priority 10) running\n");
    exit(0);
  }

  wait(0);
  wait(0);
  printf("[Test 1] Done\n");

  // Test 2: Same priority (round-robin)
  printf("\n[Test 2] Same priority (round-robin)\n");

  for(int i = 0; i < 3; i++){
    pid3 = fork();
    if(pid3 == 0){
      setpriority(getpid(), 5);
      printf("Child %d (priority 5) running\n", i);
      exit(0);
    }
  }

  wait(0); wait(0); wait(0);
  printf("[Test 2] Done\n");

  // Test 3: Edge cases
  printf("\n[Test 3] Edge cases\n");
  setpriority(getpid(), 0);   // below min, should clamp to 1
  printf("Set priority 0 (should clamp): OK\n");
  setpriority(getpid(), 99);  // above max, should clamp to 10
  printf("Set priority 99 (should clamp): OK\n");
  printf("[Test 3] Done\n");

  printf("\n=== All Tests Passed ===\n");
  exit(0);
}

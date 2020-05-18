#ifdef CS333_P3
//p3testsuite.c
//Created by Jordan Green
//CS333 - Spring 2018
//Version 1.1

#include "types.h"
#include "user.h"
#include "uproc.h"

#define SHORT_WAIT 2
#define LONG_WAIT 5

//#define TEST_ALLOC
//#define TEST_SLEEP
//#define TEST_ROUNDROBIN
#define TEST_ZOMBIE
//#define TEST_KILL

#ifdef TEST_ALLOC
//Test by Jordan Green
static void
test_process_alloc(){
  printf(1,"Process allocation test started...\nPress control-f to get an initial state. Sleeping %d seconds.\n",SHORT_WAIT);
  sleep(SHORT_WAIT * 1000);
  int rc = fork();

  switch(rc)
  {
    case 0:
      printf(1, "Process allocated, press control-f. Sleeping %d seconds.\n", SHORT_WAIT);
      sleep(SHORT_WAIT * 1000);
      exit();
      break;
    default:
      wait();
      printf(1, "Process deallocated, press control-f. Sleeping %d seconds.\n",SHORT_WAIT);
      sleep(SHORT_WAIT * 1000);
      break;
  }

  printf(1, "Test concluded.\n");
}
#endif

#ifdef TEST_SLEEP
static void
spin(int ms)
{
  int time = uptime();
  while(1)
    if((time + ms) < uptime())
      break;
}
//Test by Jordan Green.
static void
test_sleep_list(){
  printf(1, "Sleep test started...\nPress control-s to show sleeping processes. Spinning for %d seconds.\n", SHORT_WAIT);
  spin(SHORT_WAIT * 1000);
  printf(1, "Press control-s to show sleeping processes. Sleeping for %d seconds. \n",SHORT_WAIT);
  sleep(SHORT_WAIT * 1000);
  printf(1, "Press control-s to show sleeping processes. Spinning for %d seconds. \n",SHORT_WAIT);
  spin(SHORT_WAIT * 1000);

  printf(1, "Test concluded.\n");

}
#endif

#ifdef TEST_ROUNDROBIN
//Test by Jordan Green
static void
test_round_robin()
{
  int mistakes[64];
  int count;

  printf(1, "Round robin test started...\n");

  memset(&mistakes, 0, sizeof(mistakes));
  count = 0;

  int rc = 0;
  while((mistakes[count++] = rc = fork()) > 0)
    if(count %10 == 0)
      printf(1, "%d processes spawned...\n", count);

  //child logic
  if(rc == 0)
    while(1); //I'm sorry, babbage...
  //Parent logic
  else{
    printf(1, "Press control-r to show round-robin action. Sleeping for %d seconds.\n", LONG_WAIT);
    sleep(LONG_WAIT * 1000);

    printf(1, "Cleaning up children...\n");
    count = 0;
    //kill all children..
    while(mistakes[count] > 0){
      //kill each child and wait so we reap the process.
      //zombies aren't cool...
      kill(mistakes[count++]);
      wait();
    }

    printf(1, "Test concluded.\n");
  }
}
#endif

#ifdef TEST_ZOMBIE
//Test by Jordan Green
static void
test_zombie_reap(){
  printf(1, "Zombie / reap test started...");
  int rc = fork();

  if(rc == 0){
    printf(1, "Child: sleeping for %d seconds, press control-z. Zombie list should be empty:\n", SHORT_WAIT);
    sleep(SHORT_WAIT * 1000);
    printf(1, "Child: exiting. Sleeping for %d seconds, press control-z. Zombie list should be populated with PID %d:\n",SHORT_WAIT, getpid());
    exit();
    }
  else{
    sleep(SHORT_WAIT * 2 * 1000);
    printf(1, "Parent: reaping child with wait() call. Sleeping for %d seconds, press control-z. Zombie list should be empty:\n", SHORT_WAIT);
    wait();
    sleep(SHORT_WAIT * 2 * 1000);
    printf(1, "Test concluded.\n");
  }
}
#endif

#ifdef TEST_KILL
//Basic concept refrenced from geeksforgeeks.org. simplififed for our uses.
//Only handles base 10 and doesn't handle negative numbers.
char * itoa(int n, char* buf)
{
  int i = 0;

  if(n == 0){
    buf[0] = '0';
    buf[1] = '\00';
    return buf;
  }

  while(n)
  {
    int remainder = n % 10;
    if(remainder >= 10)
      buf[i++] = 'a' + remainder - 10;
    else
      buf[i++] = '0' + remainder;

    n = n/10;
  }
  buf[i] = '\00';
  int start = 0, end = i-1;

  while(start < end)
  {
    char temp = buf[end];
    buf[end] = buf[start];
    buf[start] = temp;
    start++;
    end--;
  }
  return buf;
}
//Test by Jordan Green
static void
test_kill_reap(){
  printf(1, "Kill / reap test started...\n");
  printf(1, "Sleeping %d seconds... Press control-z and control-f to show the zombie process\n", LONG_WAIT);
  sleep(LONG_WAIT * 1000);

  int rc = fork();

  if(rc == 0)
    while(1)
      sleep(1000);
  else{
    int rc2 = fork();
    if(rc2 == 0){
      char temp[256] = {0};
      char* args[] = {"kill", itoa(rc,temp),0};

      printf(1, "Executing \"kill %d\"to kill child processes.\n",rc);
      exec(args[0], args);
    }
    else
    {

      wait();
      printf(1, "Sleeping %d seconds... Press contorl-z and control-f to show the zombie process\n", LONG_WAIT);
      sleep(LONG_WAIT * 1000);
      while(wait() != -1);
      printf(1, "process reaped by calling wait()... Press control-z and control-f to show the empty list\n", LONG_WAIT);
      sleep(LONG_WAIT * 1000);
    }
  }
  printf(1, "Test concluded.\n");
}
#endif

int
main(int argc, char* argv[])
{
#ifdef TEST_ALLOC
  test_process_alloc();
#endif
#ifdef TEST_SLEEP
  test_sleep_list();
#endif
#ifdef TEST_ROUNDROBIN
  test_round_robin();
#endif
#ifdef TEST_ZOMBIE
  test_zombie_reap();
#endif
#ifdef TEST_KILL
  test_kill_reap();
#endif
}
#endif

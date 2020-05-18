// author: Michael Heyman

#ifdef CS333_P3
#include "types.h"
#include "user.h"

// Enable these directives one at a time,
// as they are mutually exclusive since some
// of them loop forever

//#define FREE_TEST
//#define ROUNDROBIN_TEST
//#define SLEEP_TEST
//#define KILL_TEST
#define EXIT_TEST
//#define WAIT_TEST

#define SLEEP_TIME 7*TPS

static int
loopforever(void)
{
  int ret = 0;

  for(;;)
    ret = 1 + 1;

  exit();
  return ret;
}

#ifdef FREE_TEST
static void
testfree(void)
{
  int pid;

  printf(1, "\n----------\nRunning Free Test\n----------\n");

  printf(1, "Press CTRL+F once to display free list and then CTRL+P.\n");
  sleep(SLEEP_TIME);

  printf(1, "Forking process with PID %d..\n", getpid());
  pid = fork();
  if(pid == 0) {
    printf(1, "Press CTRL+F once to display free list and then CTRL+P.\n");
    sleep(SLEEP_TIME);

    printf(1, "Exiting child process.\n");
    exit();
  }
  else {
    wait();
    printf(1, "Press CTRL+F once to display free list and then CTRL+P.\n");
    sleep(SLEEP_TIME);
  }

  exit();
}
#endif // FREE_TEST

#ifdef ROUNDROBIN_TEST
// original author: Josh Wolsborn
// modified with permission
static void
testroundrobin(void)
{
  int ret = 1;

  for(int i = 0; i < 5; i++){
    if(ret > 0){
      printf(1, "Looping process created\n");
      ret = fork();
    }else{
      break;
    }
  }  
  if(ret > 0){ 
    printf(1, "Press and hold CTRL+R to display ready list\n");
    printf(1, "-------------------------------------\n");
    sleep(SLEEP_TIME);
    while(wait() != -1);
  }

  loopforever();

  exit();
}
#endif // ROUNDROBIN_TEST

#ifdef SLEEP_TEST
// original author: Amie R
// modified with permission
static void
testsleep(void)
{
  int startticks;

  startticks = uptime();

  printf(1, "\nSleeptest is running, press 'control-p', and 'control-s'.\n");
  while(uptime() - startticks <= 10000);

  printf(1, "\nNow, sleeptest will go to sleep. Press 'control-p' and 'control-s'.\n");
  sleep(SLEEP_TIME);

  printf(1, "\nSleeptest woke up. Press 'control-p' and 'control-s' again.\n");

  startticks = uptime();
  while(uptime() - startticks <= 10000);
}
#endif // SLEEP_TEST

#ifdef KILL_TEST
static void
testkill(void)
{
  int pid;

  printf(1, "\n----------\nRunning Kill Test\n----------\n");

  printf(1, "Press CTRL+Z once to display zombie list and then CTRL+P.\n");
  sleep(SLEEP_TIME);

  printf(1, "Forking process with PID %d..\n", getpid());
  pid = fork();
  if(pid == 0) {
    loopforever();
  }
  else {
    sleep(1000);
    kill(pid);
    printf(1, "Child process killed.\n");
    printf(1, "Press CTRL+Z once to display zombie list and then CTRL+P.\n");
    sleep(SLEEP_TIME);
    wait();
  }

  exit();
}
#endif // KILL_TEST

#ifdef EXIT_TEST
static void
testexit(void)
{
  int pid;

  printf(1, "\n----------\nRunning Exit Test\n----------\n");

  printf(1, "Press CTRL+Z once to display zombie list and then CTRL+P.\n");
  sleep(SLEEP_TIME);

  printf(1, "Forking process with PID %d..\n", getpid());
  pid = fork();
  if(pid == 0) {
    printf(1, "Exiting child process.\n\n");
    exit();
  }
  else {
    sleep(1000);
    printf(1, "Press CTRL+Z once to display zombie list and then CTRL+P.\n");
    sleep(SLEEP_TIME);
    wait();
  }

  exit();
}
#endif // EXIT_TEST

#ifdef WAIT_TEST
static void
testwait(void)
{
  int pid;

  printf(1, "\n----------\nRunning Wait Test\n----------\n");

  printf(1, "Forking process with PID %d..\n", getpid());
  pid = fork();
  if(pid == 0) {
    printf(1, "Press CTRL+F once to display free list and then CTRL+P.\n");
    sleep(SLEEP_TIME);
  }
  else {
    wait();
    printf(1, "Child has finished.\n");
    printf(1, "Press CTRL+F once to display free list and then CTRL+P.\n");
    sleep(SLEEP_TIME);
  }

  exit();
}
#endif // WAIT_TEST

int
main(int argc, char *argv[])
{
#ifdef FREE_TEST
  testfree();
#endif // FREE_TEST
#ifdef ROUNDROBIN_TEST
  testroundrobin();
#endif // ROUNDROBIN_TEST
#ifdef SLEEP_TEST
  testsleep();
#endif // SLEEP_TEST
#ifdef KILL_TEST
  testkill();
#endif // KILL_TEST
#ifdef EXIT_TEST
  testexit();
#endif // EXIT_TEST
#ifdef WAIT_TEST
  testwait();
#endif // WAIT_TEST
  exit();
  loopforever();  // supress compiler warning
}
#endif

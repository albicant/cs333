#ifdef CS333_P2
#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int pid;
  uint time, f;

  time = uptime();
  pid = fork();
  if(pid < 0) {
    printf(2, "time: \'fork\' failed.\n");
    exit();
  }
  else if(pid == 0) {
    if(exec(argv[1], argv+1) < 0)
      exit();
  }
  else
    wait();
  
  time = uptime() - time;
  f = time % 1000;
  printf(1, "%s ran in %d.", argv[1], time / 1000);
  if(f >= 100)
    printf(1, "%d seconds.\n", f);
  else if (f >= 10)
    printf(1, "0%d seconds.\n", f);
  else
    printf(1, "00%d seconds.\n", f);

  exit();
}
#endif // CS333_P2

#include "types.h"
#include "user.h"
#ifdef CS333_P4
int
main(int argc, char *argv[])
{
  if(!argv[1])
    {
      printf(2,"You need to provide a pid\n");
      exit();
    }
  int pid = atoi(argv[1]);

  int priority = getpriority(pid);
  if(priority == -1)
    printf(2, "Error! Cannot find the process with PID = %d\n", pid);
  else
    printf(1, "Priority of the process with PID = %d is %d\n", pid, priority);
  exit();
}
#endif // CS333_P4

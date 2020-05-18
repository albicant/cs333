#include "types.h"
#include "user.h"

#ifdef CS333_P4
int
main(int argc, char *argv[])
{
  if(!argv[1] || !argv[2])
    {
      printf(2,"You need two arguments\n");
      exit();
    }
  int pid = atoi(argv[1]);
  int priority = atoi(argv[2]);

  int rc = setpriority(pid, priority);
  if(rc == -1)
    printf(2, "Error setting the priority\n");
  exit();
}
#endif // CS333_P4

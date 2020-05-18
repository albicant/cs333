#ifdef CS333_P2
#include "types.h"
#include "user.h"
#include "uproc.h"

void
printFloat(int n)
{
  int f;

  if(n >= 0) {
    printf(1, "%d.", n/1000);
    f = n % 1000;
    if(f >= 100)
      printf(1, "%d\t", f);
    else if (f >= 10)
      printf(1, "0%d\t", f);
    else
      printf(1, "00%d\t", f);
  }
}

int
main()
{
  uint max = 72;
  struct uproc *table;
  int entr;
  uint i;

  table = (struct uproc *) malloc(max * sizeof(struct uproc));
  if(!table) {
    printf(2, "Error: malloc() call failed. %s at line %d\n", __FUNCTION__, __LINE__);
    exit();
  }
 
  
  entr = getprocs(max, table);
  if(entr <= 0) {
    printf(2, "Error: ps call failed.\n");
    free(table);
    exit();
  }

//  printf(1, "\"max\" set equal to %d\n", max);
#ifdef CS333_P4
  printf(1, "PID\tName\tUID\tGID\tPPID\tPrio\tElapsed\tCPU \tState\tSize\n");
#else
  printf(1, "PID\tName\tUID\tGID\tPPID\tElapsed\tCPU \tState\tSize\n");
#endif // CS333_P4
  for(i = 0; i < entr; i++) {
#ifdef CS333_P4
    printf(1, "%d\t%s\t%d\t%d\t%d\t%d\t", table[i].pid, table[i].name, table[i].uid, table[i].gid, table[i].ppid, table[i].priority);
#else
    printf(1, "%d\t%s\t%d\t%d\t%d\t", table[i].pid, table[i].name, table[i].uid, table[i].gid, table[i].ppid);
#endif // CS333_P4
    printFloat(table[i].elapsed_ticks);
    printFloat(table[i].CPU_total_ticks);
    printf(1, "%s\t%d\n", table[i].state, table[i].size);
  }
 
  free(table);
  exit();
}
#endif // CS333_P2

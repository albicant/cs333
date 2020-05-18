#include "types.h"
#include "user.h"
#include "pdx.h"

//code done by: Mark M. and Jeremiah.

int
main(int argc, char* argv[])
{
  int i=0, pid = 0;
  while(pid >= 0) {
    pid = fork();
    if(pid == 0){
      while(1)
        i++;
    }
  }
  exit();
}

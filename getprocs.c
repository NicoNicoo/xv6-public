#include "types.h"
#include "proc.h"
#include "user.h"
#include "stat.h"

int
main(void)
{
  printf(1,"El numero de procesos corriendo es: %d\n", getprocs());
  exit();
}
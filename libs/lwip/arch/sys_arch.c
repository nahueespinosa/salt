#include "sapi.h"

uint32_t sys_now(void)
{
   return tickRead();
}

#include "types.h"
#include "uspinlock.h"
#include "x86.h"

void
uinitlock(struct uspinlock *lock){
  lock->locked = 0;
}

void
uacquire (struct uspinlock *lock){
  while( xchg(&lock->locked, 1) != 0 )
    ;
}

void
urelease (struct uspinlock *lock){
  //release the lock.
  lock->locked = 0;
}

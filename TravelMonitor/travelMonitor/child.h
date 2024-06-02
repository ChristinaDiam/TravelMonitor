#ifndef CHILD
#define CHILD

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>


pid_t createchild(int i);

#endif //CHILD
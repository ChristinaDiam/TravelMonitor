#ifndef PIPES
#define PIPES


#include <fcntl.h>
#include <sys/stat.h>

#include "child.h"

void createpipes(int numMonitors);

void destroypipes(int numMonitors);

#endif //PIPES
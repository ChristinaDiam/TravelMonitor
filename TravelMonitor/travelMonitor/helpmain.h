#ifndef HELPMAIN
#define HELPMAIN

#include "pipes.h"
#include "child.h"

using namespace std;

void travelmonitor(int numMonitors, int bufferSize, int bloomSize, string inputDirectory);


//converting int to int* by copying the value
int* createint(int i);

int sendstr(int fd, string message);

int sendint(int fd, int num);

string* readstr(int fd);

int readint(int fd);

#endif //HELPMAIN
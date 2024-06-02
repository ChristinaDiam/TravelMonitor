#ifndef HELPMAIN
#define HELPMAIN

#include<string>
#include<cstring>

using namespace std;


void monitor(char* s,char* r);

int* createint(int i);

string* readstr(int fd);

int readint(int fd);

int sendstr(int fd, string message);

int sendint(int fd, int num);

#endif //HELPMAIN
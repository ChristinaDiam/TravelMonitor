#ifndef COUNTRIES
#define COUNTRIES

#include<iostream>
#include<string>

#include"list.h"

using namespace std;

class countries
{
private:

    string country;
    int fds;
    int fdr;
    list *blooms;

public:
    countries(string country, int fds, int fdr);
    ~countries();

    string getcountry();
    int getfds();
    int getfdr();
    list *getblooms();
};


#endif //COUNTRIES
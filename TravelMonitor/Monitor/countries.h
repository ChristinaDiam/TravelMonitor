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
    list *blooms;
    list *citizens;
    list *skipvaccinated;
    list *skipnotvaccinated;

public:
    countries(string country);
    ~countries();

    string getcountry();
    list *getblooms();
    list *getcitizens();
    list *getskipvaccinated();
    list *getskipnotvaccinated();
};

#endif //COUNTRIES
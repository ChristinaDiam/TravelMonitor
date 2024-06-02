#include"countries.h"


countries::countries(string country, int fds, int fdr)
{
    this->country=country;
    this->fds=fds;
    this->fdr=fdr;

    this->blooms=new list();
}


countries::~countries()
{
    delete this->blooms;
}


string countries::getcountry(){

    return this->country;
}


int countries::getfds(){

    return this->fds;
}


int countries::getfdr(){

    return this->fdr;
}


list* countries::getblooms(){

    return this->blooms;
}
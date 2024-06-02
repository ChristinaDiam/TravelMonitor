#include"countries.h"


countries::countries(string country){

    this->country=country;

    this->blooms=new list();
    this->citizens=new list();
    this->skipvaccinated=new list();
    this->skipnotvaccinated=new list();
}


countries::~countries(){
    
    delete this->blooms;
    delete this->citizens;
    delete this->skipvaccinated;
    delete this->skipnotvaccinated;
}


string countries::getcountry(){

    return this->country;
}


list* countries::getblooms(){

    return this->blooms;
}


list* countries::getcitizens(){

    return this->citizens;
}


list* countries::getskipvaccinated(){

    return this->skipvaccinated;
}


list* countries::getskipnotvaccinated(){

    return this->skipnotvaccinated;
}

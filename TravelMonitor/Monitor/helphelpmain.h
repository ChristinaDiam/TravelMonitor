#ifndef HELPHELPMAIN
#define HELPHELPMAIN

#include "citizen.h"
#include "bloomfilter.h"
#include "skiplist.h"


//insertCitizenRecord function
void insertCitizenRecord(string ID, string fname,string lname,string country,string age,string vname,
string yn, string date, list *skipvaccinated, list *skipnotvaccinated, list *citizens, list *blooms, int bloomsize);


//checks every record 
int checkrecord(listnode *tmp,int flag,string ID, string fname, string lname, string country,string age, 
string vname, string yn, string date, list *blooms, int bloomsize, list *skipvaccinated, list *skipnotvaccinated);


//function that finds a virus with "vname" in a citizen
cvirus *findvirus(citizen *c, string vname);


//function that finds citizen with ID in citizen list
citizen *findcitizen(list *citizens, string ID);


#endif //HELPHELPMAIN
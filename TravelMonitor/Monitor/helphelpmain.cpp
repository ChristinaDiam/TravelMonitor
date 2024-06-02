#include<iostream>
#include<cstring>

#include"helphelpmain.h"

using namespace std;


int compareblooms(void* item1, void* item2){

    bloomvirus *bv1=(bloomvirus*) item1;
    bloomvirus *bv2=(bloomvirus*) item2;

    return (bv1->getvname()).compare(bv2->getvname());
}


int comparebloom(void* item1, void* item2){

    bloomvirus *bv1=(bloomvirus*) item1;
    bloomvirus *bv2=(bloomvirus*) item2;

    return (bv1->getvname()).compare(bv2->getvname());
}


int comparestrings(void* item1, void* item2){

    string s1=*((string *) item1);
    string s2=*((string *) item2);

    return (s1.compare(s2));
}


void insertCitizenRecord(string ID, string fname,string lname,string country,string age,string vname,
string yn, string date, list *skipvaccinated, list *skipnotvaccinated, list *citizens, list *blooms, int bloomsize){


    listnode *tmp=citizens->gethead();

    //ages must be 0<age<120
    if((atoi(age.c_str())>0) && (atoi(age.c_str())<120)){

        int flag1=0;

        flag1=checkrecord(tmp, flag1, ID, fname, lname, country, age, vname, yn, date,
        blooms, bloomsize,skipvaccinated,skipnotvaccinated);

        //we found a new citizen
        if(flag1==0){

            citizen *c=new citizen(ID, fname, lname, country, age, vname, yn, date);
            citizens->listinsert(c);

            char* s = new char [c->getID().length() + 1];
            strcpy(s, c->getID().c_str());

            delete[] s;

            //if citizen is vaccinated we add the virus in bloomfilter list
            //if citizen is vaccinated we add the virus in skiplist for vaccinated citizens
            if(yn=="YES"){
                

                //bloomfilter list insertion

                bloomvirus *bv=new bloomvirus(vname,NULL);

                bloomvirus *search=(bloomvirus*)blooms->search(bv,comparebloom);

                if(search==NULL){

                    bloomfilter *filter=new bloomfilter(bloomsize);

                    char* s = new char [ID.length() + 1];
                    strcpy(s, ID.c_str());

                    filter->insert((unsigned char*)s);

                    delete[] s;

                    bloomvirus *virus=new bloomvirus(vname,filter);

                    blooms->listinsert(virus);

                }else{

                    char* s = new char [ID.length() + 1];
                    strcpy(s, ID.c_str());

                    search->getbloom()->insert((unsigned char*)s);

                    delete[] s;
                } 

                delete bv; 


                //skilpist (vaccinated) insertion

                //checks if the virus already exists in list
                listnode *skiptmp=skipvaccinated->gethead();

                skiplist *found=NULL;

                while(skiptmp!=NULL){

                    skiplist *sk=(skiplist*)skiptmp->getvalue();

                    if(sk->getvname()==vname){

                        found=sk;
                        break;

                    }else{

                        skiptmp=skiptmp->getnext();
                    }
                }

                //we found a new virus
                if(found==NULL){

                    skiplist *skip=new skiplist(vname);

                    skip->insert(c);

                    skipvaccinated->listinsert(skip);

                }else{

                    found->insert(c);
                }

            }else{

                //skilpist (not vaccinated) insertion

                //checks if the virus already exists in list
                listnode *skipnottmp=skipnotvaccinated->gethead();
                
                skiplist *foundnot=NULL;

                while(skipnottmp!=NULL){

                    skiplist *sknot=(skiplist*)skipnottmp->getvalue();

                    if(sknot->getvname()==vname){

                        foundnot=sknot;
                        break;

                    }else{

                        skipnottmp=skipnottmp->getnext();
                    }
                }

                //we found a new virus
                if(foundnot==NULL){

                    skiplist *skipnot=new skiplist(vname);

                    skipnot->insert(c);

                    skipnotvaccinated->listinsert(skipnot);

                }else{

                    foundnot->insert(c);
                }
            }
        }
    }else{

        //wrong citizen record (wrong age input)
        cout<<"ERROR IN RECORD "<<ID<<endl;
    }

}



//checks if the record is valid (for duplicate records) 
int checkrecord(listnode *tmp,int flag,string ID, string fname, string lname, string country, string age, 
string vname, string yn, string date, list *blooms, int bloomsize, list *skipvaccinated, list *skipnotvaccinated){


    while(tmp!=NULL){

        citizen *cit=(citizen*)tmp->getvalue();

        //citizens with different ID are saved as a new citizen
        //citizens with same ID must have the same info but different virus info
        if(ID==cit->getID()){

            flag=1;

            //same citizen must have same first name
            if(fname==cit->getf_name()){

                //same citizen must have same last name
                if(lname==cit->getl_name()){

                    //same citizen must have same country
                    if(country==cit->getcountry()){

                        //same citizen must have same age
                        if(atoi(age.c_str())==cit->getage()){
                        
                            list *cv=cit->getvirusinfo();
                            listnode *cvir=cv->gethead();

                            int flag2=0;

                            while(cvir!=NULL){

                                cvirus *vir=(cvirus*)cvir->getvalue();

                                //if it's the same person we must have different viruses
                                if(vname==vir->getvname()){
                                    flag2=1;
                                    break;
                                }

                                cvir=cvir->getnext();
                            }

                            //we found a new virus
                            if(flag2==0){

                                cvirus *newvirus=new cvirus(vname, yn, date);
                                cv->listinsert(newvirus);

                                //if citizen is vaccinated we add the virus in bloomfilter list
                                if(yn=="YES"){
                                    
                                    bloomvirus *bv=new bloomvirus(vname,NULL);

                                    bloomvirus *search=(bloomvirus*)blooms->search(bv,compareblooms);

                                    if(search==NULL){

                                        bloomfilter *filter=new bloomfilter(bloomsize);

                                        char* s = new char [ID.length() + 1];
                                        strcpy(s, ID.c_str());

                                        filter->insert((unsigned char*)s);

                                        delete[] s;

                                        bloomvirus *virus=new bloomvirus(vname,filter);

                                        blooms->listinsert(virus);

                                    }else{

                                        char* s = new char [ID.length() + 1];
                                        strcpy(s, ID.c_str());

                                        search->getbloom()->insert((unsigned char*)s);

                                        delete[] s;
                                    } 

                                    delete bv;  

                                    
                                    //skilpist (vaccinated) insertion

                                    //checks if the virus already exists in list
                                    listnode *skiptmp=skipvaccinated->gethead();

                                    skiplist *found=NULL;

                                    while(skiptmp!=NULL){

                                        skiplist *sk=(skiplist*)skiptmp->getvalue();

                                        if(sk->getvname()==vname){

                                            found=sk;
                                            break;

                                        }else{

                                            skiptmp=skiptmp->getnext();
                                        }
                                    }

                                    //we found a new virus
                                    if(found==NULL){

                                        skiplist *skip=new skiplist(vname);

                                        skip->insert(cit);

                                        skipvaccinated->listinsert(skip);

                                    }else{

                                        found->insert(cit);
                                    }
                                    
                                //if citizen is not vaccinated we add the virus in skiplist for not vaccinated citizens
                                }else if(yn=="NO"){

                                    //skilpist (not vaccinated) insertion

                                    //checks if the virus already exists in list
                                    listnode *skipnottmp=skipnotvaccinated->gethead();
                                    
                                    skiplist *foundnot=NULL;

                                    while(skipnottmp!=NULL){

                                        skiplist *sknot=(skiplist*)skipnottmp->getvalue();

                                        if(sknot->getvname()==vname){

                                            foundnot=sknot;
                                            break;

                                        }else{

                                            skipnottmp=skipnottmp->getnext();
                                        }
                                    }

                                    //we found a new virus
                                    if(foundnot==NULL){

                                        skiplist *skipnot=new skiplist(vname);

                                        skipnot->insert(cit);

                                        skipnotvaccinated->listinsert(skipnot);

                                    }else{

                                        foundnot->insert(cit);
                                    }
                                }

                                break;

                            }else{

                                //wrong citizen record (duplicate record)
                                cout<<"ERROR IN RECORD "<<ID<<endl;
                                break;
                            }

                        }else{

                            //wrong citizen record (same person with different age)
                            cout<<"ERROR IN RECORD "<<ID<<endl;
                            break;
                        }

                    }else{

                        //wrong citizen record (same person with different country)
                        cout<<"ERROR IN RECORD "<<ID<<endl;
                        break;
                    }

                }else{

                    //wrong citizen record (same person with different last name)
                    cout<<"ERROR IN RECORD "<<ID<<endl;
                    break;
                }

            }else{

                //wrong citizen record (same person with different first name)
                cout<<"ERROR IN RECORD "<<ID<<endl;
                break;
            }

        }else{

            tmp=tmp->getnext();
        }
    }

    return flag;
}



cvirus *findvirus(citizen *c, string vname){

    list *cv;
    cv=c->getvirusinfo();

    listnode *lnode;
    lnode=cv->gethead();

    while(lnode!=NULL){

        cvirus *v;
        v=(cvirus*)lnode->getvalue();

        if(v->getvname()==vname){

            return v;
        }

        lnode=lnode->getnext();
    }

    return NULL;
}



citizen *findcitizen(list *citizens, string ID){

    listnode *lnode;
    lnode=citizens->gethead();

    while(lnode!=NULL){

        citizen *c;
        c=(citizen*)lnode->getvalue();

        if(c->getID()==ID){

            return c;
        }

        lnode=lnode->getnext();
    }

    return NULL;
}

#define PATHLENGTH 13

#include<iostream>
#include<cstdio>
#include<unistd.h>
#include<fcntl.h>
#include<cstring>
#include<string>
#include<dirent.h>

#include "helpmain.h"
#include "list.h"
#include"countries.h"
#include"helphelpmain.h"


using namespace std;


void monitor(char* s,char* r){

    //opening the pipes
    int fdr=open(r,O_RDONLY);
    int fds=open(s,O_WRONLY);
   

    if(fds==-1){

        cout<<"Error opening 'Send Pipe'."<<endl;
        perror("open");
    }

    if(fdr==-1){

        cout<<"Error opening 'Receive Pipe'."<<endl;
        perror("open");
    }


    //read the 'size of bloom' and 'buffersize' from travelMonitor
    int bloomsize;
    int buffersize;

    int read1=read(fdr,&bloomsize,sizeof(int));
    int read2=read(fdr,&buffersize,sizeof(int));

    if(read1==-1){

        perror("read 1");
        return;
    }

    if(read2==-1){

        perror("read 2");
        return;
    }



    //read messages from the travelMonitor

    list *dirs=new list();      //list of directories

    int flag=0;
    while(flag==0){

        int length;

        int r1=read(fdr,&length,sizeof(int));

        char *str=new char[length+1];
        int r2=read(fdr,str,length);


        str[length]='\0';

        if(r1==-1){

            perror("read 1");
            return;
        }

        if(r2==-1){

            perror("read 2");
            return;
        }


        int comp=strcmp("End of directory.",str);

        if(comp==0){

            flag=1;
            break;
        }

        dirs->listinsert(str);
    }


    list *countriess=new list();        //list of countries

    //opening directories and reading text files
    listnode *lnode=dirs->gethead();

    while(lnode!=NULL){

        DIR* dir;
        struct dirent* en;

        char *directory=(char*)lnode->getvalue();
    
        dir=opendir(directory);

        if(dir==NULL){

            perror("opendir");
            return;
        }


        string country(directory);
        country=country.substr(PATHLENGTH,country.length()-PATHLENGTH);
        countries *cou=new countries(country);

        list *blooms=cou->getblooms();
        list *citizens=cou->getcitizens();
        list *skipvaccinated=cou->getskipvaccinated();
        list *skipnotvaccinated=cou->getskipnotvaccinated();


        //read the text files of the directory
        while((en=readdir(dir))!=NULL){

            int comp=strcmp(".",en->d_name);
            if(comp==0){

                continue;
            }

            comp=strcmp("..",en->d_name);
            if(comp==0){

                continue;
            }


            //we open the text file and read it
            FILE *fp;

            string t(directory);
            t.append("/");

            string file(en->d_name);
            t.append(file);

            fp=fopen(t.c_str(),"r");        //open file

            if(fp==NULL){

                printf("File could not be opened.\n");
                exit(EXIT_FAILURE);
            }

            char id[20],fn[20],ln[20],country[20],age[4],virName[20],yes_no[4],date[15];
            string temp[8];

            while(fscanf(fp, "%s%s%s%s%s%s%s", id, fn, ln, country, age, virName, yes_no)!=EOF){

                temp[0]=string(id);
                temp[1]=string(fn);
                temp[2]=string(ln);
                temp[3]=string(country);
                temp[4]=string(age);
                temp[5]=string(virName);
                temp[6]=string(yes_no);

                char ch=fgetc(fp);

                if(ch==' '){
                    fscanf(fp, "%s",date);
                    temp[7]=string(date);
                }else{
                    temp[7]="";
                }

                if((temp[6]=="NO" && temp[7]=="") || (temp[6]=="YES" && temp[7]!="")){

                    if(temp[7]==""){

                        temp[7]="-";
                    }

                    insertCitizenRecord(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],
                    temp[7],skipvaccinated,skipnotvaccinated,citizens,blooms,bloomsize);

                }else{

                    //wrong citizen record (wrong information about date and yes/no)
                    cout<<"ERROR IN RECORD "<<temp[0]<<endl;
                }
            }

            fclose(fp);
        }

        countriess->listinsert(cou);

        lnode=lnode->getnext();
    }


    listnode *node=countriess->gethead();

    while(node!=NULL){

        countries *c=(countries*)node->getvalue();

        list* b=c->getblooms();


        listnode *ln=b->gethead();

        while(ln!=NULL){

            bloomvirus *bv=(bloomvirus*)ln->getvalue();

            //send virus name to travelMonitor
            string vname=bv->getvname();

            int s=sendstr(fds,vname);

            if(s==-1){
                return;
            }

            //read message from parent
            string *str=readstr(fdr);

            if(str==NULL){
                return;
            }


            //read message from parent "Send me bloomfilter"
           /* string *message=readstr(fdr);

            if(message==NULL){
                return;
            }

            cout<<*message<<endl;*/

            //send bloomfilter to parent
                
            

            ln=ln->getnext();
        }

        node=node->getnext();
    }


    int end=sendstr(fds,"End of virus");

    if(end==-1){
        return;
    }

}


int* createint(int i){

    int* pointer=new int(i);
    return pointer;
}


string* readstr(int fd){

    int length;

    int r1=read(fd,&length,sizeof(int));

    char *str=new char[length+1];
    int r2=read(fd,str,length);

    str[length]='\0';

    if(r1==-1){

        perror("read 1");
        return NULL;
    }

    if(r2==-1){

        perror("read 1");
        return NULL;
    }

    string *s=new string(str);

    delete[] str;

    return s;
}


int readint(int fd){

    int num;

    int r=read(fd,&num,sizeof(int));

    if(r==-1){

        perror("read");
        return -1;
    }

    return num;
}


int sendint(int fd, int num){

    int *pointer=createint(num);

    int w=write(fd,pointer,sizeof(int));

    if(w==-1){

        perror("write");
        return -1;
    }

    delete pointer;

    return 0;

}


int sendstr(int fd, string message){

    int *pointer=createint(message.length());

    int w1=write(fd,pointer,sizeof(unsigned int));
    int w2=write(fd,message.c_str(), message.length());

    delete pointer;

    if(w1==-1){

        perror("write 1");
        return -1;
    }

    if(w2==-1){

        perror("write 2");
        return -1;
    }

    return 0;
}

#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cstdio>

#include "pipes.h"

using namespace std;


void createpipes(int numMonitors){

    int i=0;

    while(i<numMonitors){

        //creating the name of the pipes
        string sname="SMonitor";
        string rname="RMonitor";

        string num=to_string(i);

        sname.append(num);
        rname.append(num);

        //creating the pipes (one to send and one to receive)
        int s=mkfifo(sname.c_str(),0666);
        int r=mkfifo(rname.c_str(),0666);

        if(s==-1){

            cout<<"Error creating 'Send Pipe'."<<endl;
            perror("mkfifo");
        }

        if(r==-1){

            cout<<"Error creating 'Receive Pipe'."<<endl;
            perror("mkfifo");
        }

        i++;
    }
}



void destroypipes(int numMonitors){

    int i;

    for(i=0; i<numMonitors; i++){

        string sname="SMonitor";
        string rname="RMonitor";

        string num=to_string(i);

        sname.append(num);
        rname.append(num);

        int s=unlink(sname.c_str());
        int r=unlink(rname.c_str());

        if(s==-1){

            cout<<"Error destroying 'Send Pipe'."<<endl;
            perror("unlink");
        }

        if(r==-1){

            cout<<"Error destroying 'Receive Pipe'."<<endl;
            perror("unlink");
        }
    }
}
#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cstdio>

#include "child.h"

using namespace std;

pid_t createchild(int i){

    pid_t childpid;
    childpid=fork();

    if(childpid==-1){

        perror("Failed to fork");
        return -1;
    }


    if(childpid==0){

        //Smonitor sends from travel monitor to monitor
        string sname="SMonitor";

        //Rmonitor (travel monitor receives from monitor)
        string rname="RMonitor";

        string num=to_string(i);

        sname.append(num);
        rname.append(num);

        execl("../Monitor/Monitor", "./Monitor", sname.c_str(), rname.c_str() , (char*) NULL);
    }

    return childpid;
}


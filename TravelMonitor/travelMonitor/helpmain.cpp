#include<iostream>
#include<cstdio>
#include<dirent.h>
#include<cstring>

#include "helpmain.h"

using namespace std;


void travelmonitor(int numMonitors, int bufferSize, int bloomSize, string inputDirectory){


    //function to create the pipes
    createpipes(numMonitors);

    int i=0;
    pid_t j;

    pid_t childID[numMonitors];

    //create child
    while(i<numMonitors){

        j=createchild(i);
        childID[i]=j;

        i++;
    }


    //opening send pipes for every monitor
    int fds[numMonitors];

    for(i=0; i<numMonitors; i++){

        string sname="SMonitor";

        string num=to_string(i);
        sname.append(num);

        fds[i]=open(sname.c_str(),O_WRONLY);
    
        if(fds[i]==-1){

            cout<<"Error opening 'Send Pipe'."<<endl;
            perror("open");
        }
    }


    //opening receive pipes for every monitor
    int fdr[numMonitors];

    for(i=0; i<numMonitors; i++){

        string rname="RMonitor";

        string num=to_string(i);
        rname.append(num);

        fdr[i]=open(rname.c_str(),O_RDONLY);

        if(fdr[i]==-1){

            cout<<"Error opening 'Receive Pipe'."<<endl;
            perror("open");
        }
    }
    

    //send 'size of bloom' and 'buffersize' to every Monitor
    int *pointer1=createint(bufferSize);
    int *pointer2=createint(bloomSize);

    for(i=0; i<numMonitors; i++){

        int write1=write(fds[i],pointer1,sizeof(int));
        int write2=write(fds[i],pointer2,sizeof(int));

        if(write1==-1){

            perror("write 1");
            return;
        }

        if(write2==-1){

            perror("write 2");
            return;
        }
    }

    delete pointer1;
    delete pointer2;



    //open the directory
    DIR* dir;
    struct dirent* en;

    // ../input_dir
    string inputD="../";
    inputDirectory=inputD.append(inputDirectory);

    dir=opendir(inputDirectory.c_str());

    if(dir==NULL){

        perror("opendir");
        return;
    }


    //read the directory and share the subdirectories to Monitors
    int c=0;
    while((en=readdir(dir))!=NULL){

        int comp=strcmp(".",en->d_name);
        if(comp==0){

            continue;
        }

        comp=strcmp("..",en->d_name);
        if(comp==0){

            continue;
        }

        //making the path name: ../input_dir/<subdirectory>
        //string str1="../";
        //str1.append(inputDirectory);

        string str1=inputDirectory;
        
        string str2="/";
        str1.append(str2);

        string subdirectory(en->d_name);
        str1.append(subdirectory);


        //write in 'Send Pipe' (send length of path name and path name)

        int *pointer=createint(str1.length());

        int w1=write(fds[c],pointer,sizeof(unsigned int));
        int w2=write(fds[c],str1.c_str(), str1.length());

        if(w1==-1){

            perror("write 1");
            return;
        }

        if(w2==-1){

            perror("write 2");
            return;
        }

        delete pointer;

        c++;

        //if directories are more than Monitors
        if(c>=numMonitors){
            
            c=0;
        }
    }


    //close the directory
    closedir(dir);


    //update every Monitor for the end of directory
    for(i=0; i<numMonitors; i++){

        string message="End of directory.";

        int *pointer=createint(message.length());

        int w1=write(fds[i],pointer,sizeof(unsigned int));
        int w2=write(fds[i],message.c_str(),message.length());

        if(w1==-1){

            perror("write 1");
            return;
        }

        if(w2==-1){

            perror("write 2");
            return;
        }

        delete pointer;
    }


    for(i=0; i<numMonitors; i++){

        //send message to child
        string message="Send me virus name";

        int s=sendstr(fds[i],message);

        if(s==-1){
            return;
        }

        while(1){

            //read virus name from child
            string *vname=readstr(fdr[i]);

            if(vname==NULL){
                return;
            }

            cout<<*vname<<endl;

            int s=sendstr(fds[i],"OK");

            if(s==-1){
                return;
            }

            if(!vname->compare("End of virus")){

                break;
            }
        }
        




        //send message to child
        /*string str="Send me bloomfilter";

        int ss=sendstr(fds[i],str);

        if(ss==-1){
            return;
        }*/

        //read bloomfilter from child

    }
    

    //wait for child processes before destroy the pipes
    for(i=0; i<numMonitors; i++){

        pid_t result=waitpid(childID[i],NULL,0);

        if(result==-1){

            perror("Failed to waitpid");
        }
    }


    //function to destroy the pipes
    destroypipes(numMonitors);
}



int* createint(int i){

    int* pointer=new int(i);
    return pointer;
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


int readint(int fd){

    int num;

    int r=read(fd,&num,sizeof(int));

    if(r==-1){

        perror("read");
        return -1;
    }

    return num;
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
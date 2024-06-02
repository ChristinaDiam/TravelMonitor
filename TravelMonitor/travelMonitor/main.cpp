#include<iostream>
#include<cstring>

#include "helpmain.h"

using namespace std;

int main(int argc, char *argv[]){

    int i=1;
    int numMonitors;
    int bufferSize;
    int sizeOfBloom;
    string input_dir;

    if(argc==9){

        while(i<8){

            if(!strcmp(argv[i],"-m")){

                numMonitors=atoi(argv[i+1]);

            }else if(!strcmp(argv[i],"-b")){

                bufferSize=atoi(argv[i+1]);

            }else if(!strcmp(argv[i],"-s")){

                sizeOfBloom=atoi(argv[i+1]);

            }else if(!strcmp(argv[i],"-i")){

                input_dir=argv[i+1];

            }else{

                cout<<endl<<"Wrong input."<<endl;
                return 0;
            }
            
            i=i+2;      
        }

    }else{

        cout<<endl<<"Wrong input."<<endl;
        return 0;
    }

    travelmonitor(numMonitors,bufferSize,sizeOfBloom,input_dir);

    return 0;
}
#include<iostream>

#include "helpmain.h"

using namespace std;

int main(int argc, char *argv[]){

    //argv[1] is for reading ,argv[2] is for sending
    monitor(argv[2],argv[1]);

    return 0;
}
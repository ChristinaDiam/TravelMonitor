#!/bin/bash

if [[ ($# -eq 1 || $# -eq 2 ) ]];
then
    
    if [ $1 == "make" ];
    then

        #if we have only one argument (command is "make")
        if [ $# -eq 1 ];
        then

            cd travelMonitor
            make
            cd ../
            cd Monitor
            make
            cd ../

        #else we have two arguments (command is "make run", "make clean" or "make valgrind")
        else

            if [ $2 == "run" ];
            then

                cd travelMonitor
                make run
                cd ../
            
            elif [ $2 == "clean" ]
            then

                cd travelMonitor
                make clean
                cd ../
                cd Monitor
                make clean
                cd ../

            elif [ $2 == "valgrind" ]
            then

                cd travelMonitor
                make valgrind
                cd ../

            else
                echo "Wrong input.\n"
                exit 0
            fi
        fi

    else
        echo "Wrong input.\n"
        exit 0
    fi

else
    echo "Wrong input.\n"
    exit 0
fi
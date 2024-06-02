#!/bin/bash


if [ $# -eq 3 ];
then
    inputfile=$1 
    inputdir=$2
    numfiles_perdir=$3
else
    echo "Wrong input.\n"
    exit 0
fi


#checks if the directory already exists and creates a directory with name "inputdir"
if [ -d "$inputdir" ]
then
    echo "Directory already exists."
    exit 0
else
    mkdir $inputdir
    echo "Directory created."
fi


#reads the Input File given
file=$inputfile
#array to save every word of a line
words=()

#array of counters for the countries
declare -A Ccounters

#fills inputdir with country directories and text files
while read line; do

    #separate line into words
    counter=0
    for word in $line; do 

        words[$counter]=$word
        ((counter++))
    done

    #go inside inputdir to create country directory
    cd $inputdir

    index=3
    country=${words[$index]}

    #checks if the directory already exists and creates a directory for the country
    if [ -d "$country" ]
    then
        echo "Country directory already exists."
    else
        mkdir $country
        echo "Country directory created."

        #we initialize the counter array with 1
        Ccounters[$country]=1

        #go inside country directory
        cd $country

        for (( counter=1; counter<=$numfiles_perdir; counter++ ))
        do
            #creating the name of text file
            string="$country-$counter.txt"

            #create the text file for the records
            touch $string

        done

        cd ../
    fi

    cd ../

done < $file


file=$inputfile

#fills text files with records
while read line; do

    #we need the 4rth word of the record (is the country)
    counter=0
    for word in $line; do 

        if [ $counter -eq 3 ];
        then
           country=$word
        fi

        ((counter++))
    done

    #go inside inputdir
    cd $inputdir

    #go inside country directory to put the record
    cd $country


    counter=${Ccounters[$country]}
        
    #creating the name of text file
    string="$country-$counter.txt"
    
    #counter changes for round robin
    if [ $counter -eq $numfiles_perdir ]
    then
        Ccounters[$country]=1
    else

        ((counter++))
        Ccounters[$country]=$counter
    fi

    #we put the record in the text file
    echo $line>>$string

    cd ../

    cd ../
    
done < $file
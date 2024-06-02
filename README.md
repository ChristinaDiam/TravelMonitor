# Travel Monitor #

This program, named travelMonitor, receives requests from citizens who want to travel to other countries, checks whether they have made the appropriate vaccinations, and approves whether a traveller is allowed to enter a country.  
In addition, a bash script (create_infiles.sh) was implemented to create directories of countries, which containing text files with relevant citizen records.

### The project contains two parts and the bash script: ###
	
The first part is about the parent process (TravelMonitor) and contains the following: main.cpp, bloomfilter.cpp, bloomfilter.h, hash.cpp, hash.h,helpmain.cpp, helpmain.h, list.cpp, list.h, pipes.cpp, pipes.h, child.cpp, countries.cpp, countires.h child.h and Makefile.

The second part is the child process (Monitor) and contains the following: main.cpp, bloomfilter.cpp, bloomfilter.h, hash.cpp, hash.h,
citizen.cpp, citizen.h, helpmain.cpp, helpmain.h, helphelpmain.cpp, helphelpmain.h list.cpp, list.h, skiplist.cpp, skiplist.h, countries.cpp, countires.h and Makefile.


The program, by first calling the travelmonitor function on the parent process part, creates the pipes, which will used to communicate with the child process (two pipes for each Monitor, one to send messages and one to receive messages from the child to the parent (receive)).  
Then it opens all the pipes it created. Then the parent process sends to each Monitor the necessary information (size of bloom, buffersize) and after opening and reading the directory that it accepts as an argument, it also distributes all subdirectories to the Monitors in round-robin alphabetically.

The child process part, via the monitor function, opens the pipes on its own side and reads the messages sent to it by the parent. Then, it reads the text files and initializes the record structures.

### Compiling and running ###

Two Makefiles was created, one for each part of the program, as well as a bash script that joins these two Makefiles and makes it easier to compile and run the program.  

To compile the program, type **bash TheBigMake.sh make**.

To run the program, type **bash TheBigMake.sh make run**.  
*(the bash script can automatically run the program with standard data (e.g. numMonitors=5, buffersize=50, sizeofbloom=100000), as long as the file given to read has the name: input_dir)*

To clean up the temporary files, type **bash TheBigMake.sh make clean**.
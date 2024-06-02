#valgrind ./travelMonitor –m 10 -b 1000 -s 100000 -i input_dir# set compiler options here
CPPFLAGS=-g -Wall -g3 -std=c++11

# set the name of the executable file to compile here
program=travelMonitor

# list object files needed to compile the program
objects=main.o pipes.o child.o helpmain.o countries.o hash.o list.o bloomfilter.o

args= -m 5 -b 50 -s 100000 -i input_dir 


# this makes the program. 
$(program) : $(objects)
	g++ $(CPPFLAGS) $(objects) -o $(program) 


main.o: helpmain.h
pipes.o: pipes.h
child.o: child.h
helpmain.o: helpmain.h
countries.o: countries.h
hash.o: hash.h
list.o: list.h
bloomfilter.o: bloomfilter.h

# this allows to quickly remove all generated files with 'make clean'
clean:
	rm $(program) $(objects)

# run the program with 'make run'.
run: $(program)
	./$(program) $(args)


# run the program with 'valgrind'.
valgrind: $(program)
	valgrind --trace-children=yes ./$(program) $(args)
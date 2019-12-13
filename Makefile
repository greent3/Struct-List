project2: llist.o user_interface.o
	g++ llist.o user_interface.o -o project2

llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall -DdebugMode -c llist.cpp

user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -DdebugMode -c user_interface.cpp


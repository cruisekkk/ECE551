myshell: main.o ffshell.o command.o 
	g++ command.o ffshell.o main.o -Wall -Werror -pedantic -ggdb3 -o myshell

command.o: command_handler.cpp
	g++ -c command_handler.cpp -Wall -Werror -pedantic -ggdb3 -o command.o 

ffshell.o: ff_shell.cpp
	g++ -c ff_shell.cpp -Wall -Werror -pedantic -ggdb3 -o ffshell.o 

main.o: ffosh_run.cpp
	g++ -c ffosh_run.cpp -Wall -Werror -pedantic -ggdb3 -o main.o

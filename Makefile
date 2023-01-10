microshell.o : microshell.c
	gcc microshell.c -o microshell.o -Wall
	chmod +x microshell.o

clean : 
	rm -f microshell microshell.o core *~
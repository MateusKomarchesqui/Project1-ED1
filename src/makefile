all : progrest progrdin
	rm *.o

progrest: main.o TerminalInputs.o hub.o FunctionsQRY.o report.o StaticFunctions.o ItemStruct.o Variables.o
	gcc -fstack-protector-all -std=c99 main.o TerminalInputs.o hub.o FunctionsQRY.o report.o StaticFunctions.o ItemStruct.o Variables.o -o progrest

progrdin: main.o TerminalInputs.o hub.o FunctionsQRY.o report.o DynamicFunctions.o ItemStruct.o Variables.o
	gcc -fstack-protector-all -std=c99 main.o TerminalInputs.o hub.o FunctionsQRY.o report.o DynamicFunctions.o ItemStruct.o Variables.o -o progrdin

main.o : main.c hub.h TerminalInputs.h Variables.h
	gcc -fstack-protector-all -std=c99 -c -g main.c

TerminalInputs.o : TerminalInputs.c voidpointers.h TerminalInputs.h Variables.h
	gcc -fstack-protector-all -std=c99 -c -g TerminalInputs.c

hub.o : hub.c hub.h voidpointers.h ListHeader.h TerminalInputs.h FunctionsQRY.h report.h ItemStruct.h Variables.h
	gcc -fstack-protector-all -std=c99 -c -g hub.c

FunctionsQRY.o : FunctionsQRY.c voidpointers.h ListHeader.h FunctionsQRY.h TerminalInputs.h ItemStruct.h
	gcc -fstack-protector-all -std=c99 -c -g FunctionsQRY.c

report.o : report.c report.h Variables.h
	gcc -fstack-protector-all -std=c99 -c -g report.c

ItemStruct.o : ItemStruct.c ItemStruct.h
	gcc -fstack-protector-all -std=c99 -c -g ItemStruct.c

Variables.o : Variables.c Variables.h
	gcc -fstack-protector-all -std=c99 -c -g Variables.c

DynamicFunctions.o : DynamicFunctions.c voidpointers.h ListHeader.h Variables.h
	gcc -fstack-protector-all -std=c99 -c -g DynamicFunctions.c

StaticFunctions.o : StaticFunctions.c voidpointers.h ListHeader.h Variables.h
	gcc -fstack-protector-all -std=c99 -c -g StaticFunctions.c
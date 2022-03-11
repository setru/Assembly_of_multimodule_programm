all: program
a2.o: project.asm
	nasm -f elf32 project6.asm -o a2.o
a1.o: project.c
	gcc -c -m32 project6.c -o a1.o
program: a2.o a1.o 
	gcc -m32 a1.o a2.o -o a 
clean:
	rm -f a1.o a2.o

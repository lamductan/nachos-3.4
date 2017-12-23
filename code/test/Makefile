# use normal make for this Makefile
#
# Makefile for building user programs to run on top of Nachos
#
# Several things to be aware of:
#
#    Nachos assumes that the location of the program startup routine (the
# 	location the kernel jumps to when the program initially starts up)
#       is at location 0.  This means: start.o must be the first .o passed 
# 	to ld, in order for the routine "Start" to be loaded at location 0
#

# if you are cross-compiling, you need to point to the right executables
# and change the flags to ld and the build procedure for as

GCCDIR = /home/sv/lamductan/gnu-decstation-ultrix/decstation-ultrix/2.95.3/

LDFLAGS = -T script -N
ASFLAGS = -mips2
CPPFLAGS = $(INCDIR)

# if you aren't cross-compiling:
# GCCDIR =
# LDFLAGS = -N -T 0
# ASFLAGS =
# CPPFLAGS = -P $(INCDIR)

PATH = $(GCCDIR):/lib:/usr/bin:/bin

CC = $(GCCDIR)gcc -B/home/sv/lamductan/gnu-decstation-ultrix/
AS = $(GCCDIR)as
LD = $(GCCDIR)ld

CPP = gcc -E
INCDIR =-I../userprog -I../threads
CFLAGS = -G 0 -c $(INCDIR)
 
all: halt shell matmult sort sub createfile ReadPrintInt ReadPrintChar ReadPrintString ascii help cat copy echo reverse insert testExec copy2 printA printB printC sinhvien voinuoc main

start.o: start.s ../userprog/syscall.h
	$(CPP) $(CPPFLAGS) start.c > strt.s
	$(AS) $(ASFLAGS) -o start.o strt.s
	rm strt.s

halt.o: halt.c
	$(CC) $(CFLAGS) -c halt.c
halt: halt.o start.o
	$(LD) $(LDFLAGS) start.o halt.o -o halt.coff
	../bin/coff2noff halt.coff halt

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c
shell: shell.o start.o
	$(LD) $(LDFLAGS) start.o shell.o -o shell.coff
	../bin/coff2noff shell.coff shell

sort.o: sort.c
	$(CC) $(CFLAGS) -c sort.c
sort: sort.o start.o
	$(LD) $(LDFLAGS) start.o sort.o -o sort.coff
	../bin/coff2noff sort.coff sort

matmult.o: matmult.c
	$(CC) $(CFLAGS) -c matmult.c
matmult: matmult.o start.o
	$(LD) $(LDFLAGS) start.o matmult.o -o matmult.coff
	../bin/coff2noff matmult.coff matmult

createfile.o: createfile.c
	$(CC) $(CFLAGS) -c createfile.c
createfile: createfile.o start.o
	$(LD) $(LDFLAGS) start.o createfile.o -o createfile.coff
	../bin/coff2noff createfile.coff createfile

sub.o: sub.c
	$(CC) $(CFLAGS) -c sub.c
sub: sub.o start.o
	$(LD) $(LDFLAGS) start.o sub.o -o sub.coff
	../bin/coff2noff sub.coff sub

ReadPrintInt.o: ReadPrintInt.c
	$(CC) $(CFLAGS) -c ReadPrintInt.c
ReadPrintInt: ReadPrintInt.o start.o
	$(LD) $(LDFLAGS) start.o ReadPrintInt.o -o ReadPrintInt.coff
	../bin/coff2noff ReadPrintInt.coff ReadPrintInt

ReadPrintChar.o: ReadPrintChar.c
	$(CC) $(CFLAGS) -c ReadPrintChar.c
ReadPrintChar: ReadPrintChar.o start.o
	$(LD) $(LDFLAGS) start.o ReadPrintChar.o -o ReadPrintChar.coff
	../bin/coff2noff ReadPrintChar.coff ReadPrintChar

ReadPrintString.o: ReadPrintString.c
	$(CC) $(CFLAGS) -c ReadPrintString.c
ReadPrintString: ReadPrintString.o start.o
	$(LD) $(LDFLAGS) start.o ReadPrintString.o -o ReadPrintString.coff
	../bin/coff2noff ReadPrintString.coff ReadPrintString

ascii.o: ascii.c
	$(CC) $(CFLAGS) -c ascii.c
ascii: ascii.o start.o
	$(LD) $(LDFLAGS) start.o ascii.o -o ascii.coff
	../bin/coff2noff ascii.coff ascii

help.o: help.c
	$(CC) $(CFLAGS) -c help.c
help: help.o start.o
	$(LD) $(LDFLAGS) start.o help.o -o help.coff
	../bin/coff2noff help.coff help

cat.o: cat.c
	$(CC) $(CFLAGS) -c cat.c
cat: cat.o start.o
	$(LD) $(LDFLAGS) start.o cat.o -o cat.coff
	../bin/coff2noff cat.coff cat

copy.o: copy.c
	$(CC) $(CFLAGS) -c copy.c
copy: copy.o start.o
	$(LD) $(LDFLAGS) start.o copy.o -o copy.coff
	../bin/coff2noff copy.coff copy

echo.o: echo.c
	$(CC) $(CFLAGS) -c echo.c
echo: echo.o start.o
	$(LD) $(LDFLAGS) start.o echo.o -o echo.coff
	../bin/coff2noff echo.coff echo

reverse.o: reverse.c
	$(CC) $(CFLAGS) -c reverse.c
reverse: reverse.o start.o
	$(LD) $(LDFLAGS) start.o reverse.o -o reverse.coff
	../bin/coff2noff reverse.coff reverse

insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c
insert: insert.o start.o
	$(LD) $(LDFLAGS) start.o insert.o -o insert.coff
	../bin/coff2noff insert.coff insert

testExec.o: testExec.c
	$(CC) $(CFLAGS) -c testExec.c
testExec: testExec.o start.o
	$(LD) $(LDFLAGS) start.o testExec.o -o testExec.coff
	../bin/coff2noff testExec.coff testExec

copy2.o: copy2.c
	$(CC) $(CFLAGS) -c copy2.c
copy2: copy2.o start.o
	$(LD) $(LDFLAGS) start.o copy2.o -o copy2.coff
	../bin/coff2noff copy2.coff copy2

printA.o: printA.c
	$(CC) $(CFLAGS) -c printA.c
printA: printA.o start.o
	$(LD) $(LDFLAGS) start.o printA.o -o printA.coff
	../bin/coff2noff printA.coff printA

printB.o: printB.c
	$(CC) $(CFLAGS) -c printB.c
printB: printB.o start.o
	$(LD) $(LDFLAGS) start.o printB.o -o printB.coff
	../bin/coff2noff printB.coff printB

printC.o: printC.c
	$(CC) $(CFLAGS) -c printC.c
printC: printC.o start.o
	$(LD) $(LDFLAGS) start.o printC.o -o printC.coff
	../bin/coff2noff printC.coff printC

sinhvien.o: sinhvien.c
	$(CC) $(CFLAGS) -c sinhvien.c
sinhvien: sinhvien.o start.o
	$(LD) $(LDFLAGS) start.o sinhvien.o -o sinhvien.coff
	../bin/coff2noff sinhvien.coff sinhvien

voinuoc.o: voinuoc.c
	$(CC) $(CFLAGS) -c voinuoc.c
voinuoc: voinuoc.o start.o
	$(LD) $(LDFLAGS) start.o voinuoc.o -o voinuoc.coff
	../bin/coff2noff voinuoc.coff voinuoc

main.o: main.c
	$(CC) $(CFLAGS) -c main.c
main: main.o start.o
	$(LD) $(LDFLAGS) start.o main.o -o main.coff
	../bin/coff2noff main.coff main

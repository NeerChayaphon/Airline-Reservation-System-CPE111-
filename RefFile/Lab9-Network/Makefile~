# Makefile for demo programs for Lecture 8
# Networks
# We also need a queue and a min priority queue for this lecture

ifeq ($(OSTYPE),WINDOWS)
	EXECEXT =.exe
	COMP	=__MINGCC__
	PLATFORM	=mingw
else
	EXECEXT =
	COMP	=__GCC__
	PLATFORM	=linux
endif

EXECUTABLES= networkTester$(EXECEXT) queueTesterL$(EXECEXT) 

all : $(EXECUTABLES)

linkedListQueue.o :	linkedListQueue.c abstractQueue.h
	gcc -c linkedListQueue.c

minPriorityQueue.o :	minPriorityQueue.c minPriorityQueue.h
	gcc -c minPriorityQueue.c

queueTester.o :	queueTester.c abstractQueue.h
	gcc -c queueTester.c

linkedListNetwork.o :	linkedListNetwork.c abstractNetwork.h abstractQueue.h
	gcc -c linkedListNetwork.c

networkTester.o :	networkTester.c abstractNetwork.h networkBuilder.h
	gcc -c networkTester.c

networkBuilder.o :	networkBuilder.c abstractNetwork.h networkBuilder.h
	gcc -c networkBuilder.c


# queueTester using the linkedListQueue implementation of the abstract queue
queueTesterL$(EXECEXT) : queueTester.o linkedListQueue.o
	gcc -o queueTesterL$(EXECEXT) queueTester.o linkedListQueue.o

networkTester$(EXECEXT) : networkTester.o linkedListNetwork.o linkedListQueue.o networkBuilder.o minPriorityQueue.o
	gcc -o networkTester$(EXECEXT) networkTester.o linkedListNetwork.o \
              linkedListQueue.o networkBuilder.o minPriorityQueue.o


clean : 
	-rm *.o
	-rm $(EXECUTABLES) 

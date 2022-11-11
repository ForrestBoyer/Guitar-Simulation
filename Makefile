CC = g++
CFLAGS = --std=c++14 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

all: KSGuitarSim MusicTest

KSGuitarSim: KSGuitarSim.o
	$(CC) $(CFLAGS) KSGuitarSim.o  -o KSGuitarSim $(LIB)

KSGuitarSim.o: CircularBuffer.hpp StringSound.hpp KSGuitarSim.cpp
	$(CC) $(CFLAGS) -c KSGuitarSim.cpp

MusicTest: musictest.o
	$(CC) $(CFLAGS) musictest.o  -o musictest $(LIB)

MusicTest.o:
	$(CC) $(CFLAGS) -c musictest.cpp

clean:
	rm *.o KSGuitarSim musictest
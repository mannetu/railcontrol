# change application name here (executable output name)
TARGET=railcontrol

# compiler
CC=g++
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe --std=c++11

GTKLIB=`pkg-config gtkmm-3.0 --cflags --libs`

# linker
LD=g++
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=    main.o canbus.o railroad.o commandline.o #gleisstellbild.o

all: $(OBJS)
		$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o: src/main.cpp
		$(CC) -c $(CCFLAGS) src/main.cpp $(GTKLIB) -o main.o

canbus.o: src/canbus.cpp
		$(CC) -c $(CCFLAGS) src/canbus.cpp -o canbus.o

railroad.o: src/railroad.cpp
		$(CC) -c $(CCFLAGS) src/railroad.cpp -o railroad.o

commandline.o: src/commandline.cpp
		$(CC) -c $(CCFLAGS) src/commandline.cpp -o commandline.o

#gleisstellbild.o: src/gleisstellbild.cpp
#		$(CC) -c $(CCFLAGS) src/gleisstellbild.cpp $(GTKLIB) -o gleisstellbild.o


clean:
		rm -f *.o $(TARGET)

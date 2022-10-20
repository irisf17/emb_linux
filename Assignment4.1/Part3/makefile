OBJECTS = main.o increment.o decrement.o fifo.o
SOURCE = src/main.cpp src/increment.cpp src/decrement.cpp src/fifo.cpp

all: $(OBJECTS)
	g++ $(OBJECTS) -lpthread -o output

main.o:
	g++ -c -lpthread src/main.cpp -I include

increment.o:
	g++ -c -lpthread src/increment.cpp -I include

decrement.o:
	g++ -c -lpthread src/decrement.cpp -I include
fifo.o:
	g++ -c -lpthread src/fifo.cpp -I include

clean:
	rm -f main.o increment.o decrement.o fifo.o  output
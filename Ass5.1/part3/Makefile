OBJS = counter_th.o

all: counter_th

counter_th: $(OBJS)
	gcc -o counter_th $(OBJS) -l pthread 

%.o: src/%.cpp
	gcc -o $@ -c $< -I include

clean:
	rm -f *.o counter_th
	echo Clean done
all : sleeping_ta dining_philosophers

sleeping_ta : sleeping_ta.c
	gcc sleeping_ta.c -Wall -lpthread -o sleeping_ta

dining_philosophers : dining_philosophers.c
	gcc dining_philosophers.c -Wall -lpthread -o dining_philosophers

.PHONY : clean

clean:
	rm sleeping_ta dining_philosophers


all : sleeping_ta dining_philosophers producer_consumer_main

sleeping_ta : sleeping_ta.c
	gcc sleeping_ta.c -Wall -lpthread -o sleeping_ta

dining_philosophers : dining_philosophers.c
	gcc dining_philosophers.c -Wall -lpthread -o dining_philosophers

producer_consumer_main : producer_consumer_main.o producer_and_consumer.o buffer.o
	gcc producer_consumer_main.o producer_and_consumer.o buffer.o -o producer_consumer_main -lpthread

producer_consumer_main.o : producer_consumer_main.c
	gcc -c -Wall producer_consumer_main.c

producer_and_consumer.o : producer_and_consumer.c
	gcc -c -Wall producer_and_consumer.c

buffer.o : buffer.c
	gcc -c -Wall buffer.c

.PHONY : clean

clean:
	rm sleeping_ta dining_philosophers producer_consumer_main *.o


all: cordle

cordle: $(wildcard *.c)
	gcc $(wildcard *.c) -o cordle 

clean:
	rm cordle 
run: all
	./cordle

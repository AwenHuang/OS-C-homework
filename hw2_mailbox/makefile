all:
	gcc Central.c -o central
	gcc External.c -o external
	./external 100 1 &
	./external 22 2 &
	./external 50 3 &
	./external 40 4 &
	./central 60 & 
clean:
	rm -f ./external
	rm -f ./central

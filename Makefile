CC = g++
OBJ = main.o dictionary.o 

dic: $(OBJ)
	$(CC) -std=c++11 $(OBJ) -o $@

.cpp.o:
	$(CC) -std=c++11 -g -c $<

clean:
	rm *.o dic

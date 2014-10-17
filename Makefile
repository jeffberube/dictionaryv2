CC = g++
OBJ = dictionaryv2.o 

dictionaryv2: $(OBJ)
	$(CC) $(OBJ) -g -o $@

.c.o:
	$(CC) -c $<

clean:
	rm *.o dictionaryv2

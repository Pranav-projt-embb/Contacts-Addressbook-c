
OBJ := $(patsubst %.c, %.o, $(wildcard *.c))

26018F_380_AddressBook: $(OBJ)
	gcc -o $@ $^

clean:
	rm -f *.o *.exe 26018F_380_AddressBook

.PHONY: clean

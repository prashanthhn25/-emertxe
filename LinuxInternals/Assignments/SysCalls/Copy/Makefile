$OBJ := my_copy.o main.o
$CFLAGS := -p
$CC := gcc
$DEPS := syscalls.h

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $^ 

main.exe: $(OBJ)
	 gcc $(CFLAGS) -o $@ $^ $(CFLAGS)

$(OBJ):

clean:
	rm *.o *.exe 



SRC_DIR=src
HD_DIR=hd
GCC_FLAG=-Wall
DEBUG=-g

stegano: stegano.o main.o decode.o
	gcc $(DEBUG) -o $@ $^

stegano.o : $(SRC_DIR)/stegano.c
	gcc $(DEBUG) -o $@ -c $^ $(GCC_FLAG)

decode.o : $(SRC_DIR)/decode.c
	gcc $(DEBUG) -o $@ -c $^ $(GCC_FLAG)

main.o: $(SRC_DIR)/main.c $(HD_DIR)/stegano.h $(HD_DIR)/decode.h
	gcc $(DEBUG) -o $@ -c $< $(GCC_FLAG)

clean:
	rm *.o stegano

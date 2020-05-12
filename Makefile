CC=g++
CFLAGS=-g
ALLOBJ=main.o parser.o statichashing.o transactions.o ui.o randomfile.o record.o
DEPS=parser.h statichashing.h transactions.h ui.h randomfile.h record.h
DATAFILES=hash_data.bin hash_index.bin random_data.bin random_index.bin

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myDBMS: $(ALLOBJ)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean

clean:
	rm -f myDBMS
	rm -f $(ALLOBJ)
	rm -f $(DATAFILES)

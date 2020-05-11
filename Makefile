CC=g++
CFLAGS=-g
ALLOBJ=main.o parser.o statichashing.o transactions.o ui.o randomfile.o record.o
DEPS=parser.h statichashing.h transactions.h ui.h randomfile.h record.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

myDBMS: $(ALLOBJ)
	$(CC) -o $@ $^ $(CFLAGS)
.PHONY: clean

clean:
	rm -f myDBMS
	rm -f $(ALLOBJ)

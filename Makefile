
CFLAGS = -Wall -O0 -g3
LDFLAGS = 
LDLIBS = -loauth -lcurl

all: ctw

ctw: main.o tweet.o
	$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean test

clean:
	$(RM) *.exe *.o

test: ctw
	./ctw "Tweet from unreadable tweet"

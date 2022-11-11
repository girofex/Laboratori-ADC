PLAY = malloc_play
TEST = test_vector
VLIB = vector

SOURCES = Makefile COPYING README $(VLIB).c $(VLIB).h $(TEST).c $(PLAY).c
MAINDIR = starwarsrealloc

all: $(VLIB).o $(TEST) $(PLAY)

$(PLAY) : $(PLAY).c
	gcc -o $(PLAY) $(PLAY).c

$(VLIB).o: $(VLIB).c $(VLIB).h
	gcc -c $(VLIB).c

$(TEST): $(TEST).o $(VLIB).o
	gcc -o $(TEST) $(TEST).o $(VLIB).o

$(TEST).o: $(TEST).c $(VLIB).h
	gcc -c $(TEST).c

clean:
	/bin/rm -f a.out *.o $(TEST) $(PLAY)

tgz: clean $(SOURCES)
	cd ../.. ; tar cvzf $(MAINDIR)/$(MAINDIR).tgz $(MAINDIR)/src


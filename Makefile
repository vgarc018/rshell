SRCDIR=./src
BINDIR=./bin

all:
	@mkdir -p $(BINDIR)
	g++ -Wall -Werror -ansi -pedantic $(SRCDIR)/rshell.cpp -o $(BINDIR)/rshell

clean:
	@rm -r $(BINDIR)

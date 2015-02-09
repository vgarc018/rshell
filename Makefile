SRCDIR=./src
BINDIR=./bin

all:
	@mkdir -p $(BINDIR)
	g++ -Wall -Werror -ansi -pedantic $(SRCDIR)/rshell.cpp -o $(BINDIR)/rshell
	g++ -Wall -Werror -ansi -pedantic $(SRCDIR)/ls.cpp -o $(BINDIR)/ls
clean:
	@rm -r $(BINDIR)

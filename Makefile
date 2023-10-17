CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OUTDIR = bin
OUTFILE = $(OUTDIR)/titletwist
SRCDIR = src
OBJDIR = obj
INCLUDE = -I$(SRCDIR)

_DEPS = book.h library.h loan.h persistence.h
DEPS = $(patsubst %,$(SRCDIR)/%,$(_DEPS))

_OBJ = book.o library.o main.o persistence.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE)

$(OUTFILE): $(OBJ)
	mkdir -p $(OUTDIR)
	$(CC) -o $@ $^ $(CFLAGS)

all: $(OUTFILE)

clean:
	rm -rf $(OBJDIR) $(OUTDIR)

.PHONY: all clean

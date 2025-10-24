CC      ?= gcc
CFLAGS  ?= -O2 -std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=200809L
LDLIBS  ?= -lfl

EXEC    := saunalang
LEXER   := lexer.l
PARSER  := parser.y
LEXC    := lexer.yy.c
PARSEC  := parser.tab.c
PARSEH  := parser.tab.h
EXAMPLE := ../examples.sl   # ajuste se seu exemplo tiver outro nome

all: $(EXEC)
	@echo "✅ binário: ./$(EXEC)"

$(EXEC): $(PARSEC) $(LEXC)
	$(CC) $(CFLAGS) -o $@ $(PARSEC) $(LEXC) $(LDLIBS)

$(PARSEC) $(PARSEH): $(PARSER)
	bison -Wall -Wcounterexamples -d $(PARSER)

$(LEXC): $(LEXER) $(PARSEH)
	flex -o $(LEXC) $(LEXER)

run: $(EXEC)
	@./$(EXEC) < $(EXAMPLE)

clean:
	rm -f $(EXEC) $(PARSEC) $(PARSEH) $(LEXC)

.PHONY: all run clean

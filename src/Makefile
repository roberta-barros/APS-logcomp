CC      ?= gcc
CFLAGS  ?= -O2 -std=c99 -Wall -Wextra -D_POSIX_C_SOURCE=200809L
LDLIBS  ?= -lfl -lm

EXEC    := saunalang
LEXER   := lexer.l
PARSER  := parser.y
LEXC    := lexer.yy.c
PARSEC  := parser.tab.c
PARSEH  := parser.tab.h
VMSRC   := saunavm.c
VMHDR   := saunavm.h

# Diretório de exemplos
EXAMPLES := ../examples

all: $(EXEC)
	@echo "✅ Compilação concluída: ./$(EXEC)"
	@echo ""
	@echo "Uso: ./$(EXEC) [opções] <arquivo.snl>"
	@echo "  -d, --debug   Mostra assembly e estado final"
	@echo "  -a, --asm     Mostra apenas assembly gerado"

$(EXEC): $(PARSEC) $(LEXC) $(VMSRC)
	$(CC) $(CFLAGS) -o $@ $(PARSEC) $(LEXC) $(VMSRC) $(LDLIBS)

$(PARSEC) $(PARSEH): $(PARSER) $(VMHDR)
	bison -Wall -Wcounterexamples -d $(PARSER)

$(LEXC): $(LEXER) $(PARSEH)
	flex -o $(LEXC) $(LEXER)

# Targets para rodar exemplos
run-ex1: $(EXEC)
	@echo "=== Exemplo 1: Básico ==="
	./$(EXEC) $(EXAMPLES)/ex1.snl

run-ex2: $(EXEC)
	@echo "=== Exemplo 2: Comparação por peso ==="
	./$(EXEC) $(EXAMPLES)/ex2.snl

run-ex3: $(EXEC)
	@echo "=== Exemplo 3: Erro de sintaxe ==="
	-./$(EXEC) $(EXAMPLES)/ex3.snl

run-all: $(EXEC)
	@echo "========================================="
	@echo "Rodando todos os exemplos válidos..."
	@echo "========================================="
	@echo ""
	@for f in $(EXAMPLES)/*.snl; do \
		if [ "$$(basename $$f)" != "ex3.snl" ]; then \
			echo ">>> Executando $$f"; \
			./$(EXEC) $$f; \
			echo ""; \
		fi; \
	done

test: $(EXEC)
	@echo "=== Testes automatizados ==="
	@./test.sh

clean:
	rm -f $(EXEC) $(PARSEC) $(PARSEH) $(LEXC) *.o

.PHONY: all run-ex1 run-ex2 run-ex3 run-all test clean

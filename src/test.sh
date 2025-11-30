#!/bin/bash

EXEC="./saunalang"
EXAMPLES="../examples"
PASSED=0
FAILED=0

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' 

echo "=========================================="
echo "  SaunaLang - Testes Automatizados"
echo "=========================================="
echo ""

run_test() {
    local file=$1
    local should_fail=$2
    local name=$(basename "$file")
    
    echo -n "Testando $name... "
    
    output=$($EXEC "$file" 2>&1)
    result=$?
    
    if [ "$should_fail" = "true" ]; then
        if [ $result -ne 0 ]; then
            echo -e "${GREEN}OK${NC} (erro esperado detectado)"
            ((PASSED++))
        else
            echo -e "${RED}FALHOU${NC} (deveria dar erro)"
            ((FAILED++))
        fi
    else
        if [ $result -eq 0 ]; then
            echo -e "${GREEN}OK${NC}"
            ((PASSED++))
        else
            echo -e "${RED}FALHOU${NC}"
            echo "Output: $output"
            ((FAILED++))
        fi
    fi
}

if [ ! -f "$EXEC" ]; then
    echo -e "${RED}Erro: Executável não encontrado. Execute 'make' primeiro.${NC}"
    exit 1
fi

echo "--- Testes de Sintaxe Válida ---"
for f in $EXAMPLES/ex1.snl $EXAMPLES/ex2.snl $EXAMPLES/ex4.snl $EXAMPLES/ex5.snl $EXAMPLES/ex6.snl $EXAMPLES/ex7.snl; do
    if [ -f "$f" ]; then
        run_test "$f" "false"
    fi
done

echo ""
echo "--- Testes de Detecção de Erro ---"
run_test "$EXAMPLES/ex3.snl" "true"

echo ""
echo "Resultados: ${GREEN}$PASSED passaram${NC}, ${RED}$FAILED falharam${NC}"

if [ $FAILED -gt 0 ]; then
    exit 1
fi
exit 0

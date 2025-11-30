# SaunaLang — Linguagem de Controle de Sauna

Uma linguagem de programação simples e expressiva, projetada para controle de sistemas de sauna. Inclui uma máquina virtual própria (**SaunaVM**) que simula um modelo térmico realista.

## Objetivos do Projeto

Este projeto implementa uma linguagem de programação completa com:

1. **Linguagem de Programação** - SaunaLang com sintaxe em português
2. **Estruturas Básicas** - Variáveis, condicionais e loops
3. **Análise Léxica e Sintática** - Implementada com Flex e Bison
4. **Máquina Virtual Própria** - SaunaVM (Turing-completa)
5. **Exemplos de Teste** - 8 programas demonstrando todas as características

## Arquitetura

### SaunaLang (Linguagem)

Linguagem de domínio específico em português com palavras-chave intuitivas:

```
potencia 80;
aquecer 30s;

se (temp > 70) : {
    imprimir "Sauna aquecida!";
} senao : {
    imprimir "Aguardando...";
}
```

### SaunaVM (Máquina Virtual)

VM minimalista e **Turing-completa** com:

- **2 registradores de propósito geral**: R0, R1
- **2 sensores readonly**: TEMP (temperatura), PESO (peso)
- **Stack** para operações e variáveis
- **Modelo térmico** simulado

## EBNF

```ebnf
programa       = { declaracao } EOF ;
declaracao     = acao ";" | atribuicao ";" | if_stmt | while_stmt ;

acao           = "aquecer" tempo | "potencia" numero | "imprimir" saida ;
atribuicao     = "set" ident "=" expr ;

if_stmt        = "se" cond ":" bloco [ "senao" ":" bloco ] ;
while_stmt     = "enquanto" loop_cond ":" bloco ;
bloco          = "{" { declaracao } "}" ;

cond           = pred { ( "e" | "ou" ) pred } ;
comparacao     = lado_esq comparador lado_dir ;
comparador     = "==" | "!=" | "<" | "<=" | ">" | ">=" ;
loop_cond      = "sempre" | cond ;

sensor         = "temp" | "peso" ;
tempo          = numero "s" ;
```

## Instruções da VM

| Instrução | Descrição |
|-----------|-----------|
| `SET Rx n` | Rx := n |
| `MOV Rx Ry` | Rx := Ry |
| `LOAD Rx S` | Rx := sensor (TEMP/PESO) |
| `STORE var Rx` | variável := Rx |
| `LOADV Rx var` | Rx := variável |
| `ADD Rx Ry` | Rx := Rx + Ry |
| `SUB Rx Ry` | Rx := Rx - Ry |
| `CMP Rx Ry` | Compara e seta flags |
| `JMP/JEQ/JNE/JLT/JLE/JGT/JGE` | Saltos |
| `HEAT n` | Aquece por n segundos |
| `POW n` | Define potência (0-100) |
| `PRINT Rx` | Imprime valor |
| `PRINTS idx` | Imprime string |
| `PUSH/POP Rx` | Operações de pilha |
| `HALT` | Para execução |

### Modelo Térmico

A SaunaVM simula aquecimento realista:

```
ΔT = (potência × 0.15 - (T - 25) × 0.05) / √(peso/100)
```

- Aquecimento proporcional à potência
- Resfriamento natural para temperatura ambiente (25°C)
- Peso afeta taxa de aquecimento

## Compilação e Execução

### Requisitos

- GCC
- Flex
- Bison
- Make

### Compilar

```bash
cd src
make
```

### Executar

```bash
./saunalang [opções] <arquivo.snl>

Opções:
  -d, --debug   Mostra assembly gerado e estado final
  -a, --asm     Mostra apenas assembly gerado
  -h, --help    Mostra ajuda
```

### Exemplos

```bash
# Executa exemplo básico
./saunalang ../examples/ex1.snl

# Executa com debug (mostra assembly)
./saunalang -d ../examples/ex5.snl

# Executa todos os exemplos
make run-all

# Roda testes automatizados
make test
```

## Files do projeto

```
saunalang/
├── SaunaLang.ebnf          # Gramática formal
├── README.md               # Este arquivo
├── src/
│   ├── Makefile            # Build system
│   ├── lexer.l             # Analisador léxico (Flex)
│   ├── parser.y            # Analisador sintático + codegen (Bison)
│   ├── saunavm.h           # Header da VM
│   ├── saunavm.c           # Implementação da VM
│   └── test.sh             # Script de testes
└── examples/
    ├── ex1.snl             # Teste básico de ações
    ├── ex2.snl             # Comparação por peso
    ├── ex3.snl             # Erro de sintaxe (proposital)
    ├── ex4.snl             # Loop com contador
    ├── ex5.snl             # Aquecimento até alvo
    ├── ex6.snl             # Todos operadores
    └── ex7.snl             # Sessão completa
```

## Exemplos de Programas

### Exemplo 1: Básico
```
potencia 60;
aquecer 30s;
set alvo = temp;
imprimir "Temperatura:";
imprimir alvo;
```

### Exemplo 5: Aquecimento até Alvo
```
potencia 100;
enquanto (temp < 80) : {
    aquecer 10s;
    imprimir temp;
}
imprimir "Meta atingida!";
```

### Exemplo 7: Sessão Completa
```
// Pré-aquecimento
potencia 100;
aquecer 20s;

// Ajuste por peso
se (peso > 150) : {
    potencia 80;
    aquecer 40s;
} senao : {
    potencia 70;
    aquecer 30s;
}

// Estabilização
enquanto (temp < 100) : {
    potencia 60;
    aquecer 5s;
}

// Resfriamento
potencia 0;
aquecer 10s;
```

## Por que a SaunaVM é Turing-Completa?

A SaunaVM é Turing-completa porque possui:

1. **Memória ilimitada** (em teoria): registradores + pilha + variáveis
2. **Operações aritméticas**: ADD, SUB
3. **Comparações**: CMP com flags
4. **Saltos condicionais**: JEQ, JNE, JLT, JLE, JGT, JGE
5. **Saltos incondicionais**: JMP

Isso permite implementar qualquer algoritmo computável, incluindo uma máquina de Turing universal.

## Saída de Exemplo

```
$ ./saunalang -d examples/ex5.snl

OK: análise léxica e sintática concluída.
Programa compilado: 18 instruções

=== Disassembly ===
  0000: PRINTS   "Sistema de aquecimento automatico"
  0001: PRINTS   "Meta: atingir 80 graus"
  0002: POW      100
  ...
===================

=== Executando na SaunaVM ===

Sistema de aquecimento automatico
Meta: atingir 80 graus
[SAUNA] Potência ajustada para 100%
Temperatura inicial:
25
...
[SAUNA] Sessão encerrada. Temperatura final: 85°C
```


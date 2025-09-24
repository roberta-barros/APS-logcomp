# Microl — Linguagem para VMs simples

**Entrega parcial (#1):** Gramática em EBNF + exemplo.

Microl é uma linguagem de alto nível e baixo atrito que pode ser usada para VMs já prontas (MicrowaveVM) ou VMs próprias. 
Ela oferece variáveis, expressões aritméticas/booleanas, `if/elif/else`, `while/for/repeat`, I/O por memória mapeada (`MEM[i]`) e um escape para instruções nativas da VM (`instr X(...)`).

## Palavras‑reservadas
`let, const, sensor, register, fn, int, bool, byte, if, elif, else, while, for, repeat, until, break, continue, return, print, instr, true, false`

## EBNF
A gramática completa está em [`microl.ebnf`](microl.ebnf).

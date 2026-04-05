
# 🌳 Árvore Binária de Busca em C

Implementação de uma **Binary Search Tree (BST)** em C com leitura de registros a partir de arquivo CSV.

---

## 📋 Sobre

Este projeto constrói uma árvore binária de busca dinamicamente a partir de um arquivo `.txt` no formato CSV (separado por `;`). Cada nó armazena um registro com **chave inteira**, **nome** e **valor float**.

---

## 📁 Estrutura

```
.
├── main.c       # Código-fonte principal
└── input.txt    # Arquivo de entrada com os registros
```

---

## 📄 Formato do Arquivo de Entrada

Um registro por linha, no formato:

```
chave;nome completo;valor
```

**Exemplo (`input.txt`):**
```
0;Matheus Gerhard;2500.00
30;Ana Paula;1800.50
190;Carlos Silva;3200.75
```

| Campo  | Tipo   | Descrição                          |
|--------|--------|------------------------------------|
| chave  | int    | Identificador único (índice da BST)|
| nome   | string | Nome completo (suporta espaços)    |
| valor  | float  | Valor numérico                     |

---

## ⚙️ Funções

| Função | Descrição |
|---|---|
| `inserirReg()` | Insere um registro na BST recursivamente |
| `buscaReg()` | Busca um registro pela chave (iterativo) |
| `arquivoToArvore()` | Lê o CSV e popula a árvore |
| `retornaQtd()` | Conta as linhas do arquivo de entrada |
| `liberarArvore()` | Libera toda a memória da árvore (pós-ordem) |

---

## 🚀 Como usar

**Compilar:**
```bash
gcc main.c -o bst
```

**Executar:**
```bash
./bst
```

**Saída esperada:**
```
Achou o registro de indice 30 : Ana Paula
```

---

## 🔧 Detalhes Técnicos

- Usa `%[^;]` no `fscanf` para ler nomes com espaços até o delimitador `;`
- `strdup()` aloca memória individual para cada nome nos nós
- `liberarArvore()` percorre em **pós-ordem** para evitar vazamento de memória

---

## ⚠️ Limitações

- Nome suporta até **99 caracteres**
- Árvore **não balanceada** (não é AVL nem Red-Black)
- Chaves duplicadas são **rejeitadas** com aviso no terminal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//atoi() str -> int
//atof() str -> double
//atol() str -> long
//itoa() int -> str

typedef struct registro {
    struct registro *dir;
    struct registro *esq;
    int chave;
    char* nome;
    float valor;


} Registro;

void liberarArvore(Registro* no) {
    if (no == NULL) return;
    liberarArvore(no->esq);
    liberarArvore(no->dir);
    free(no->nome); // libera o strdup()
    free(no);
}

Registro* buscaReg(Registro* no, int chave) {
    while (no != NULL) {
        if (no->chave == chave) {
            printf("\nAchou o registro de indice %d : %s \n",chave,no->nome);
            return no;
        }else if (no->chave > chave) {
            no = no->esq;
        }else {
            no = no->dir;
        }
    }
    return NULL;
}


Registro* inserirReg(Registro* no, int chave, char* nome, float valor) {
    if (no == NULL) {
        no = (Registro*) malloc(sizeof(Registro));
        no->chave = chave;
        no->nome = strdup(nome);
        no->valor = valor;
        no->dir = NULL;
        no->esq = NULL;
    }else if (no->chave > chave) {
        no->esq = inserirReg(no->esq, chave, nome, valor);
    }else if (no->chave < chave) {
        no->dir = inserirReg(no->dir, chave, nome, valor);
    }else {
        printf("\nInserção Inválida!\n");

    }
    return no;
}


Registro* arquivoToArvore(char* nome, Registro* no, int qtd) {
    FILE *file = fopen(nome, "r");

    if (file == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }
    for (int i = 0; i < qtd; i++) {
        int chave;
        char nomereg[100];
        float valor;
        fscanf(file, "%d;%[^;];%f", &chave, nomereg, &valor);
        no = inserirReg(no, chave, nomereg, valor);
    }


    fclose(file);
    return no;
}



//Retorna a quantidade de linhas do arquivo txt
int retornaQtd(char *nome) {
    FILE *file = fopen(nome, "r");
    if (file == NULL) {
        printf("Erro na abertura do arquivo\n");
        return 0;
    }
    int qtd = 0;
    char c;
    qtd++;
    while (!feof(file)) {
        c = fgetc(file);
        if (c == '\n') {
            qtd++;

        }

    }
    fclose(file);
    return qtd;
}



int main(void) {
    //vetor dos indices
    Registro *no;
    no = NULL;
    char nome[50] = "input.txt";
    int qtd = retornaQtd(nome);

    no = arquivoToArvore(nome,no,qtd);
    buscaReg(no, 30);

    liberarArvore(no);
    return 0;
}
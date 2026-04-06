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

int getAltura(Registro *raiz) {
    if (raiz == NULL) {
        return -1; // Convenção: árvore vazia tem altura -1
    } else {
        int esq = getAltura(raiz->esq);
        int dir = getAltura(raiz->dir);

        if (esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
}

Registro* buscaReg(Registro* no, int chave) {
    while (no != NULL) {
        if (no->chave == chave) {
            printf("\nAchou o registro de indice %d : %s \nSalario : %.2f\n",chave,no->nome,no->valor);
            return no;
        }else if (no->chave > chave) {
            no = no->esq;
        }else {
            no = no->dir;
        }
    }
    printf("Registro nao encontrado");
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
        printf("\nInsercao Inválida!\n");

    }
    return no;
}


Registro* arquivoToArvore(char* nome, Registro* no) {
    FILE *file = fopen(nome, "r");

    if (file == NULL) {
        printf("Erro na abertura do arquivo\n");
        return NULL;
    }

    int chave;
    char nomereg[100];
    float valor;

    while (fscanf(file, "%d;%[^;];%f\n", &chave, nomereg, &valor) == 3) {
        no = inserirReg(no, chave, nomereg, valor);
    }

    fclose(file);
    return no;
}

Registro* constroiBalanceada(Registro** elementos, int inicio, int fim) {
    if (inicio > fim) return NULL;

    int meio = (inicio + fim) / 2;
    Registro* noNovo = elementos[meio];

    if (noNovo != NULL) {
        noNovo->esq = constroiBalanceada(elementos, inicio, meio - 1);
        noNovo->dir = constroiBalanceada(elementos, meio + 1, fim);
    }

    return noNovo;
}
//Preenche o vetor "elementos" com os endereços de memória da árvore ORDENADA
void inorder(Registro* no, Registro** elementos, int* i) {
    if (no == NULL) return;
    inorder(no->esq, elementos, i);
    elementos[*i] = no;
    (*i)++;
    inorder(no->dir, elementos, i);
}


//Retorna a quantidade de linhas do arquivo txt
int contaNos(Registro* no) {
    if (no == NULL) return 0;
    return 1 + contaNos(no->esq) + contaNos(no->dir);
}


int main(void) {
    //vetor dos indices
    Registro *no;
    no = NULL;
    char nome[50] = "input.txt";
    char confirm = 's';
    int id;
    //Criação da árvore (desbalanceada)
    no = arquivoToArvore(nome,no);
    printf("\n%d\n", getAltura(no));
    //Criando o vetor ordenado das chaves da árvore
    int qtd = contaNos(no);
    printf("\n%d\n",qtd);
    Registro** elementos = malloc(qtd * sizeof(Registro*));
    int i = 0;
    inorder(no, elementos, &i);
    //Ordenando a árvore
    no = constroiBalanceada(elementos, 0, qtd - 1);
    printf("\n%d\n", getAltura(no));
    free(elementos);



    while (confirm != 'n') {
        printf("\nDigite um id para buscar:\n");
        scanf("%d", &id);
        buscaReg(no, id);
        printf("\nDeseja continuar a buscar? (aperte n para sair):\n");
        scanf(" %c", &confirm);
    }


    liberarArvore(no);
    return 0;
}
#include <stdio.h>
typedef struct registro {
    struct registro *dir;
    struct registro *esq;
    struct registro *meio;
    int index;
    char nome[50];
    float valor;

} Registro;


Registro pegaRegistro(int index) {
    Registro registro;
    return registro;
};

int retornaQtd(char *nome) {
    FILE *file = fopen(nome, "r");

    int qtd = 0;
    char c;
    qtd++;
    while (!feof(file)) {
        c = fgetc(file);
        printf("%c", c);
        if (c == '\n') {
            qtd++;

        }

    }
    return qtd;
}



int main(void) {
    const char filename[50] = "input.txt";
    int valor = retornaQtd(filename);
    printf("\nRegistros: %d\n", valor);




    return 0;
}
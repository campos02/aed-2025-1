#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct No {
    int valor;
    struct No* noEsquerdo;
    struct No* noDireito;
} No;

int Altura(No* raiz) {
    if (raiz == NULL)
        return 0;
    
    int alturaEsquerda = Altura(raiz->noEsquerdo);
    int alturaDireita = Altura(raiz->noDireito);

    if (alturaEsquerda > alturaDireita)
        return alturaEsquerda + 1;
    else
        return alturaDireita + 1;
}

int FatorDeBalanceamento(No* raiz) {
    return Altura(raiz->noEsquerdo) - Altura(raiz->noDireito);
}

void Balancear(No** raiz) {
    int fatorDeBalanceamento = FatorDeBalanceamento(*raiz);
    if (fatorDeBalanceamento > 1) {
        if (FatorDeBalanceamento((*raiz)->noEsquerdo) < 0) {
            No* temp = (*raiz)->noEsquerdo->noDireito;
            (*raiz)->noEsquerdo->noDireito = temp->noEsquerdo;
            
            temp->noEsquerdo = (*raiz)->noEsquerdo;
            (*raiz)->noEsquerdo = temp->noDireito;

            temp->noDireito = *raiz;
            *raiz = temp;
        } else {
            No* temp = (*raiz)->noEsquerdo;
            (*raiz)->noEsquerdo = temp->noDireito;

            temp->noDireito = *raiz;
            *raiz = temp;
        }
    } else if (fatorDeBalanceamento < -1) {
        if (FatorDeBalanceamento((*raiz)->noDireito) > 0) {
            No* temp = (*raiz)->noDireito->noEsquerdo;
            (*raiz)->noDireito->noEsquerdo = temp->noDireito;
            
            temp->noDireito = (*raiz)->noDireito;
            (*raiz)->noDireito = temp->noEsquerdo;

            temp->noEsquerdo = *raiz;
            *raiz = temp;
        } else {
            No* temp = (*raiz)->noDireito;
            (*raiz)->noDireito = temp->noEsquerdo;

            temp->noEsquerdo = *raiz;
            *raiz = temp;
        }
    }
}

void Inserir(No** raiz, int valor) {
    if (*raiz == NULL) {
        *raiz = malloc(sizeof(No));
        (*raiz)->valor = valor;
        (*raiz)->noEsquerdo = NULL;
        (*raiz)->noDireito = NULL;
        return;
    }

    if (valor > (*raiz)->valor)
        Inserir(&(*raiz)->noDireito, valor);
    else if (valor < (*raiz)->valor)
        Inserir(&(*raiz)->noEsquerdo, valor);
    else
        return;

    Balancear(&(*raiz));
}

int VerificarArvore(No* raiz) {
    if (raiz == NULL)
        return 1;
    
    if (!VerificarArvore(raiz->noEsquerdo))
        return 0;
    if (!VerificarArvore(raiz->noDireito))
        return 0;

    int fatorDeBalanceamento = FatorDeBalanceamento(raiz);
    if (fatorDeBalanceamento > 1 || fatorDeBalanceamento < -1)
        return 0;

    return 1;
}

int main() {
    int nos = 0;
    printf("Digite a quantidade de nos: ");
    scanf("%d", &nos);

    if (nos < 1)
        return 1;

    No* raiz;
    srand(time(0));

    for (int i = 0; i < nos; i++) {
        Inserir(&raiz, rand());
    }

    if (VerificarArvore(raiz))
        printf("\nArvore AVL");
    else
        printf("\nArvore nao AVL");
}
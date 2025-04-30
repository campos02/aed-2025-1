#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AdicionarNome(char *nomes);
void RemoverNome(char **nomes);

int main() {
    int escolha;
    char *nomes = calloc(1, sizeof(char));

    while (1) {
        printf("1 - Adicionar nome   2 - Remover nome   3 - Listar nomes   4 - Sair\n");
        scanf("%d", &escolha);
        getchar();

        switch (escolha) {
            case 1:
                AdicionarNome(nomes);
                break;
            case 2:
                RemoverNome(&nomes);
                break;
            case 3:
                printf("%s", nomes);
                break;
            case 4:
                free(nomes);
                return 0;
        }

        printf("\n");
    }
}

void AdicionarNome(char *nomes) {
    char nome[80];

    printf("Digite o nome: ");
    scanf("%79[^\n]s", nome);
    getchar();

    nomes = realloc(nomes, strlen(nomes) + strlen(nome) + 2);
    strcat(nomes, nome);
    strcat(nomes, "\n");
}

void RemoverNome(char **nomes) {
    char nome[80];

    printf("Digite o nome: ");
    scanf("%79[^\n]s", nome);
    getchar();

    char *removido = calloc(strlen(*nomes) + 2, sizeof(char));
    char *token = strtok(*nomes, "\n");

    while (token != NULL) {
        // Se forem diferentes
        if (strcmp(nome, token)) {
            strcat(removido, token);
            strcat(removido, "\n");
        }

        token = strtok(NULL, "\n");
    }

    free(*nomes);
    *nomes = removido;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int escolha;
    char nomes[] = "";

    while (1) {
        printf("1 - Adicionar nome   2 - Remover nome   3 - Listar nomes   4 - Sair\n");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                AdicionarNome(nomes);
                break;
            case 2:
                RemoverNome(nomes);
                break;
            case 3:
                printf("%s", nomes);
                break;
            case 4:
                return 0;
        }

        printf("\n");
    }
}

void AdicionarNome(char *nomes) {
    char *nome;

    printf("Digite o nome: ");
    scanf("%s", nome);

    strcat(nomes, nome);
    strcat(nomes, "\n");
}

void RemoverNome(char *nomes) {
    char *nome;

    printf("Digite o nome: ");
    scanf("%s", nome);

    strtok(nomes, nome);
}

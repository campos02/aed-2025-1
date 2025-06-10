#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void AddContact(void **pBuffer, int *pBufferSize);
void RemoveContact(void **pBuffer, int *pBufferSize);
void SearchContact(void **pBuffer, int *pBufferSize);
void ListContacts(void *pBuffer, int *pBufferSize);

int main() {
    // Option - pBuffer size - current offset
    void *pBuffer = malloc(sizeof(int) + sizeof(int) + sizeof(int));
    int *pBufferSize = (int*)pBuffer + 1;
    *pBufferSize = 3 * sizeof(int);

    int *option = (int*)pBuffer;
    do
    {
        printf("\n1 - Adicionar Pessoa\n2 - Remover Pessoa\n3 - Buscar Pessoa\n4 - Listar Todos\n5 - Sair\n");
        scanf("%d", option);
        getchar(); // Remove trailing newline from stdout
        
        switch (*option) {
            case 1:
                AddContact(&pBuffer, pBufferSize);
                break;
            case 2:
                RemoveContact(&pBuffer, pBufferSize);
                break;
            case 3:
                SearchContact(&pBuffer, pBufferSize);
                break;
            case 4:
                ListContacts(pBuffer, pBufferSize);
                break;
            case 5:
                break;
        }

        // Reassign in case a realloc was performed(most options)
        pBufferSize = (int*)pBuffer + 1;
        option = (int*)pBuffer;
    } while (*option != 5);

    free(pBuffer);
}

void AddContact(void **pBuffer, int *pBufferSize) {
    int *currentOffset = (int*)*pBuffer + 2;
    *currentOffset = *pBufferSize;

    // Use a 100 char buffer for both name and email
    *pBufferSize += 200 * sizeof(char) + sizeof(int);
    *pBuffer = realloc(*pBuffer, *pBufferSize);

    // Reassign after realloc
    pBufferSize = (int*)*pBuffer + 1;
    currentOffset = (int*)*pBuffer + 2;

    printf("\nDigite o nome do contato: ");
    char *name = (char*)*pBuffer + *currentOffset;
    scanf("%99[^\n]s", name);
    getchar(); // Remove trailing newline from stdout
    *currentOffset += strlen(name) + 1;
    
    printf("Digite a idade do contato: ");
    int *age = (int*)((char*)*pBuffer + *currentOffset);
    scanf("%d", age);
    getchar(); // Remove trailing newline from stdout
    *currentOffset += sizeof(int);

    printf("Digite o email do contato: ");
    char *email = (char*)*pBuffer + *currentOffset;
    scanf("%99[^\n]s", email);
    getchar(); // Remove trailing newline from stdout
    *currentOffset += strlen(email) + 1;

    *pBufferSize = *currentOffset;
    *pBuffer = realloc(*pBuffer, *pBufferSize);
}

void RemoveContact(void **pBuffer, int *pBufferSize) {
    // 100 char buffer to hold search input email
    *pBufferSize += 100 * sizeof(char);
    *pBuffer = realloc(*pBuffer, *pBufferSize);
    pBufferSize = (int*)*pBuffer + 1;

    char *searchEmail = (char*)*pBuffer + *pBufferSize - 100 * sizeof(char);
    printf("\nEmail do contato a ser removido: ");
    scanf("%99[^\n]s", searchEmail);
    getchar(); // Remove trailing newline from stdout

    int *currentOffset = (int*)*pBuffer + 2;
    *currentOffset = 3 * sizeof(int);

    while (*currentOffset < *pBufferSize) {
        char *name = (char*)*pBuffer + *currentOffset;
        *currentOffset += strlen(name) + 1;
        
        int *age = (int*)((char*)*pBuffer + *currentOffset);
        *currentOffset += sizeof(int);

        char *email = (char*)*pBuffer + *currentOffset;
        *currentOffset += strlen(email) + 1;

        if (strcmp(email, searchEmail) == 0) {
            *pBufferSize -= strlen(name) + 1 + sizeof(int) + strlen(email) + 1;
            
            memmove((char*)*pBuffer + *currentOffset - (strlen(name) + 1 + sizeof(int) + strlen(email) + 1),
                (char*)*pBuffer + *currentOffset,
                strlen(name) + 1 + sizeof(int) + strlen(email) + 1);
            
            break;
        }
    }

    *pBufferSize -= 100 * sizeof(char);
    *pBuffer = realloc(*pBuffer, *pBufferSize);
}

void SearchContact(void **pBuffer, int *pBufferSize) {
    // 100 char buffer to hold search input email
    *pBufferSize += 100 * sizeof(char);
    *pBuffer = realloc(*pBuffer, *pBufferSize);
    pBufferSize = (int*)*pBuffer + 1;

    char *searchEmail = (char*)*pBuffer + *pBufferSize - 100 * sizeof(char);
    printf("\nEmail a ser buscado: ");
    scanf("%99[^\n]s", searchEmail);
    getchar(); // Remove trailing newline from stdout

    int *currentOffset = (int*)*pBuffer + 2;
    *currentOffset = 3 * sizeof(int);

    while (*currentOffset < *pBufferSize) {
        char *name = (char*)*pBuffer + *currentOffset;
        *currentOffset += strlen(name) + 1;
        
        int *age = (int*)((char*)*pBuffer + *currentOffset);
        *currentOffset += sizeof(int);

        char *email = (char*)*pBuffer + *currentOffset;
        *currentOffset += strlen(email) + 1;

        if (strcmp(email, searchEmail) == 0) {
            printf("\nEncontrado:\nNome: %s\nIdade: %d\nEmail: %s\n", name, *age, email);
            break;
        }
    }

    *pBufferSize -= 100 * sizeof(char);
    *pBuffer = realloc(*pBuffer, *pBufferSize);
}

void ListContacts(void *pBuffer, int *pBufferSize) {
    int *currentOffset = (int*)pBuffer + 2;
    *currentOffset = 3 * sizeof(int);

    while (*currentOffset < *pBufferSize) {
        char *name = (char*)pBuffer + *currentOffset;
        *currentOffset += strlen(name) + 1;
        
        int *age = (int*)((char*)pBuffer + *currentOffset);
        *currentOffset += sizeof(int);

        char *email = (char*)pBuffer + *currentOffset;
        *currentOffset += strlen(email) + 1;

        printf("\nNome: %s\nIdade: %d\nEmail: %s\n", name, *age, email);
    }
}
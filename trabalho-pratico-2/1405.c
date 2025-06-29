#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CurrentChar {
    char character;
    int count;
} CurrentChar;

typedef struct Character {
    char character;
    struct Character *next;
} Character;

typedef struct Heap {
    int a;
    int b;
    int c;
    Character *first;
    Character *last;
} Heap;

void AddChar(Heap *queue, char character) {
    Character *newCharacter = malloc(sizeof(Character));
    newCharacter->character = character;

    if (queue->first == NULL)
        queue->first = newCharacter;

    newCharacter->next = queue->last;
    queue->last = newCharacter;
}

char RemoveChar(Heap *queue) {
    Character *returnedChar = queue->first;
    if (returnedChar == NULL)
        return '\0';
    
    Character *queueChar = queue->last;
    CurrentChar currentChar;
    currentChar.character = queueChar->character;
    currentChar.count = 1;

    if (queueChar->next != NULL) {
        while (queueChar->next->next != NULL) {
            if (queueChar->next->next->character == currentChar.character)
                currentChar.count++;
            
            queueChar = queueChar->next;
            currentChar.character = queueChar->character;
        }

        queueChar->next = NULL;
        queue->first = queueChar;
    } else {
        queue->first = NULL;
        queue->last = NULL;
    }

    return returnedChar->character;
}

int main() {
    //char *string = calloc(1, sizeof(char));
    int a = 1, b = 1, c = 7;
    
    Heap *queue = malloc(sizeof(Heap));
    queue->first = NULL;
    queue->last = NULL;
    queue->a = a;
    queue->b = b;
    queue->c = c;

    for (int i = 0; i < a; i++) {
        AddChar(queue, 'a');
    }

    for (int i = 0; i < b; i++) {
        AddChar(queue, 'b');
    }

    for (int i = 0; i < c; i++) {
        AddChar(queue, 'c');
    }

    for (int i = 0; i < a + b + c; i++) {
        printf("%c\n", RemoveChar(queue));
    }

    free(queue);
}
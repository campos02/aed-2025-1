#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Character {
    char character;
    int count;
    struct Character *next;
} Character;

typedef struct Heap {
    Character *first;
    Character *last;
} Heap;

void AddChar(Heap *queue, char character, int count) {
    if (count < 1)
        return;

    Character *newCharacter = malloc(sizeof(Character));
    newCharacter->character = character;
    newCharacter->count = count;
    newCharacter->next = NULL;

    if (queue->first == NULL) {
        queue->first = newCharacter;
        queue->last = queue->first;
        return;
    }

    if (newCharacter->count > queue->first->count) {
        Character *queueChar = queue->first;
        newCharacter->next = queueChar;
        queue->first = newCharacter;
        return;
    }

    Character *queueChar = queue->first;
    while (queueChar->next != NULL) {
        if (newCharacter->count > queueChar->next->count) {
            Character *nextChar = queueChar->next;
            newCharacter->next = nextChar;
            queueChar->next = newCharacter;
            return;
        }

        queueChar = queueChar->next;
    }
    
    queue->last->next = newCharacter;
    queue->last = newCharacter;
}

Character* RemoveChar(Heap *queue) {
    Character *character = queue->first;
    if (character != NULL)
        queue->first = queue->first->next;
    
    return character;
}

int main() {
    char *string = calloc(1, sizeof(char));
    int a = 7, b = 1, c = 0;
    
    Heap *queue = malloc(sizeof(Heap));
    queue->first = NULL;
    queue->last = NULL;

    AddChar(queue, 'a', a);
    AddChar(queue, 'b', b);
    AddChar(queue, 'c', c);

    for (int i = 0; i < a + b + c; i++) {
        Character *queueChar = RemoveChar(queue);

        if (i > 1 && string[i - 1] == string[i - 2]) {
            if (queueChar->character == string[i - 1]) {
                Character *nextChar = RemoveChar(queue);
                if (nextChar == NULL)
                    break;
                
                AddChar(queue, queueChar->character, queueChar->count);
                free(queueChar);
                queueChar = nextChar;
            }
        }

        int originalLen = strlen(string);
        string = realloc(string, originalLen + 2);

        string[originalLen] = queueChar->character;
        string[originalLen + 1] = '\0';

        if (queueChar->count > 1)
            AddChar(queue, queueChar->character, queueChar->count - 1);
        
        free(queueChar);
    }

    printf("%s\n", string);
    free(queue);
    free(string);
}
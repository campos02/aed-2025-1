typedef struct Stack {
    int *tokens;
    int top;
    int limit;
} Stack;

int evalRPN(char** tokens, int tokensSize) {
    Stack *stack = malloc(sizeof(Stack));

    stack->tokens = malloc(sizeof(int));
    stack->top = 0;
    stack->limit = 10000;

    for (int i = 0; i < tokensSize; i++) {
        if (strcmp(tokens[i], "+") == 0) {
            if (stack->top >= 2) {
                stack->top--;
                int op2 = stack->tokens[stack->top];

                stack->top--;
                int op1 = stack->tokens[stack->top];

                stack->tokens = realloc(stack->tokens, (stack->top + 1) * sizeof(int));
                stack->tokens[stack->top] = op1 + op2;
                stack->top++;
            }
        } else if (strcmp(tokens[i], "-") == 0) {
            if (stack->top >= 2) {
                stack->top--;
                int op2 = stack->tokens[stack->top];

                stack->top--;
                int op1 = stack->tokens[stack->top];

                stack->tokens = realloc(stack->tokens, (stack->top + 1) * sizeof(int));
                stack->tokens[stack->top] = op1 - op2;
                stack->top++;
            }
        } else if (strcmp(tokens[i], "*") == 0) {
            if (stack->top >= 2) {
                stack->top--;
                int op2 = stack->tokens[stack->top];

                stack->top--;
                int op1 = stack->tokens[stack->top];

                stack->tokens = realloc(stack->tokens, (stack->top + 1) * sizeof(int));
                stack->tokens[stack->top] = op1 * op2;
                stack->top++;
            }
        } else if (strcmp(tokens[i], "/") == 0) {
            if (stack->top >= 2) {
                stack->top--;
                int op2 = stack->tokens[stack->top];

                stack->top--;
                int op1 = stack->tokens[stack->top];

                if (op2 != 0) {
                    stack->tokens = realloc(stack->tokens, (stack->top + 1) * sizeof(int));
                    stack->tokens[stack->top] = op1 / op2;
                    stack->top++;
                }
            }
        } else {
            if (stack->top < stack->limit) {
                stack->tokens = realloc(stack->tokens, (stack->top + 1) * sizeof(int));
                stack->tokens[stack->top] = atoi(tokens[i]);
                stack->top++;
            }
        }
    }

    stack->top--;
    int result = stack->tokens[stack->top];
    
    free(stack->tokens);
    free(stack);

    return result;
}
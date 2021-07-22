#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strcat_c(char *original, char tocat) {
    int originalSize;
    if (original == NULL) {
        original = malloc(2 * sizeof(char));
        originalSize = 0;
    } else {
        originalSize = strlen(original);
    }

    original[originalSize] = tocat;
    original[originalSize + 1] = '\0';

    return original;
}

int isOperator(char o) {
    switch (o) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':
        case '(':
        case ')':
            return 1;
        default:
            return 0;
    }
}

int isOperator_s(char *o) { return isOperator(o[0]); }

char **tokenize(char *exp, int *tokenCount) {
    char **tokenizedExp, **temp, *buffer = NULL;
    int tokens = 0;

    tokenizedExp = malloc((tokens + 1) * sizeof(char *));

    int i = 0, expSize = strlen(exp);
    while (i < expSize) {
        buffer = NULL;
        if (exp[i] == ' ') {
            i++;
            continue;
        } else if (isOperator(exp[i])) {
            buffer = strcat_c(buffer, exp[i]);
            i++;
        } else {
            while (exp[i] != ' ' && !isOperator(exp[i]) && i < expSize) {
                buffer = strcat_c(buffer, exp[i]);
                i++;
            }
        }

        if (tokens > 0) {
            tokenizedExp = realloc(tokenizedExp, (tokens + 1) * sizeof(char *));
        }

        tokenizedExp[tokens] = malloc(strlen(buffer) * sizeof(char));
        strcpy(tokenizedExp[tokens], buffer);
        tokens++;
    }

    *tokenCount = tokens;
    return tokenizedExp;
}

struct Stack {
    int top;
    unsigned int capacity;
    int *elements;
};

struct Stack *initStack(unsigned int size) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));

    if (!stack) {
        return NULL;
    }

    stack->top = -1;
    stack->capacity = size;

    stack->elements = (int *)malloc(stack->capacity * sizeof(int));

    return stack;
}

int isEmpty(struct Stack *stack) { return stack->top == -1; }

int peek(struct Stack *stack) { return stack->elements[stack->top]; }

int pop(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->elements[stack->top--];
    }
}

void push(struct Stack *stack, int op) { stack->elements[++stack->top] = op; }

int evaluate_postfix(char *postfix) {
    int tokens;
    char **tokenizedPostfixExp = tokenize(postfix, &tokens);

    struct Stack *stack = initStack(tokens);

    int operand1, operand2, operation;

    for (int i = 0; i < tokens; i++) {
        if (!isOperator_s(tokenizedPostfixExp[i])) {
            push(stack, atoi(tokenizedPostfixExp[i]));
        } else {
            operand1 = pop(stack);
            operand2 = pop(stack);

            switch (tokenizedPostfixExp[i][0]) {
                case '+':
                    operation = operand2 + operand1;
                    break;
                case '-':
                    operation = operand2 - operand1;
                    break;
                case '*':
                    operation = operand2 * operand1;
                    break;
                case '/':
                    operation = operand2 / operand1;
                    break;
                case '%':
                    operation = operand2 % operand1;
                    break;
                case '^':
                    operation = operand2 ^ operand1;
                    break;
            }

            push(stack, operation);
        }
    }

    return pop(stack);
}

int main(int argc, char const *argv[]) {
    char *postfixExp = "54 37 22 * 654 / + 92 -";
    printf("Postfix [INPUT]: %s\n", postfixExp);
    printf("Evaluated: %d\n", evaluate_postfix(postfixExp));

    return 0;
}

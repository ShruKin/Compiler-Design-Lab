#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OPERATION_SIZE 256

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

char *join(char **exp, int tokens) {
    char *joined = exp[0];
    strcat(joined, " ");

    for (int i = 1; i < tokens; i++) {
        strcat(joined, exp[i]);
        strcat(joined, " ");
    }

    return joined;
}

int precedence(char *o) {
    switch (o[0]) {
        case '^':
            return 3;
        case '/':
        case '*':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return -1;
    }
}

struct Stack {
    int top;
    unsigned int capacity;
    char **elements;
};

struct Stack *initStack(unsigned int size) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));

    if (!stack) {
        return NULL;
    }

    stack->top = -1;
    stack->capacity = size;

    stack->elements = malloc(stack->capacity * sizeof(char *));

    return stack;
}

int isEmpty(struct Stack *stack) { return stack->top == -1; }

char *peek(struct Stack *stack) { return stack->elements[stack->top]; }

char *pop(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->elements[stack->top--];
    }
    return NULL;
}

void push(struct Stack *stack, char *op) { stack->elements[++stack->top] = op; }

char *infix_to_postfix(char *infix) {
    int tokens;
    char **tokenizedInfixExp = tokenize(infix, &tokens);

    char **postfix = malloc(tokens * sizeof(char *));
    struct Stack *stack = initStack(tokens);
    int k = 0;

    for (int i = 0; i < tokens; i++) {
        if (!isOperator_s(tokenizedInfixExp[i])) {
            postfix[k++] = tokenizedInfixExp[i];
        }

        else if (tokenizedInfixExp[i] == "(") {
            push(stack, tokenizedInfixExp[i]);
        }

        else if (tokenizedInfixExp[i] == ")") {
            while (!isEmpty(stack) && peek(stack) != "(") {
                postfix[k++] = pop(stack);
            }

            if (!isEmpty(stack) && peek(stack) != "(") {
                return NULL;
            } else {
                pop(stack);
            }
        }

        else {
            while (!isEmpty(stack) && precedence(tokenizedInfixExp[i]) <=
                                          precedence(peek(stack))) {
                postfix[k++] = pop(stack);
            }
            push(stack, tokenizedInfixExp[i]);
        }
    }

    while (!isEmpty(stack)) {
        postfix[k++] = pop(stack);
    }

    return join(postfix, tokens);
}

char *infix_to_prefix(char *infix) {
    int tokens;
    char **tokenizedInfixExp = tokenize(infix, &tokens);

    char **prefix = malloc(tokens * sizeof(char *));
    struct Stack *stack = initStack(tokens);
    int k = tokens - 1;

    for (int i = tokens - 1; i >= 0; i--) {
        if (!isOperator_s(tokenizedInfixExp[i])) {
            prefix[k--] = tokenizedInfixExp[i];
        }

        else if (tokenizedInfixExp[i] == ")") {
            push(stack, tokenizedInfixExp[i]);
        }

        else if (tokenizedInfixExp[i] == "(") {
            while (!isEmpty(stack) && peek(stack) != ")") {
                prefix[k--] = pop(stack);
            }

            if (!isEmpty(stack) && peek(stack) != ")") {
                return NULL;
            } else {
                pop(stack);
            }
        }

        else {
            while (!isEmpty(stack) && precedence(tokenizedInfixExp[i]) <=
                                          precedence(peek(stack))) {
                prefix[k--] = pop(stack);
            }
            push(stack, tokenizedInfixExp[i]);
        }
    }

    while (!isEmpty(stack)) {
        prefix[k--] = pop(stack);
    }

    return join(prefix, tokens);
}

char *postfix_to_infix(char *postfix) {
    int tokens;
    char **tokenizedPostfixExp = tokenize(postfix, &tokens);

    struct Stack *stack = initStack(2 * tokens);

    char *operand1 = malloc(MAX_OPERATION_SIZE * sizeof(char)),
         *operand2 = malloc(MAX_OPERATION_SIZE * sizeof(char)),
         *operation = malloc(MAX_OPERATION_SIZE * sizeof(char));

    for (int i = 0; i < tokens; i++) {
        if (!isOperator_s(tokenizedPostfixExp[i])) {
            push(stack, tokenizedPostfixExp[i]);
        } else {
            strcpy(operand1, pop(stack));
            strcpy(operand2, pop(stack));

            strcpy(operation, "(");
            strcat(operation, operand2);
            strcat(operation, tokenizedPostfixExp[i]);
            strcat(operation, operand1);
            strcat(operation, ")");

            push(stack, operation);
        }
    }

    return peek(stack);
}

char *postfix_to_prefix(char *postfix) {
    int tokens;
    char **tokenizedPostfixExp = tokenize(postfix, &tokens);

    struct Stack *stack = initStack(2 * tokens);

    char *operand1 = malloc(MAX_OPERATION_SIZE * sizeof(char)),
         *operand2 = malloc(MAX_OPERATION_SIZE * sizeof(char)),
         *operation = malloc(MAX_OPERATION_SIZE * sizeof(char));

    for (int i = 0; i < tokens; i++) {
        if (!isOperator_s(tokenizedPostfixExp[i])) {
            push(stack, tokenizedPostfixExp[i]);
        } else {
            strcpy(operand1, pop(stack));
            strcpy(operand2, pop(stack));

            strcpy(operation, tokenizedPostfixExp[i]);
            strcat(operation, " ");
            strcat(operation, operand2);
            strcat(operation, " ");
            strcat(operation, operand1);
            strcat(operation, " ");

            push(stack, operation);
        }
    }

    return peek(stack);
}

char *prefix_to_infix(char *prefix) {
    int tokens;
    char **tokenizedPrefixExp = tokenize(prefix, &tokens);

    struct Stack *stack = initStack(2 * tokens);

    char *operand1 = malloc(MAX_OPERATION_SIZE * sizeof(char)),
         *operand2 = malloc(MAX_OPERATION_SIZE * sizeof(char)),
         *operation = malloc(MAX_OPERATION_SIZE * sizeof(char));

    for (int i = tokens - 1; i >= 0; i--) {
        if (!isOperator_s(tokenizedPrefixExp[i])) {
            push(stack, tokenizedPrefixExp[i]);
        } else {
            strcpy(operand1, pop(stack));
            strcpy(operand2, pop(stack));

            strcpy(operation, "(");
            strcat(operation, operand1);
            strcat(operation, tokenizedPrefixExp[i]);
            strcat(operation, operand2);
            strcat(operation, ")");

            push(stack, operation);
        }
    }

    return peek(stack);
}

int main(int argc, char const *argv[]) {
    // char *exp = "54 + 37 * 22 / 654 - 92";  // infix
    // char *exp = "54 37 22 * 654 / + 92 -";  // postfix
    // char *exp = "+ 54 - * 37 / 22 654 92";  // prefix

    char *infixExp = "54 + 37 * 22 / 654 - 92";
    printf("Postfix: %s\n", infix_to_postfix(infixExp));
    printf("Prefix: %s\n", infix_to_prefix(infixExp));

    printf("\n");

    char *postfixExp = "54 37 22 * 654 / + 92 -";
    printf("Infix: %s\n", postfix_to_infix(postfixExp));
    printf("Prefix: %s\n", postfix_to_prefix(postfixExp));

    printf("\n");

    char *prefixExp = "+ 54 - * 37 / 22 654 92";
    printf("Infix: %s\n", prefix_to_infix(prefixExp));

    return 0;
}

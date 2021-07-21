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

char **infix_to_postfix(char **infix, int tokens) {
    char **postfix = malloc(tokens * sizeof(char *));
    struct Stack *stack = initStack(tokens);
    int k = 0;

    for (int i = 0; i < tokens; i++) {
        if (!isOperator_s(infix[i])) {
            postfix[k++] = infix[i];
        }

        else if (infix[i] == "(") {
            push(stack, infix[i]);
        }

        else if (infix[i] == ")") {
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
            while (!isEmpty(stack) &&
                   precedence(infix[i]) <= precedence(peek(stack))) {
                postfix[k++] = pop(stack);
            }
            push(stack, infix[i]);
        }
    }

    while (!isEmpty(stack)) {
        postfix[k++] = pop(stack);
    }

    return postfix;
}

int main(int argc, char const *argv[]) {
    // char *exp = "54 + 37 * 22 / 654 - 92";  // infix
    // // char *exp = "54 37 22 * 654 / + 92 -";  // postfix
    // // char *exp = "+ 4 - * 37 / 22 654 92";  // prefix

    char *infixExp = "54 + 37 * 22 / 654 - 92";
    int tokens;
    char **tokenizedInfixExp = tokenize(infixExp, &tokens);

    char **tokenizedPostfixExp = infix_to_postfix(tokenizedInfixExp, tokens);
    char *postfixExp = join(tokenizedPostfixExp, tokens);

    printf("\nPostfix: %s", postfixExp);

    return 0;
}

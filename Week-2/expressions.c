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
    for (int i = 1; i < tokens; i++) {
        strcat(joined, exp[i]);
        strcat(joined, " ");
    }

    return joined;
}

int main(int argc, char const *argv[]) {
    // char *exp = "54 + 37 * 22 / 654 - 92";  // infix
    // char *exp = "54 37 22 * 654 / + 92 -";  // postfix
    char *exp = "+ 4 - * 37 / 22 654 92";  // prefix

    int tokens;
    char **tokenizedExp = tokenize(exp, &tokens);

    printf("No. of tokens: %d\n", tokens);
    for (int i = 0; i < tokens; i++) {
        printf("%s ", tokenizedExp[i]);
    }

    printf("\nJoined: %s", join(tokenizedExp, tokens));

    return 0;
}

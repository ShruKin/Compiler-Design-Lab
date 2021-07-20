#include <stdio.h>
#include <string.h>

int isComment(char *line) {
    if (line[0] == '/' && line[1] == '/') {
        return 1;
    }

    int size = strlen(line);
    if (line[0] == '/' && line[1] == '*' && line[size - 2] == '*' &&
        line[size - 1] == '/') {
        return 1;
    }

    return 0;
}

int main(int argc, char const *argv[]) {
    char *test_cases[3] = {"// This is a single line comment",
                           "/* This is a multiline comment */",
                           "sum += (a + b + c / 4)"};

    for (int i = 0; i < 3; i++) {
        printf("%s\t", test_cases[i]);

        if (isComment(test_cases[i]))
            printf("Comment\n");
        else
            printf("Not Comment\n");
    }

    return 0;
}

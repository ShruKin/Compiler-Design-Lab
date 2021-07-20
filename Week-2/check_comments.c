#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 256

int main(int argc, char const *argv[]) {
    FILE *inFp;
    char line[MAX_LINE_SIZE], ch, nextCh, next2Ch;
    int lineSize, lineNo = 1, multlineStart = 0;

    inFp = fopen("tests\\comm.c", "r");

    if (inFp == NULL) {
        printf("Error: Can't open file\n");
        return 0;
    }

    while (fgets(line, MAX_LINE_SIZE, inFp)) {
        lineSize = strlen(line);

        if (multlineStart) {
            for (int j = 0; j < lineSize; j++) {
                if (line[j] == '*' && line[j + 1] == '/') {
                    multlineStart = 0;
                    printf("to Ln %d, Col %d => VALID\n", lineNo, j + 3);
                }
            }
        }

        for (int i = 0; i < lineSize; i++) {
            if (line[i] == '/') {
                if (line[i + 1] == '/') {
                    printf("Single line comment at: Ln %d, Col %d => VALID\n",
                           lineNo, i + 1);
                }

                if (line[i + 1] == '*') {
                    multlineStart = 1;
                    printf("Multi line comment from Ln %d, Col %d ", lineNo,
                           i + 1);
                    for (int j = i + 2; j < lineSize; j++) {
                        if (line[j] == '*' && line[j + 1] == '/') {
                            multlineStart = 0;
                            printf("to Ln %d, Col %d => VALID\n", lineNo,
                                   j + 3);
                        }
                    }
                }
            }
        }

        lineNo++;
    }

    if (multlineStart) {
        printf("=> INVALID");
    }

    fclose(inFp);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    FILE *inFp, *outFp;
    char *line, ch, nextCh, next2Ch;

    inFp = fopen("tests\\comm.c", "r");
    outFp = fopen("tests\\comm_no_comments.c", "w");

    if (inFp == NULL) {
        printf("Error: Can't open file\n");
        return 0;
    }

    while ((ch = fgetc(inFp)) != EOF) {
        if (ch == '/') {
            nextCh = fgetc(inFp);

            if (nextCh == '/') {
                while ((nextCh = fgetc(inFp)) != '\n') {
                    putchar(nextCh);
                }
            }

            else if (nextCh == '*') {
                while (1) {
                    if ((nextCh = fgetc(inFp)) == '*' &&
                        (next2Ch = fgetc(inFp)) == '/') {
                        break;
                    }
                    putchar(nextCh);
                }
            }

            else {
                fputc(ch, outFp);
            }
        }

        else if (ch == ' ' || ch == '\n' || ch == '\t') {
            continue;
        }

        else {
            fputc(ch, outFp);
        }
    }

    fclose(inFp);
    fclose(outFp);

    return 0;
}

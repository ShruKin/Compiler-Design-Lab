#include <stdio.h>
#include <string.h>

int validIdentifier(char *str) {
    int i = 0;

    if (!((str[i] >= 'a' && str[i] <= 'z') ||
          (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_'))
        return 0;

    i++;

    while (str[i] != '\0') {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
            return 0;
        i++;
    }

    return 1;
}

int main(int argc, char const *argv[]) {
    int n;
    char str[256];

    char *test_cases[10] = {
        "i",          "rank1", "MAX",      "max",     "Min",
        "class_rank", "a's",   "fact rec", "2sqroot", "class,rank",
    };

    for (int i = 0; i < 10; i++) {
        printf("%s\t", test_cases[i]);

        if (validIdentifier(test_cases[i]))
            printf("VALID\n");
        else
            printf("INVALID\n");
    }
    return 0;
}

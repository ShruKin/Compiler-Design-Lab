#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define INVALID -1

#define END_STATE_INT -2
#define END_STATE_FLT -3

int state_0(char c) {
    if (isdigit(c)) {
        return 1;
    } else {
        return INVALID;
    }
}

int state_1(char c) {
    if (isdigit(c)) {
        return 1;
    } else if (c == '.') {
        return 2;
    } else {
        return END_STATE_INT;
    }
}

int state_2(char c) {
    if (isdigit(c)) {
        return 3;
    } else {
        return INVALID;
    }
}

int state_3(char c) {
    if (isdigit(c)) {
        return 3;
    } else {
        return END_STATE_FLT;
    }
}

typedef int (*automata)(char);

int number_constant_automata(char *str) {
    automata states[4] = {&state_0, &state_1, &state_2, &state_3};

    int current_state = 0, i = 0;
    while (1) {
        current_state = states[current_state](str[i++]);
        if (current_state == INVALID || current_state == END_STATE_INT ||
            current_state == END_STATE_FLT) {
            return current_state;
        }
    }
    return INVALID;
}

int main(int argc, char const *argv[]) {
    char *test_cases[10] = {
        "2", "2.0", "0.2", "25", "23.65", ".65", "5.", "156.1458", "1264", "96",
    };

    for (int i = 0; i < 10; i++) {
        printf("%s\t", test_cases[i]);

        switch (number_constant_automata(test_cases[i])) {
            case INVALID:
                printf("INVALID");
                break;
            case END_STATE_INT:
                printf("INTEGER");
                break;
            case END_STATE_FLT:
                printf("FLOATING-POINT");
                break;
        }
        printf("\n");
    }

    return 0;
}
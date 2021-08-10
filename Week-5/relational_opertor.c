#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define INVALID -1

#define END_STATE_LT -2
#define END_STATE_NE -3
#define END_STATE_LE -4
#define END_STATE_EQ -5
#define END_STATE_GE -6
#define END_STATE_GT -7

int state_0(char c) {
    switch (c) {
        case '<':
            return 1;
        case '=':
            return END_STATE_EQ;
        case '>':
            return 2;
        default:
            return INVALID;
    }
}

int state_1(char c) {
    switch (c) {
        case '>':
            return END_STATE_NE;
        case '=':
            return END_STATE_LE;
        default:
            return END_STATE_LT;
    }
}

int state_2(char c) {
    switch (c) {
        case '=':
            return END_STATE_GE;
        default:
            return END_STATE_GT;
    }
}

typedef int (*automata)(char);

char* relational_op_automata(char* str) {
    automata states[3] = {&state_0, &state_1, &state_2};

    int current_state = 0, i = 0;
    while (1) {
        current_state = states[current_state](str[i++]);
        if (current_state < 0) break;
    }

    switch (current_state) {
        case END_STATE_LT:
            return "Less Than";
        case END_STATE_NE:
            return "Not Equal To";
        case END_STATE_LE:
            return "Less Than or Equal To";
        case END_STATE_EQ:
            return "Equal To";
        case END_STATE_GE:
            return "Greater Than or Equal To";
        case END_STATE_GT:
            return "Greater Than";
        default:
            return "INVALID";
    }

    return 0;
}

int main(int argc, char const* argv[]) {
    char* test_cases[11] = {"<",  "<>",  "<=", ">",  ">=", "=",
                            "==", "===", "><", ">>", "<<"};

    for (int i = 0; i < 11; i++) {
        printf("%s\t", test_cases[i]);

        printf("\t%s\n", relational_op_automata(test_cases[i]));
    }

    return 0;
}
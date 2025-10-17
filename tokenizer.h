#ifndef tokenizer
#define tokenizer

enum token { // size of enum in memory is int (4 bytes)
    UNUSED,
    IDENTIFIER,
    CONSTANT,
    OPERATOR_PLUS,
    OPERATOR_SUBTRACT,
    OPERATOR_DIVIDE,
    OPERATOR_ASSIGNMENT,
    WHITE_SPACE,
    ERROR,
};

typedef struct { // 8 bytes
    enum token id;
    int location;
} token_info;

#endif
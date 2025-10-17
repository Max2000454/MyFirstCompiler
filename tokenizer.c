#include<stdlib.h>
#include<stdio.h>
#include<regex.h>
#include<string.h>
#include "tokenizer.h"

#define MAXIMUM_LINE_SIZE 1208

// one important type : regex_t -> opaque struct
// four important functions: regcomp(&regex, str, compilerMode), regexec(&regex, otherStr, 0, NULL, 0), regerror(reti, &regex, bufErr, sizeof(bufErr)), regfree(&regex);
int isLetter(char c) {
    regex_t regex;
    int reti;
    char bufErr[126];
    int found = -1;
    char str[2] = {c, '\0'};
    
    reti = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (reti) {
        regerror(reti, &regex, bufErr, sizeof(bufErr));
        perror(bufErr);
        exit(EXIT_FAILURE);
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
        found = 1;
    } else if (reti == REG_NOMATCH) {
        found = 0;
    } else {
        regerror(reti, &regex, bufErr, sizeof(bufErr));
        perror(bufErr);
        exit(EXIT_FAILURE);
    }

    regfree(&regex);
    return found;
}

// practiced methods by doing again then fixing to look the same lol
int isNumber(char c) {
    regex_t regex;
    int reti;
    char bufErr[128];
    int found = -1;
    char str[2] = {c, '\0'};

    reti = regcomp(&regex, "[0-9]", REG_EXTENDED);
    if (reti != 0) {
        regerror(reti, &regex, bufErr, sizeof(bufErr));
        perror(bufErr);
        exit(EXIT_FAILURE);
    }

    reti = regexec(&regex, str, 0, NULL, 0);
    if (reti == 0) {
        found = 1;
    } else if (reti == REG_NOMATCH) {
        found = 0;
    } else {
        regerror(reti, &regex, bufErr, sizeof(bufErr));
        perror(bufErr);
        exit(EXIT_FAILURE);
    }

    regfree(&regex);
    return found;
}

/*
int isLetterSimple(char c) {
    return (c >= 'A' && c <= 'Z');
}

int isNumberSimple(char c) {
    return (c >= '0' && c <= '9');
}
*/

enum token scanToken(FILE* fp) {
    char c = fgetc(fp);

    if (c == ' ') {
        printf("WHITESPACE\n");
        return WHITE_SPACE;

    } else if (c == '+') {
        printf("ADD\n");
        return OPERATOR_PLUS;

    } else if (c == '-') {
        printf("SUB\n");
        return OPERATOR_SUBTRACT;

    } else if (c == '/') {
        printf("DIVIDE\n");
        return OPERATOR_DIVIDE;

    } else if (c == '=') {
        printf("ASSIGN\n");
        return OPERATOR_ASSIGNMENT;

    } else if (isLetter(c)) {
        char d = fgetc(fp);
        while(isLetter(d)) {
            d = fgetc(fp);
        }
        ungetc(d, fp);
        printf("ID\n");
        return IDENTIFIER;

    } else if (isNumber(c)) {
        char d = fgetc(fp);
        while(isNumber(d)) {
            d = fgetc(fp);
        }
        ungetc(d, fp);
        printf("CONST\n");
        return CONSTANT;
    }

    printf("%c\n", c);
    return ERROR;
}

void checkForEOF(FILE* fp) {
    char c = fgetc(fp);
    if (c == EOF) return;
    ungetc(c, fp);
}

int main(int argc, char* argv[]) {
    //char buf[MAXIMUM_LINE_SIZE];
    FILE* fp = fopen("arith.txt", "r");
    if (fp == NULL) {
        perror("Could not open file");
    }

    enum token BUF[MAXIMUM_LINE_SIZE];
    token_info tokenInfoArr[MAXIMUM_LINE_SIZE * sizeof(token_info)];
    int currentEnd = 0;
    while (!feof(fp)) {
        BUF[currentEnd] = scanToken(fp);
        currentEnd++;
        checkForEOF(fp);
    }

    switch(BUF[0]) {
        case 0:
            printf("We have an identifier, %d\n", BUF[0]);
            break;
        default:
            printf("Looks like we didn't have an identifier as the first symbol!\n");
            break;
    }

    for (int i = 0; i < currentEnd; i++) {
        printf("%d ", BUF[i]);
    }
    printf("\n");

    fclose(fp);
    return 0;
}
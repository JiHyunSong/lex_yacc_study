/* 
2014.10.28 Author by JiHyun Song
Compiler Mini C Scanner
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define NO_KEYWORDS 7
#define ID_LENGTH 12

struct tokenType {
    int number;         // token number
    union {
        char id[ID_LENGTH];
        int num;
    } value;            // token value
};

enum tsymbol { tnull=-1,
    tnot,   tnotequ,    tmod,   tmodAssign, tident, tnumber,    /* 0,   1,  2,  3,  4,  5,  */
    tand,   tlparen,    trparen,    tmul,   tmulAssign, tplus,  /* 6,   7,  8,  9,  10, 11, */
    tinc,   taddAssign, tcomma, tminus, tdec,   tsubAssign,     /* 12,  13, 14, 15, 16, 17, */
    tdiv,   tdivAssign, tsemicolon, tless,  tlesse, tassign,    /* 18,  19, 20, 21, 22, 23, */
    tequal, tgreat, tgreate,    tlbracket,  trbracket,  teof,   /* 24,  25, 26, 27, 28, 29, */
    tconst, telse,  tif,    tint,   treturn,    tvoid,          /* 30,  31, 32, 33, 34, 35, */
    twhile, tlbrace,    tor,    trbrace                         /* 36,  37, 38, 39          */
};

char *keyword[NO_KEYWORDS] = {
    "const",    "else", "if",   "int",  "return",   "void", "while"
};

enum tsymbol tnum[NO_KEYWORDS] = {
    tconst, telse,  tif,    tint,   treturn,    tvoid,  twhile
};

int hexValue(char ch)
{
    switch (ch) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return (ch - '0');
            break;
        case 'A': case 'B': case 'C': case 'D': case 'E':
        case 'F':
            return (ch - 'A' + 10);
            break;
        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f':
            return (ch - 'a' + 10);
            break;
        default:
            return -1;
            break;
    }
    return -1;
}

int getIntNum(char firstCharacter) {
    int num = 0;
    int value;
    char ch;

    if(firstCharacter != '0') {
        ch = firstCharacter;        // decimal
        do {
            num = 10 * num + (int)(ch - '0');
            ch = getchar();
        } while(isdigit(ch)); 
    } else {
        ch = getchar();
        if ((ch >= '0') && (ch <= '7')) { // octal
            do {
                num = 8*num + (int)(ch - '0');
                ch = getchar();
            } while ((ch >= '0') && (ch <= '7'));
        } else if ((ch == 'x') || (ch == 'X')) { // hexa decimal
            while ((value=hexValue(ch=getchar())) != -1)
                num = 16*num + value;
        }
        else num = 0;
    }

    ungetc(ch, stdin);      // retract
    return num; 
}

void lexicalError(int n)
{
    printf(" *** Lexical Error : ");
    switch (n) {
        case 1: printf("an identifier length must be less than 12.\n");
            break;
        case 2: printf("next character must be &.\n");
            break;
        case 3: printf("next character must be |.\n");
            break;
        case 4: printf("invalid character!\n");
            break;
    }
}

int superLetter(char ch)
{
    if (isalpha(ch) || ch == '_') return 1;
    else return 0;
}

int superLetterOrDigit(char ch)
{
    if (isalnum(ch) || ch == '_') return 1;
    else return 0;
}

struct tokenType scanner() {
    struct tokenType token;
    int i=0, index=0;
    char ch, id[ID_LENGTH];

    token.number = tnull;

do {
    while(isspace(ch = getchar())) ;    // skip branks

    if (superLetter(ch)) {              // identifier or keyword
        i = 0;
        do {
            if (i < ID_LENGTH) id[i++] = ch;
            ch = getchar();
        } while (superLetterOrDigit(ch));

        if (i >= ID_LENGTH) lexicalError(1);
        id[i] = '\0';
        ungetc(ch, stdin);              // retract

        // find the identifier in the keyword table
        for (index=0; index < NO_KEYWORDS; index++)
            if(!strcmp(id, keyword[index])) break;

        if (index < NO_KEYWORDS)        // found, keyword exit
            token.number = tnum[index];
        else {                          // not found, identifier exit
            token.number = tnum[index];
            strcpy(token.value.id, id);
        }
    }   // end of identifier of keyword
    else if (isdigit(ch)) {             // integer constant
        token.number = tnumber;
        token.value.num = getIntNum(ch);
    }
    else {
        switch (ch) {                   // special character
            case '/':   // state 10
                ch = getchar();
                if (ch == '*')          // text comment
                    do {
                        while (ch != '*') ch = getchar();
                        ch = getchar();
                    } while (ch != '/') ;
                else if (ch == '/')     // line comment
                    while (getchar() != '\n') ;
                else if (ch == '=')     // divide itself and reassign
                    token.number = tdivAssign;
                else {
                    token.number = tdiv;
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '!':   // state 17
                ch = getchar();
                if (ch == '=')  token.number = tnotequ;
                else {
                    token.number = tnot;
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '%':   // state 20
                ch = getchar();
                if (ch == '=')  token.number = tmodAssign;
                else {
                    token.number = tmod;
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '&':   // state 23
                ch = getchar();
                if (ch == '&')  token.number = tand;
                else {
                    lexicalError(2);
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '*':   // state 25
                ch = getchar();
                if (ch == '=')  token.number = tmulAssign;
                else {
                    token.number = tmul;
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '+':   // state 28
                ch = getchar();
                if (ch == '+')  token.number = tinc;
                else if (ch == '=') token.number = taddAssign;
                else {
                    token.number = tplus;
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '-':   // state 32
                ch = getchar();
                if (ch == '-')  token.number = tdec;
                else if (ch == '=') token.number = tsubAssign;
                else {
                    token.number = tminus;
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '<':   // state 36
                ch = getchar();
                if (ch == '=')  token.number = tlesse;
                else {
                    token.number = tless;
                    ungetc(ch, stdin);  // retract
                }
               break;
            case '=':   // state 39
                ch = getchar();
                if (ch == '=')  token.number = tequal;
                else {
                    token.number = tassign;
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '>':   // state 42
                ch = getchar();
                if (ch == '=')  token.number = tgreate;
                else {
                    token.number = tgreat;
                    ungetc(ch, stdin);  // retract 
                }
                break;
            case '|':   // state 45
                ch = getchar();
                if (ch == '|')  token.number = tor;
                else {
                    lexicalError(3);
                    ungetc(ch, stdin);  // retract
                }
                break;
            case '(': token.number = tlparen;   break;
            case ')': token.number = trparen;   break;
            case ',': token.number = tcomma;    break;
            case ';': token.number = tsemicolon;    break;
            case '[': token.number = tlbracket; break;
            case ']': token.number = trbracket; break;
            case '{': token.number = tlbrace;   break;
            case '}': token.number = trbrace;   break;
            case EOF: token.number = teof;  break;
            default:    {
                printf("Current character : %c", ch);
                lexicalError(4);
                break;
            }
        }   // switch end
    }
} while(token.number == tnull);
return token;

} // end of scanner

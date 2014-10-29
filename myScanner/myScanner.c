#include <stdio.h>
#include "myScanner.h"

static char* symbolStrings[] = {
    "tnot",   "tnotequ",    "tmod",   "tmodAssign", "tident", "tnumber",    /* 0,   1,  2,  3,  4,  5,  */
    "tand",   "tlparen",    "trparen",    "tmul",   "tmulAssign", "tplus",  /* 6,   7,  8,  9,  10, 11, */
    "tinc",   "taddAssign", "tcomma", "tminus", "tdec",   "tsubAssign",     /* 12,  13, 14, 15, 16, 17, */
    "tdiv",   "tdivAssign", "tsemicolon", "tless",  "tlesse", "tassign",    /* 18,  19, 20, 21, 22, 23, */
    "tequal", "tgreat", "tgreate",    "tlbracket",  "trbracket",  "teof",   /* 24,  25, 26, 27, 28, 29, */
    "tconst", "telse",  "tif",    "tint",   "treturn",    "tvoid",          /* 30,  31, 32, 33, 34, 35, */
    "twhile", "tlbrace",    "tor",    "trbrace"                             /* 36,  37, 38, 39          */
};

int main() {
    struct tokenType a;
    printf("Input Mini C : \n");

    while (1) {
        a = scanner();
        if (a.number < 40) {
            printf("Symbol : %s\n", symbolStrings[a.number]);
            if (a.number == 0) {
                printf("Symbol tnot num: %d\n", a.value.num);
                printf("Symbol tnot id : %s\n", a.value.id);
                if (a.value.id < NO_KEYWORDS)
                    printf("Symbol keyword : %s\n", keyword[a.number]);
            }
        }
        else { 
            printf("what? : %s\n", symbolStrings[a.number]);
        }
    }
    return 0;
}

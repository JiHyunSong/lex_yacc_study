  /*-------------------------*/
 /* DEFINITION SECTION         */
 /*-------------------------*/
%{
/* for atoi(), atof() function include */
#include <math.h>
%}
 /* Define useful token formulators */
DIGIT    [0-9]
ID       [a-z][a-z0-9]*
 

%%
 /*-------------------------*/
 /* RULE SECTION                 */
 /*-------------------------*/
{DIGIT}+  {
          printf( "An integer: %s (%d)\n", yytext, atoi( yytext ) );
}

{DIGIT}+"."{DIGIT}* {
          printf( "A float: %s (%g)\n", yytext, atof( yytext ) );
}

if|then|begin|end|procedure|function {
          printf( "A keyword: %s\n", yytext );
}

{ID}   {
          printf( "An identifier: %s\n", yytext );
}

"+"|"-"|"*"|"/"  {
          printf( "An operator: %s\n", yytext );
}

"{"[^}\n]*"}"   {
          ; /* skip the contents in { } as comments. */
}

[ \t\n]+  {
          ; /* ignore the white space(tab, new line.... */
}

.   {
         /* all one character which is
          * unrecognized woth above pattern
          */
          printf( "Unrecognized character: %s\n", yytext );
}

 

%%
 /*-----------------------------*/
 /* USER SUBROUTINE SECTION  */
 /*-----------------------------*/
main( int argc, char **argv )
{
    ++argv, --argc;      /* skip over program name */
    if ( argc > 0 )
            yyin = fopen( argv[0], "r" );
    else
            yyin = stdin;
    yylex();              /* call lexical analyzer */
}

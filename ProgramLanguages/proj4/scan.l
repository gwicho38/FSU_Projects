%{
    #include "y.tab.h"
    void yyerror(char *);
%}

%%

    /*keywords*/
"dump"     { return dump; }
"reset"    { return reset; }
"++"       { return increment; }
"--"       { return decrement; }
"<<"       { return s_l; }
">>"       { return s_r; }


    /* variables */
[a-z]       { yylval.var = *yytext; return VARIABLE; }

    /* integers */
[0-9]+      { yylval.val = atoi(yytext); return INTEGER; }

    /* operators */
[-+()=*;~%&^|/] { return *yytext; }

    /* skip whitespace */
[ \t\n]     ;

<<EOF>>     {return EOF;}

    /* anything else is an error */
.            ;

%%

int yywrap(void) {
    return 1;
}

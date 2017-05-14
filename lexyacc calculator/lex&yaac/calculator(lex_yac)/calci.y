%{
#include "y.tab.h"
#include "parser.h"
#include <math.h>
%}
%token NUMBER NAME
%start statement_list
%right '='
%left  '<' '>' NE LE GE
%left  '+' '-'
%left  '*' '/'
%%
([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {	yylval.dval = atof(yytext); 
						return NUMBER;
						}
[ \t]	;		 /* ignore white space */
[A-Za-z][A-Za-z0-9]*  { /* return symbol pointer */
                         yylval.symp = symlook(yytext);
                         return NAME; 
                      }

"$"	{ return 0; /* end of input */ }

\n|"="|"+"|"-"|"*"|"/"	return yytext[0];

statement_list:	statement '\n'
	           |	statement_list statement '\n'
       	;

statement:	NAME '=' expression	{ $1->value = $3; }
         |	expression		{ printf("= %g\n", $1); }
   	  ;

expression: expression '+' term { $$ = $1 + $3; }
          | expression '-' term { $$ = $1 - $3; }
          | term
	       ;
term:       term '*' factor { $$ = $1 * $3; }
    |       term '/' factor { if ($3 == 0.0)
	                              yyerror("divide by zero");
                              else
				             $$ = $1 / $3;
                            }
    | factor
    ;

factor: '(' expression ')' { $$ = $2; }
      | '-' factor         { $$ = -$2; }
      | NUMBER             { $$ = $1; }
      | NAME               { $$ = $1->value; }
      ;
%%

int main(){


}

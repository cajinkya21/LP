%{
	#include <stdio.h>
	#include <stdlib.h>
%}

letter [a-zA-Z]
digit [0-9]
arthop ["+""-""/""*""%"]
asg "="
bitop ["&""^""|""~"]
comma ","
eos   ";"

%%

(auto)|(break)|(case)|(char)|(const)|(continue)|(default)|(do)|(double)  |
(else)|(enum)|(extern)|(float)|(for)|(goto)|(if)|(int)|(long)|(register) |
(return)|(short)|(signed)|(sizeof)|(static)|(struct)|(switch)|(typedef)|(union) |
(unsigned)|(void)|(volatile)|(while)	{printf(" [K: %s] ",yytext);}

{letter}({letter}|{digit})* 		{printf(" [ID: %s] ",yytext); }

{arthop} 				{printf("[ArOP: %s]",yytext);}
("+""+")				{printf("[InOP: %s]",yytext);}
("-""-")				{printf("[DeOP: %s]",yytext);}
{arthop}*{asg}				{printf("[AsgOP: %s]",yytext);}
("<")|(">")|("=""=")|("!""=")|(">""=")|("<""=")		{printf("[Relational op: %s]",yytext);}
("&""&")|("|""|")|("!")			{printf("[LogOP: %s]",yytext);}
{bitop}|("<""<")|(">"">")		{printf("[BitOP: %s]",yytext);}
{comma}					{printf("[CommaOP: %s]",yytext);}

{digit}+ 				{printf("[int const: %s]",yytext);}
{digit}*"."{digit}*			{printf("[flo const: %s]",yytext);}
("\"")(.)+("\"")			{printf("[Stg const: %s]",yytext);}
"'"."'"					{printf("[Char const: %s]",yytext);}

{eos}					{printf("[EOS: %s]",yytext);}
\n 					{printf("\n");}


%%
int main()
{
	yylex();
	printf("\n**************Done scanning******************\n");
}

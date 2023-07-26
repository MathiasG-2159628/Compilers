%{
#include <stdio.h>
#include "structs.h"
#include "symboltable.h"
#include "yyfunctions.h"
%}



%token IDENTIFIER SEMICOLON INT BOOL PACKAGE RETURN VAR IF FOR LPAREN RPAREN LBRACE RBRACE PLUS MIN MUL DIV PLUSASSIGN MINASSIGN 
%token MULASSIGN DIVASSIGN AND OR NOT INC DEC GT GE LT LE EQ NE INTLITERAL BOOLLITERAL



%left MUL DIV
%left PLUS MIN

%type declaration_statement

//TODO: structs maken voor alle producties zoals in opwarmingsoefening

%%


statement : declaration_statement
          | assignment_statement
          | if_statement
          | for_statement
          | return_statement
          | block_statement
          | compound_statement
          ;

compound_statement : statement statement {}

identifierlist : IDENTIFIER identifierlist
               | IDENTIFIER
               ;

type : INT
     | BOOL
     ;

declaration_statement : VAR identifierlist type SEMICOLON {}
            | VAR identifierlist type EQ expressionlist SEMICOLON {}
            ;

function_declaration : 'func' IDENTIFIER function_signature block_statement{}
            ;

function_signature : LPAREN parameters RPAREN function_result {}
                   ;

function_result : type
                ;
/* 
function_body : block_statement
              ;  */

parameters : parameterlist {}
           | %empty {}
           ;

parameterlist : parameter_declaration {}
              | parameterlist ',' parameter_declaration {}
              ;

parameter_declaration : IDENTIFIER type {}
                      ;
            
assignment_statement : IDENTIFIER  expression SEMICOLON
           ;

if_statement : IF expression LBRACE block_statement %empty{} //Else not implemented
             ;

for_statement : FOR expression block_statement
              ;

return_statement : RETURN expression SEMICOLON
                 ;

block_statement : LBRACE compound_statement RBRACE
                ;

//EXPRESSIONS

expressionlist : expressionlist ',' expression
               | expression
               ;

expression : INTLITERAL 
           | BOOLLITERAL
           | IDENTIFIER {$$ = lookupSymbol($1)}
           | arithmetic_op_expression
           | arithmetic_assign_op_expression
           | boolean_op_expression
           | NOT expression               { $$ = !$2; }
           | expression INC                { $$ = $2 + 1; }
           | expression INC                { $$ = $2 - 1; }
           | LPAREN expression RPAREN
           ;

arithmetic_op_expression : 
             expression PLUS expression   { $$ = $1 + $3; }
           | expression MIN expression    { $$ = $1 - $3; }
           | expression MUL expression    { $$ = $1 * $3; }
           | expression DIV expression    { $$ = $1 / $3; }

arithmetic_assign_op_expression :
             IDENTIFIER PLUSASSIGN expression   { $$ = $1 += $3; } // find typeid for int to validate $3 is numeriic
           | IDENTIFIER MINASSIGN expression    { $$ = $1 -= $3; }
           | IDENTIFIER MULASSIGN expression    { $$ = $1 *= $3; }
           | IDENTIFIER DIVASSIGN expression    { $$ = $1 /= $3; }

boolean_op_expression : 
             expression AND expression    { $$ = $1 && $3; }
           | expression OR expression     { $$ = $1 || $3; }
           | expression EQ expression     { $$ = $1 == $3; } // compare types and do yyerror
           | expression NE expression     { $$ = $1 != $3; }

boolean_arithmetic_op_expression:
             expression GT expression     { $$ = $1 > $3; }
           | expression GE expression     { $$ = $1 >= $3; }
           | expression LT expression     { $$ = $1 < $3; }
           | expression LE expression     { $$ = $1 <= $3; }

         

%%

int main() {
    yyparse();
    return 0;
}

int yyerror(const char *message) {
    printf("Error: %s\n", message);
    return 1;
}

int yylex() {
}







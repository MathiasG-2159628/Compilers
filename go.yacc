%{
#include <stdio.h>
%}

%token SEMICOLON IDENTIFIER INT BOOL PACKAGE RETURN VAR IF FOR LPAREN RPAREN LBRACE RBRACE
%token PLUS MIN MUL DIV PLUSASSIGN MINASSIGN MULASSIGN DIVASSIGN AND OR NOT INC DEC GT GE LT LE EQ NE
%token INTLITERAL BOOLLITERAL

%left '+' '-'
%left '*' '/'
%right '='

%%

program : /* empty */
        | program statement '\n'
        ;

statement : declaration
          | assignment
          | if_statement
          | for_statement
          | return_statement
          ;

declaration : VAR IDENTIFIER ':' type_specifier SEMICOLON
            ;

type_specifier : INT
               | BOOL
               ;

assignment : IDENTIFIER  expression SEMICOLON
           ;

if_statement : IF expression LBRACE program RBRACE
             ;

for_statement : FOR LPAREN assignment SEMICOLON expression SEMICOLON assignment RPAREN LBRACE program RBRACE
              ;

return_statement : RETURN expression SEMICOLON
                 ;

expression : INTLITERAL
           | BOOLLITERAL
           | IDENTIFIER
           | expression PLUS expression   { $$ = $1 + $3; }
           | expression MIN expression    { $$ = $1 - $3; }
           | expression MUL expression    { $$ = $1 * $3; }
           | expression DIV expression    { $$ = $1 / $3; }
           | expression PLUSASSIGN expression   { $$ = $1 += $3; }
           | expression MINASSIGN expression    { $$ = $1 -= $3; }
           | expression MULASSIGN expression    { $$ = $1 *= $3; }
           | expression DIVASSIGN expression    { $$ = $1 /= $3; }
           | expression AND expression    { $$ = $1 && $3; }
           | expression OR expression     { $$ = $1 || $3; }
           | NOT expression               { $$ = !$2; }
           | INC expression               { $$ = $2 + 1; }
           | DEC expression               { $$ = $2 - 1; }
           | expression GT expression     { $$ = $1 > $3; }
           | expression GE expression     { $$ = $1 >= $3; }
           | expression LT expression     { $$ = $1 < $3; }
           | expression LE expression     { $$ = $1 <= $3; }
           | expression EQ expression     { $$ = $1 == $3; }
           | expression NE expression     { $$ = $1 != $3; }
           | LPAREN expression RPAREN
           ;

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

void yyerror(const char* message) {
    printf("Error: %s\n", message);
    exit(1);
}





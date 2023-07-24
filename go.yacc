%{
#include <stdio.h>
int yylex();

struct Expression{
    void EvaluateExpression()

}

struct Symbol{
    char name[10];
    void* value; 
    struct Symbol* next;
};

struct SymbolTable{
    struct Symbol* head;
};

struct SymbolTable symbolTable = {NULL};

void addSymbol(SymbolTable* symbolTable, char* name, int value) {
    struct Symbol* newSymbol = {NULL, NULL, NULL}
    strcpy(newSymbol->name, name);
    newSymbol->value = value;
    newSymbol->next = st->head;
    st->head = newSymbol;
}

void updateSymbol(struct SymbolTable* st, char* name, int value) {
    struct Symbol* current = st->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    printf("Variabele '%s' bestaat niet in de symbol table.\n", name);

}

int lookupSymbol(struct SymbolTable* st, char* name) {
    struct Symbol* current = st->head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current->value;
        }
        current = current->next;
    }

    printf("Variabele '%s' is niet aanwezig in de symbol table.\n", name);
    return 0;
}


%}



%token IDENTIFIER SEMICOLON INT BOOL PACKAGE RETURN VAR IF FOR LPAREN RPAREN LBRACE RBRACE PLUS MIN MUL DIV PLUSASSIGN MINASSIGN 
%token MULASSIGN DIVASSIGN AND OR NOT INC DEC GT GE LT LE EQ NE INTLITERAL BOOLLITERAL



%left MUL DIV
%left PLUS MIN

%type declaration

//TODO: structs maken voor alle producties zoals in opwarmingsoefening

%%

program : //$
        | program statement '\n'
        ;

statement : declaration
          | assignment
          | if_statement
          | for_statement
          | return_statement
          | block
          ;

statementlist : statement {}
              | statementlist statement {}

identifierlist : IDENTIFIER identifierlist
               | IDENTIFIER
               ;


type : INT
     | BOOL
     ;

declaration : VAR identifierlist type SEMICOLON {}
            | VAR identifierlist type EQ expressionlist SEMICOLON {}
            ;

function_declaration : 'func' IDENTIFIER function_signature function_body{}
            ;

function_signature : LPAREN parameters RPAREN function_result {}
                   ;

function_result : type
                ;

function_body : block
              ; 

parameters : parameterlist {}
           | %empty {}
           ;

parameterlist : parameter_declaration {}
              | parameterlist ',' parameter_declaration {}
              ;

parameter_declaration : IDENTIFIER type {}
                      ;
            
assignment : IDENTIFIER  expression SEMICOLON
           ;

if_statement : IF expression LBRACE block if_statement_continuation{}
             ;

if_statement_continuation : %empty //Else not implemented
                          | 

for_statement : FOR expression block
              ;

return_statement : RETURN expression SEMICOLON
                 ;

block : LBRACE statementlist RBRACE
      ;

//EXPRESSIONS

expressionlist : expressionlist ',' expression
               | expression
               ;

expression : INTLITERAL 
           | BOOLLITERAL
           | IDENTIFIER {$$ = lookupSymbol($1)}
           | op_expression
           | NOT expression               { $$ = !$2; }
           | INC expression               { $$ = $2 + 1; }
           | DEC expression               { $$ = $2 - 1; }
           | LPAREN expression RPAREN
           ;

op_expression : expression PLUS expression   { $$ = $1 + $3; }
           | expression MIN expression    { $$ = $1 - $3; }
           | expression MUL expression    { $$ = $1 * $3; }
           | expression DIV expression    { $$ = $1 / $3; }
           | expression PLUSASSIGN expression   { $$ = $1 += $3; }
           | expression MINASSIGN expression    { $$ = $1 -= $3; }
           | expression MULASSIGN expression    { $$ = $1 *= $3; }
           | expression DIVASSIGN expression    { $$ = $1 /= $3; }
           | expression AND expression    { $$ = $1 && $3; }
           | expression OR expression     { $$ = $1 || $3; }
           | expression GT expression     { $$ = $1 > $3; }
           | expression GE expression     { $$ = $1 >= $3; }
           | expression LT expression     { $$ = $1 < $3; }
           | expression LE expression     { $$ = $1 <= $3; }
           | expression EQ expression     { $$ = $1 == $3; }
           | expression NE expression     { $$ = $1 != $3; }

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





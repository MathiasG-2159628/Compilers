%{
#include <stdio.h>

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

%union{
    char* id;
    int integer;
    bool boolean;
}

%token SEMICOLON INT BOOL PACKAGE RETURN VAR IF FOR LPAREN RPAREN LBRACE RBRACE
%token PLUS MIN MUL DIV PLUSASSIGN MINASSIGN MULASSIGN DIVASSIGN AND OR NOT INC DEC GT GE LT LE EQ NE

%token <id> IDENTIFIER
%token <integer> INTLITERAL
%token <boolean> BOOLLITERAL


%left MUL DIV
%left PLUS MIN

%%

program : //$
        | program statement '\n'
        ;

statement : declaration
          | assignment
          | if_statement
          | for_statement
          | return_statement
          ;

//Todo: expressionlist, .... andere expressies
declaration : VAR IDENTIFIER INT  {$$ = addSymbol(&symbolTable, $1, 0)}
              VAR IDENTIFIER BOOL {$$ = addSymbol(&symbolTable, $1, false)}
            ;

/* type_specifier : INT
               | BOOL
               ; */

assignment : IDENTIFIER  expression SEMICOLON
           ;

if_statement : IF expression LBRACE statement RBRACE {if($2){$$ = $4}}
             ;

for_statement : FOR LPAREN assignment SEMICOLON expression SEMICOLON assignment RPAREN LBRACE program RBRACE
              ;

return_statement : RETURN expression SEMICOLON
                 ;

expression : INTLITERAL 
           | BOOLLITERAL
           | IDENTIFIER {$$ = lookupSymbol($1)}
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





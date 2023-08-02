#include <stdio.h>
#include "tokens.h"
#include "lexer.h"

/* Array with tokens such that index = tokenid - 250*/
char *tokens[] = {
"SEMICOLON",
"ID",
"INT", "BOOL",
"PACKAGE", "RETURN", "VAR", "IF", "FOR",
"LPAREN", "RPAREN", "LBRACE", "RBRACE",
"PLUS", "MIN", "MUL", "DIV", 
"PLUSASSIGN", "MINASSIGN", "MULASSIGN", "DIVASSIGN",
"AND", "OR", "NOT",
"INC", "DEC",
"GT", "GE", "LT", "LE", "EQ", "NE",
"INTLITERAL", "BOOLLITERAL"
}; 

int main(int argc, char* argv[])
{
  int tokenid;
  /*
  /* If we de not explicitly bind yyin to a file, stdin is assumed. */
  yyin = fopen(argv[1], "r");
 
  while (tokenid=yylex())
    {
      /* Token codes start from 250 */ 
      printf(" %s", tokens[tokenid-250]);

      /* Append value */
      if ( (tokenid == IDEN) || (tokenid == INT) || (tokenid == BOOL) ) 
	printf("=\"%s\"", yytext);
    }
    printf("\n");

  return 0;
}

%{
/* 
go.lex: lex-file for go basisniveau
*/

#include "tokens.h"

  /* Keep track of current position of lex for error messages, i.e. 
     the position just *after* the last token read */
  int line_nr = 1;
  int col_nr = 1; 
  int lastTokenType = -1;

%}

semicolon             ";"
integer               "int"
boolean               "bool"
package               "package"
return                "return"
var                   "var"
if                    "if"
for                   "for"
leftparenthesis       "("
rightparenthesis      ")"
leftbracket           "{"
rightbracket          "}"
plus                  "+"
min                   "-"
mul                   "*"
div                   "/"
plusassign            "+="
minassign             "-="
mulassign             "*="
divassign             "/="
and                   "&&"
or                    "||"
not                   "!"
increment             "++"
decrement             "--"
greaterthan           ">"
greaterorequal        ">="
lesserthan            "<"
lesserorequal         "<="
equals                "=="
notequals             "!="
intliteral            "-"?[0-9]+
boolliteral          "true"|"false"
identifier            [a-z]([a-z]|[0-9])*



%%
" "                       {}
{semicolon}               {lastTokenType = SEMICOLON; return SEMICOLON;}
{integer}                 {lastTokenType = INT; return INT;}
{boolean}                 {lastTokenType = BOOL; return BOOL;}                
{package}                 {lastTokenType = PACKAGE; return PACKAGE;}               
{return}                  {lastTokenType = RETURN; return RETURN;}   
{var}                     {lastTokenType = VAR; return VAR;}
{if}                      {lastTokenType = IF; return IF;}
{for}                     {lastTokenType = FOR; return FOR;}
{leftparenthesis}         {lastTokenType = LPAREN; return LPAREN;}
{rightparenthesis}        {lastTokenType = RPAREN; return RPAREN;}
{leftbracket}             {lastTokenType = LEFTBRACKET; return LBRACE;}
{rightbracket}            {lastTokenType = RIGHTBRACKET; return RBRACE;}
{plus}                    {lastTokenType = PLUS; return PLUS;}
{min}                     {lastTokenType = MIN; return MIN;}
{mul}                     {lastTokenType = MUL; return MUL;}
{div}                     {lastTokenType = DIV; return DIV;}
{plusassign}              {lastTokenType = PLUSASSIGN; return PLUSASSIGN;}
{minassign}               {lastTokenType = MINASSIGN; return MINASSIGN;}
{mulassign}               {lastTokenType = MULASSIGN; return MULASSIGN;}
{divassign}               {lastTokenType = DIVASSIGN; return DIVASSIGN;}
{and}                     {lastTokenType = AND; return AND;}
{or}                      {lastTokenType = OR; return OR;}
{not}                     {lastTokenType = NOT; return NOT;}
{increment}               {lastTokenType = INC; return INC;}
{decrement}               {lastTokenType = DEC; return DEC;}
{greaterthan}             {lastTokenType = GT; return GT;}
{greaterorequal}          {lastTokenType = GE; return GE;}
{lesserthan}              {lastTokenType = LT; return LT;}
{lesserorequal}           {lastTokenType = LE; return LE;}
{equals}                  {lastTokenType = EQ; return EQ;}
{notequals}               {lastTokenType = NE;  return NE;}
{intliteral}              {lastTokenType = INTLITERAL; return INTLITERAL;}
{boolliteral}             {lastTokenType = BOOLLITERAL; return BOOLLITERAL;}
{identifier}              {lastTokenType = IDENTIFIER; return IDENTIFIER;}
"\n"                      {if (lastTokenType == IDENTIFIER || lastTokenType == CONSTANT || lastTokenType == CLOSING_BRACKET) {
                               lastTokenType = -1; 
                               return SEMICOLON; 
                           }}

.            {
  if (yytext[0] < ' '){ /* non-printable char */
  
    /*yyerror*/ fprintf(stderr,"illegal character: ^%c",yytext[0] + '@'); 
  }
  else {
    if (yytext[0] > '~') {
      
      /* non-printable char printed as octal int padded with zeros, eg \012*/
      /*yyerror(*/fprintf(stderr,"illegal character: \\%03o", (int) yytext[0]);
    }
    else {
      /*Hier hit de error*/
      /*yyerror(*/fprintf(stderr,"illegal character: %s",yytext);
    }
  }
  /* lex read exactly one char; the illegal one */
  fprintf(stderr," at line %d column %d\n", line_nr, (col_nr-1));
			       }
%%

/* Function called by (f)lex when EOF is read. If yywrap returns a
   true (non-zero) (f)lex will terminate and continue otherwise.*/
int yywrap(){
  return (1);
}

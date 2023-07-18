%{
/* 
go.lex: lex-file for go basisniveau
*/

#include "tokens.h"

  /* Keep track of current position of lex for error messages, i.e. 
     the position just *after* the last token read */
  int line_nr = 1;
  int col_nr = 1; 

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
{semicolon}               {return SEMICOLON;}
{integer}                 {return INT;}
{boolean}                 {return BOOL;}                
{package}                 {return PACKAGE;}               
{return}                  {return RETURN;}   
{var}                     {return VAR;}
{if}                      {return IF;}
{for}                     {return FOR;}
{leftparenthesis}         {return LPAREN;}
{rightparenthesis}        {return RPAREN;}
{leftbracket}             {return LBRACE;}
{rightbracket}            {return RBRACE;}
{plus}                    {return PLUS;}
{min}                     {return MIN;}
{mul}                     {return MUL;}
{div}                     {return DIV;}
{plusassign}              {return PLUSASSIGN;}
{minassign}               {return MINASSIGN;}
{mulassign}               {return MULASSIGN;}
{divassign}               {return DIVASSIGN;}
{and}                     {return AND;}
{or}                      {return OR;}
{not}                     {return NOT;}
{increment}               {return INC;}
{decrement}               {return DEC;}
{greaterthan}             {return GT;}
{greaterorequal}          {return GE;}
{lesserthan}              {return LT;}
{lesserorequal}           {return LE;}
{equals}                  {return EQ;}
{notequals}               {return NE;}
{intliteral}              {return INTLITERAL;}
{boolliteral}             {return BOOLLITERAL;}
{identifier}              {return IDENTIFIER;}


.      {
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

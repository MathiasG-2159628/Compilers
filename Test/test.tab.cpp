
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "test.ypp"


  #include <string>
  #include <stdio.h>
  #include <iostream>
  #include "structs.hpp"
  #include "symboltable.hpp"
  #include <string>
  #include "ReturnValue.hpp" 
  #include "tokens.h"
  #include "lexer.h"
  #include "functiontable.hpp"
  #include "lex.yy.c"

  Stm thesyntree;



/* Line 189 of yacc.c  */
#line 92 "test.tab.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDEN = 258,
     BOOLLITERAL = 259,
     INTLITERAL = 260,
     SEMICOLON = 261,
     INT = 262,
     BOOL = 263,
     RETURN = 264,
     VAR = 265,
     IF = 266,
     FOR = 267,
     LPAREN = 268,
     RPAREN = 269,
     LBRACE = 270,
     RBRACE = 271,
     PLUS = 272,
     MIN = 273,
     MUL = 274,
     DIV = 275,
     PLUSASSIGN = 276,
     MINASSIGN = 277,
     MULASSIGN = 278,
     DIVASSIGN = 279,
     AND = 280,
     OR = 281,
     NOT = 282,
     INC = 283,
     DEC = 284,
     GT = 285,
     GE = 286,
     LT = 287,
     LE = 288,
     EQ = 289,
     NE = 290,
     COMMA = 291,
     PRINT = 292,
     FUNC = 293,
     PACKAGE = 294,
     IS = 295
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 25 "test.ypp"

  //Literals and base classes
  char* id;

  bool boollit;
  int intlit;
  Stm stm;
  Exp exp;

  //Lists
  ExpList* explist;
  StmList* stmlist;
  IdList*  idlist;
  ParamList* paramlist;

  //Function related stuff
  Param_declaration* paramdecl;
  Function_signature* funcsig;



/* Line 214 of yacc.c  */
#line 190 "test.tab.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 202 "test.tab.cpp"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  50
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   336

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNRULES -- Number of states.  */
#define YYNSTATES  145

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     8,    10,    12,    14,    16,
      18,    20,    22,    24,    26,    28,    30,    34,    37,    39,
      43,    46,    50,    54,    60,    66,    73,    80,    85,    90,
      95,   100,   105,   110,   115,   119,   123,   126,   130,   137,
     143,   148,   153,   157,   161,   165,   168,   170,   174,   177,
     180,   186,   191,   195,   197,   199,   201,   203,   206,   210,
     212,   214,   216,   218,   222,   226,   230,   234,   238,   242,
     246,   250,   254,   258,   262,   266,   271
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      42,     0,    -1,    45,    -1,    -1,    46,    -1,    47,    -1,
      48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,    -1,
      53,    -1,    54,    -1,    55,    -1,    59,    -1,     3,    -1,
      44,    36,     3,    -1,    43,    45,    -1,    43,    -1,    15,
      45,    16,    -1,    15,    16,    -1,    11,    61,    46,    -1,
      12,    61,    46,    -1,    37,    13,    60,    14,     6,    -1,
      10,    44,    40,    60,     6,    -1,    10,    44,     8,    40,
      60,     6,    -1,    10,    44,     7,    40,    60,     6,    -1,
      10,    44,     8,     6,    -1,    10,    44,     7,     6,    -1,
      44,    40,    60,     6,    -1,     3,    23,    61,     6,    -1,
       3,    24,    61,     6,    -1,     3,    21,    61,     6,    -1,
       3,    22,    61,     6,    -1,     3,    28,     6,    -1,     3,
      29,     6,    -1,     9,     6,    -1,     9,    61,     6,    -1,
      38,     3,    56,    15,    45,    16,    -1,    38,     3,    56,
      15,    16,    -1,    13,    57,    14,     7,    -1,    13,    57,
      14,     8,    -1,    13,    57,    14,    -1,    13,    14,     7,
      -1,    13,    14,     8,    -1,    13,    14,    -1,    58,    -1,
      57,    36,    58,    -1,     3,     7,    -1,     3,     8,    -1,
       3,    13,    60,    14,     6,    -1,     3,    13,    14,     6,
      -1,    60,    36,    61,    -1,    61,    -1,     5,    -1,     4,
      -1,     3,    -1,    27,    61,    -1,    13,    61,    14,    -1,
      62,    -1,    63,    -1,    64,    -1,    65,    -1,    61,    19,
      61,    -1,    61,    20,    61,    -1,    61,    17,    61,    -1,
      61,    18,    61,    -1,    61,    25,    61,    -1,    61,    26,
      61,    -1,    61,    34,    61,    -1,    61,    35,    61,    -1,
      61,    30,    61,    -1,    61,    31,    61,    -1,    61,    32,
      61,    -1,    61,    33,    61,    -1,     3,    13,    60,    14,
      -1,     3,    13,    14,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   105,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   128,   132,   138,   146,   148,   152,
     154,   160,   164,   169,   173,   175,   177,   179,   181,   186,
     192,   194,   196,   198,   203,   210,   218,   222,   229,   236,
     249,   256,   259,   262,   265,   268,   274,   278,   283,   287,
     294,   301,   311,   313,   317,   319,   321,   326,   327,   328,
     329,   330,   331,   335,   336,   337,   338,   342,   343,   344,
     345,   349,   350,   351,   352,   355,   363
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDEN", "BOOLLITERAL", "INTLITERAL",
  "SEMICOLON", "INT", "BOOL", "RETURN", "VAR", "IF", "FOR", "LPAREN",
  "RPAREN", "LBRACE", "RBRACE", "PLUS", "MIN", "MUL", "DIV", "PLUSASSIGN",
  "MINASSIGN", "MULASSIGN", "DIVASSIGN", "AND", "OR", "NOT", "INC", "DEC",
  "GT", "GE", "LT", "LE", "EQ", "NE", "COMMA", "PRINT", "FUNC", "PACKAGE",
  "IS", "$accept", "program", "statement", "identifierlist",
  "statementlist", "block_statement", "if_statement", "for_statement",
  "print_statement", "declaration_statement", "assignment_statement",
  "arithmetic_assign_op_statement", "inc_dec_statement",
  "return_statement", "function_declaration_statement",
  "function_signature", "parameterlist", "parameter_declaration",
  "void_function_statement", "expressionlist", "expression",
  "arithmetic_op_expression", "boolean_op_expression",
  "boolean_arithmetic_op_expression", "function_expression", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    42,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    44,    44,    45,    45,    46,
      46,    47,    48,    49,    50,    50,    50,    50,    50,    51,
      52,    52,    52,    52,    53,    53,    54,    54,    55,    55,
      56,    56,    56,    56,    56,    56,    57,    57,    58,    58,
      59,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    62,    62,    63,    63,    63,
      63,    64,    64,    64,    64,    65,    65
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     2,     1,     3,
       2,     3,     3,     5,     5,     6,     6,     4,     4,     4,
       4,     4,     4,     4,     3,     3,     2,     3,     6,     5,
       4,     4,     3,     3,     3,     2,     1,     3,     2,     2,
       5,     4,     3,     1,     1,     1,     1,     2,     3,     1,
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     4,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,    15,     0,     0,     0,     0,     0,     0,     0,     0,
      18,     0,     2,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,     0,     0,     0,     0,     0,     0,
       0,    56,    55,    54,    36,     0,     0,     0,    59,    60,
      61,    62,    15,     0,     0,     0,    20,     0,     0,     0,
       1,    17,     0,     0,     0,     0,    53,     0,     0,     0,
       0,    34,    35,     0,     0,    57,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,    22,    19,     0,     0,     0,    16,     0,
      51,     0,     0,    32,    33,    30,    31,    76,     0,    58,
      65,    66,    63,    64,    67,    68,    71,    72,    73,    74,
      69,    70,    28,     0,    27,     0,     0,     0,     0,    45,
       0,    46,     0,    29,    50,    52,    75,     0,     0,    24,
      23,    48,    49,    43,    44,    42,     0,    39,     0,    26,
      25,    40,    41,    47,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    87,   120,   121,    23,    55,
      56,    38,    39,    40,    41
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -34
static const yytype_int16 yypact[] =
{
      85,   289,   104,     4,   220,   220,     7,    20,    35,    14,
      85,    10,   -34,   -34,   -34,   -34,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   205,   220,   220,   220,   220,    34,
      57,    74,   -34,   -34,   -34,   220,   220,    95,   -34,   -34,
     -34,   -34,   -34,    24,   244,   244,   -34,    86,   220,    98,
     -34,   -34,   115,   220,   113,    -2,   263,   118,   139,   160,
     181,   -34,   -34,   217,   223,   290,   -34,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,    -5,
       2,   220,   -34,   -34,   -34,    11,    -1,   117,   -34,     3,
     -34,   127,   220,   -34,   -34,   -34,   -34,   -34,    29,   -34,
     290,   290,   274,   274,    27,   108,    73,    73,    73,    73,
     301,   301,   -34,   220,   -34,   220,     5,   133,    59,    78,
      45,   -34,    46,   -34,   -34,   263,   -34,    15,    18,   -34,
     -34,   -34,   -34,   -34,   -34,    82,   137,   -34,   125,   -34,
     -34,   -34,   -34,   -34,   -34
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -34,   -34,   -34,   143,    -6,    47,   -34,   -34,   -34,   -34,
     -34,   -34,   -34,   -34,   -34,   -34,   -34,     6,   -34,   -33,
       1,   -34,   -34,   -34,   -34
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      47,   112,   118,    37,    51,    44,    45,    42,   114,   123,
       1,   129,    91,   119,    50,    85,     2,     3,     4,     5,
      89,   139,     6,    46,   140,   117,    57,    58,    59,    60,
      98,    79,    80,    48,    92,   113,    64,    65,    49,    92,
      61,    92,   115,   126,     7,     8,    52,    92,   116,     1,
      53,    92,    -1,    72,    92,     2,     3,     4,     5,   135,
      52,     6,   137,    62,    81,    92,   131,   132,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     127,   136,   128,     7,     8,   133,   134,    63,     1,   141,
     142,    82,    83,   125,     2,     3,     4,     5,    71,    72,
       6,    66,    84,    -1,    -1,    -1,    -1,    31,    32,    33,
      34,    86,    67,    68,    69,    70,   138,    35,    88,    90,
      71,    72,     7,     8,    93,    73,    74,    75,    76,    77,
      78,    36,   122,   124,    -1,    67,    68,    69,    70,   130,
     118,   144,   143,    71,    72,    94,    43,     0,    73,    74,
      75,    76,    77,    78,     0,     0,    67,    68,    69,    70,
       0,     0,     0,     0,    71,    72,    95,     0,     0,    73,
      74,    75,    76,    77,    78,     0,     0,    67,    68,    69,
      70,     0,     0,     0,     0,    71,    72,    96,     0,     0,
      73,    74,    75,    76,    77,    78,     0,     0,    67,    68,
      69,    70,     0,     0,     0,     0,    71,    72,    31,    32,
      33,    73,    74,    75,    76,    77,    78,     0,    35,    54,
      31,    32,    33,    31,    32,    33,     0,     0,     0,     0,
      35,    97,    36,    35,     0,     0,     0,    99,     0,     0,
      67,    68,    69,    70,    36,     0,     0,    36,    71,    72,
       0,     0,     0,    73,    74,    75,    76,    77,    78,     6,
       0,    67,    68,    69,    70,     0,     0,     0,     0,    71,
      72,     0,     0,     0,    73,    74,    75,    76,    77,    78,
      67,    68,    69,    70,     0,     0,     0,     0,    71,    72,
       0,    67,    68,    73,    74,    75,    76,    77,    78,    71,
      72,     0,    24,     0,    73,    74,    75,    76,    77,    78,
      25,    26,    27,    28,     0,    71,    72,    29,    30,     0,
      73,    74,    75,    76,    77,    78,    71,    72,     0,     0,
       0,    73,    74,    75,    76,    -1,    -1
};

static const yytype_int16 yycheck[] =
{
       6,     6,     3,     2,    10,     4,     5,     3,     6,     6,
       3,     6,    14,    14,     0,    48,     9,    10,    11,    12,
      53,     6,    15,    16,     6,    14,    25,    26,    27,    28,
      63,     7,     8,    13,    36,    40,    35,    36,     3,    36,
       6,    36,    40,    14,    37,    38,    36,    36,    81,     3,
      40,    36,    25,    26,    36,     9,    10,    11,    12,    14,
      36,    15,    16,     6,    40,    36,     7,     8,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
     113,    36,   115,    37,    38,     7,     8,    13,     3,     7,
       8,    44,    45,    92,     9,    10,    11,    12,    25,    26,
      15,     6,    16,    30,    31,    32,    33,     3,     4,     5,
       6,    13,    17,    18,    19,    20,   122,    13,     3,     6,
      25,    26,    37,    38,     6,    30,    31,    32,    33,    34,
      35,    27,    15,     6,    26,    17,    18,    19,    20,     6,
       3,    16,   136,    25,    26,     6,     3,    -1,    30,    31,
      32,    33,    34,    35,    -1,    -1,    17,    18,    19,    20,
      -1,    -1,    -1,    -1,    25,    26,     6,    -1,    -1,    30,
      31,    32,    33,    34,    35,    -1,    -1,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    25,    26,     6,    -1,    -1,
      30,    31,    32,    33,    34,    35,    -1,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,    -1,    25,    26,     3,     4,
       5,    30,    31,    32,    33,    34,    35,    -1,    13,    14,
       3,     4,     5,     3,     4,     5,    -1,    -1,    -1,    -1,
      13,    14,    27,    13,    -1,    -1,    -1,    14,    -1,    -1,
      17,    18,    19,    20,    27,    -1,    -1,    27,    25,    26,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    15,
      -1,    17,    18,    19,    20,    -1,    -1,    -1,    -1,    25,
      26,    -1,    -1,    -1,    30,    31,    32,    33,    34,    35,
      17,    18,    19,    20,    -1,    -1,    -1,    -1,    25,    26,
      -1,    17,    18,    30,    31,    32,    33,    34,    35,    25,
      26,    -1,    13,    -1,    30,    31,    32,    33,    34,    35,
      21,    22,    23,    24,    -1,    25,    26,    28,    29,    -1,
      30,    31,    32,    33,    34,    35,    25,    26,    -1,    -1,
      -1,    30,    31,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     9,    10,    11,    12,    15,    37,    38,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    59,    13,    21,    22,    23,    24,    28,
      29,     3,     4,     5,     6,    13,    27,    61,    62,    63,
      64,    65,     3,    44,    61,    61,    16,    45,    13,     3,
       0,    45,    36,    40,    14,    60,    61,    61,    61,    61,
      61,     6,     6,    13,    61,    61,     6,    17,    18,    19,
      20,    25,    26,    30,    31,    32,    33,    34,    35,     7,
       8,    40,    46,    46,    16,    60,    13,    56,     3,    60,
       6,    14,    36,     6,     6,     6,     6,    14,    60,    14,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,     6,    40,     6,    40,    60,    14,     3,    14,
      57,    58,    15,     6,     6,    61,    14,    60,    60,     6,
       6,     7,     8,     7,     8,    14,    36,    16,    45,     6,
       6,     7,     8,    58,    16
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 15:

/* Line 1455 of yacc.c  */
#line 132 "test.ypp"
    {
                  std::cout << "identifierlist : IDEN " << (yyvsp[(1) - (1)].id) << "\n";
                  char* identifier = new char[std::strlen((yyvsp[(1) - (1)].id)) + 1];
                  std::strcpy(identifier, (yyvsp[(1) - (1)].id));
                  (yyval.idlist) = new IdList(identifier, nullptr);
                ;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 138 "test.ypp"
    {
                  std::cout << "identifierlist : identifierlist COMMA IDEN " << (yyvsp[(3) - (3)].id) << "\n";
                  char* identifier = new char[std::strlen((yyvsp[(3) - (3)].id)) + 1];
                  std::strcpy(identifier, (yyvsp[(3) - (3)].id));
                  (yyval.idlist) = new IdList(identifier, (yyvsp[(1) - (3)].idlist));
                ;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 146 "test.ypp"
    {std::cout << "statementlist: statement statementlist \n"; 
                                        (yyval.stmlist) = new StmList((yyvsp[(1) - (2)].stm), (yyvsp[(2) - (2)].stmlist));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 148 "test.ypp"
    {std::cout << "statementlist: statement \n"; 
                                        (yyval.stmlist) = new StmList((yyvsp[(1) - (1)].stm), nullptr);;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 152 "test.ypp"
    {std::cout << "LBRACE statementlist RBRACE \n";
                                              (yyval.stm) = new BlockStm((yyvsp[(2) - (3)].stmlist)); thesyntree = (yyval.stm);;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 154 "test.ypp"
    {std::cout << "LBRACE RBRACE \n";
                                              (yyval.stm) = new BlockStm(nullptr); thesyntree = (yyval.stm);;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 160 "test.ypp"
    {std::cout << "IF expression block_statement \n"; 
                                                          (yyval.stm) = new If_stm((yyvsp[(2) - (3)].exp), (yyvsp[(3) - (3)].stm)); thesyntree = (yyval.stm);;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 164 "test.ypp"
    {std::cout << "for_statement : FOR LPAREN expression RPAREN block_statement \n"; 
                                                            (yyval.stm) = new For_stm((yyvsp[(2) - (3)].exp), (yyvsp[(3) - (3)].stm)); thesyntree = (yyval.stm);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 169 "test.ypp"
    {std::cout << "print_statement : PRINT LPAREN expressionlist RPAREN \n"; 
                                                      (yyval.stm) = new PrintStm((yyvsp[(3) - (5)].explist)); thesyntree = (yyval.stm);;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 173 "test.ypp"
    {std::cout << "declaration_statement : VAR identifierlist IS expressionlist SEMICOLON \n";
                                                                      (yyval.stm) = new DeclarationStm(-1, (yyvsp[(2) - (5)].idlist), (yyvsp[(4) - (5)].explist)); thesyntree = (yyval.stm);;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 175 "test.ypp"
    {std::cout << "declaration_statement : VAR identifierlist type IS expressionlist SEMICOLON \n";
                                                                            (yyval.stm) = new DeclarationStm(BOOL, (yyvsp[(2) - (6)].idlist), (yyvsp[(5) - (6)].explist)); thesyntree = (yyval.stm);;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 177 "test.ypp"
    {std::cout << "declaration_statement : VAR identifierlist type IS expressionlist SEMICOLON \n";
                                                                            (yyval.stm) = new DeclarationStm(INT, (yyvsp[(2) - (6)].idlist), (yyvsp[(5) - (6)].explist)); thesyntree = (yyval.stm);;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 179 "test.ypp"
    {std::cout << "declaration_statement : VAR identifierlist type SEMICOLON \n";
                                    (yyval.stm) = new DeclarationStm(BOOL, (yyvsp[(2) - (4)].idlist), nullptr); thesyntree = (yyval.stm);;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 181 "test.ypp"
    {std::cout << "declaration_statement : VAR identifierlist type SEMICOLON \n";
                                    (yyval.stm) = new DeclarationStm(INT, (yyvsp[(2) - (4)].idlist), nullptr); thesyntree = (yyval.stm);;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 186 "test.ypp"
    {std::cout << "assignment_statement : identifierlist IS expressionlist SEMICOLON \n";
                                                                  (yyval.stm) = new AssignStm((yyvsp[(1) - (4)].idlist), (yyvsp[(3) - (4)].explist)); thesyntree = (yyval.stm);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 192 "test.ypp"
    { std::cout << "arithmetic_assign_op_statement : IDEN MULASSIGN expression" << std::endl;
                                          (yyval.stm) = new ArithmeticAssignOpStm((yyvsp[(1) - (4)].id), MULASSIGN, (yyvsp[(3) - (4)].exp)); ;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 194 "test.ypp"
    { std::cout << "arithmetic_assign_op_statement : IDEN DIVASSIGN expression" << std::endl;                                       
                                          (yyval.stm) = new ArithmeticAssignOpStm((yyvsp[(1) - (4)].id), DIVASSIGN, (yyvsp[(3) - (4)].exp)); ;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 196 "test.ypp"
    { std::cout << "arithmetic_assign_op_statement : IDEN PLUSASSIGN expression" << std::endl;
                                          (yyval.stm) = new ArithmeticAssignOpStm((yyvsp[(1) - (4)].id), PLUSASSIGN, (yyvsp[(3) - (4)].exp)); ;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 198 "test.ypp"
    { std::cout << "arithmetic_assign_op_statement : IDEN MINASSIGN expression" << std::endl;
                                          (yyval.stm) = new ArithmeticAssignOpStm((yyvsp[(1) - (4)].id), MINASSIGN, (yyvsp[(3) - (4)].exp)); ;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 203 "test.ypp"
    {
                      
                      char* identifier = new char[std::strlen(yylval.id) + 1];
                      std::strcpy(identifier, yylval.id);
                      std::cout << "inc_dec_statement : IDEN " << identifier << "INC SEMICOLON " << std::endl;
                      (yyval.stm) = new IncDecStm(INC,identifier);
                      ;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 210 "test.ypp"
    {
                      std::cout << "inc_dec_statement : IDEN DEC SEMICOLON " << std::endl;
                      char* identifier = new char[std::strlen((yyvsp[(1) - (3)].id)) + 1];
                      std::strcpy(identifier, (yyvsp[(1) - (3)].id));
                      (yyval.stm) = new IncDecStm(DEC,identifier);
                      ;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 218 "test.ypp"
    {
                  std::cout << "return_statement : RETURN SEMICOLON " << std::endl;
                  (yyval.stm) = new ReturnStm(nullptr); 
                  thesyntree = (yyval.stm);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 222 "test.ypp"
    {
                  std::cout << "return_statement : RETURN expression SEMICOLON  " << std::endl;
                  (yyval.stm) = new ReturnStm((yyvsp[(2) - (3)].exp)); 
                  thesyntree = (yyval.stm);;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 229 "test.ypp"
    {
                                char* identifier = new char[std::strlen((yyvsp[(2) - (6)].id)) + 1];
                                std::strcpy(identifier, (yyvsp[(2) - (6)].id));
                                std::cout << "function_declaration_statement : FUNC IDEN " << identifier << " function_signature LBRACE statementlist RBRACE " << std::endl;
                                (yyval.stm) = new Function_DeclarationStm((yyvsp[(3) - (6)].funcsig), (yyvsp[(5) - (6)].stmlist), identifier); 
                                thesyntree = (yyval.stm);;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 236 "test.ypp"
    {  
                                char* identifier = new char[std::strlen((yyvsp[(2) - (5)].id)) + 1];
                                std::strcpy(identifier, (yyvsp[(2) - (5)].id));
                                std::cout << "DECLARING FUNCTION " << identifier << " " << std::endl;                             

                                std::cout << "function_declaration_statement : FUNC IDEN " << identifier << " function_signature LBRACE statementlist RBRACE " << std::endl;
                                 
                                (yyval.stm) = new Function_DeclarationStm((yyvsp[(3) - (5)].funcsig), nullptr, identifier); 
                               
                                thesyntree = (yyval.stm);
                                ;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 249 "test.ypp"
    {
                  std::cout << "function_signature : LPAREN parameterlist RPAREN INT " << std::endl;
                  

                  (yyval.funcsig) = new Function_signature((yyvsp[(2) - (4)].paramlist), INT);
                  ;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 256 "test.ypp"
    {
                    std::cout << "function_signature : LPAREN parameterlist RPAREN BOOL " << std::endl;
                    (yyval.funcsig) = new Function_signature((yyvsp[(2) - (4)].paramlist), BOOL);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 259 "test.ypp"
    {
                    std::cout << "function_signature : LPAREN parameterlist RPAREN " << std::endl;
                    (yyval.funcsig) = new Function_signature((yyvsp[(2) - (3)].paramlist), -1);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 262 "test.ypp"
    {
                  std::cout << "function_signature : LPAREN RPAREN INT " << std::endl;
                  (yyval.funcsig) = new Function_signature(nullptr, INT);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 265 "test.ypp"
    {
                    std::cout << "function_signature : LPAREN RPAREN BOOL " << std::endl;
                    (yyval.funcsig) = new Function_signature(nullptr, BOOL);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 268 "test.ypp"
    {
                    std::cout << "function_signature : LPAREN RPAREN " << std::endl;
                    (yyval.funcsig) = new Function_signature(nullptr, -1);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 274 "test.ypp"
    {
                std::cout << "parameterlist : parameter_declaration " << std::endl;
                (yyval.paramlist) = new ParamList((yyvsp[(1) - (1)].paramdecl), nullptr);
                ;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 278 "test.ypp"
    {
                std::cout << "parameterlist : parameter_declaration " << std::endl;
                (yyval.paramlist) = new ParamList((yyvsp[(3) - (3)].paramdecl), (yyvsp[(1) - (3)].paramlist));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 283 "test.ypp"
    {
                                char* identifier = new char[std::strlen(yylval.id) + 1];
                                std::strcpy(identifier, yylval.id);
                                (yyval.paramdecl) = new Param_declaration(identifier, INT);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 287 "test.ypp"
    {  
                                char* identifier = new char[std::strlen(yylval.id) + 1];
                                std::strcpy(identifier, yylval.id);
                                (yyval.paramdecl) = new Param_declaration(identifier, BOOL);;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 294 "test.ypp"
    {
                          char* identifier = new char[std::strlen((yyvsp[(1) - (5)].id)) + 1];
                          std::strcpy(identifier, (yyvsp[(1) - (5)].id));
                          std::cout << "void_function_statement : IDEN " << identifier << " LPAREN expressionlist RPAREN SEMICOLON " << std::endl;

                          (yyval.stm) = new VoidFunctionStm((yyvsp[(3) - (5)].explist), identifier); thesyntree = (yyval.stm);;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 301 "test.ypp"
    {
                          char* identifier = new char[std::strlen(yylval.id) + 1];
                          std::strcpy(identifier, yylval.id);
                          std::cout << "void_function_statement : IDEN " << identifier << " LPAREN RPAREN SEMICOLON " << std::endl;
                          (yyval.stm) = new VoidFunctionStm(nullptr, identifier); thesyntree = (yyval.stm);;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 311 "test.ypp"
    {std::cout << "expressionlist COMMA expression  \n";
                                                 (yyval.explist) = new ExpList((yyvsp[(3) - (3)].exp), (yyvsp[(1) - (3)].explist));;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 313 "test.ypp"
    {std::cout << "expression  \n";
                            (yyval.explist) = new ExpList((yyvsp[(1) - (1)].exp), nullptr);;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 317 "test.ypp"
    {std::cout << "expression : INTLITERAL " << yylval.intlit << "\n";
                        (yyval.exp) = new IntlitExp(yylval.intlit);;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 319 "test.ypp"
    {std::cout << "expression : BOOLLITERAL " << yylval.boollit << "\n";
                         (yyval.exp) = new BoollitExp(yylval.boollit);;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 321 "test.ypp"
    {std::cout << "expression : IDEN " << yylval.id << "\n";
                  char* identifier = new char[std::strlen(yylval.id) + 1];
                  std::strcpy(identifier, yylval.id);
                  (yyval.exp) = new IdExp(identifier);
                  ;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 326 "test.ypp"
    {(yyval.exp) = new NotExp((yyvsp[(2) - (2)].exp)); std::cout << "expression: NOT expression";;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 327 "test.ypp"
    {std::cout << "LPAREN expression RPAREN  \n"; (yyval.exp) = (yyvsp[(2) - (3)].exp);;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 335 "test.ypp"
    {(yyval.exp) = new ArithmeticOpExp((yyvsp[(1) - (3)].exp), MUL, (yyvsp[(3) - (3)].exp)); std::cout << "arithmetic_op_expression : expression MUL expression" << std::endl;;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 336 "test.ypp"
    {(yyval.exp) = new ArithmeticOpExp((yyvsp[(1) - (3)].exp), DIV, (yyvsp[(3) - (3)].exp)); std::cout << "arithmetic_op_expression : expression DIV expression" << std::endl;;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 337 "test.ypp"
    {(yyval.exp) = new ArithmeticOpExp((yyvsp[(1) - (3)].exp), PLUS, (yyvsp[(3) - (3)].exp)); std::cout << "arithmetic_op_expression : expression PLUS expression" << std::endl;;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 338 "test.ypp"
    {(yyval.exp) = new ArithmeticOpExp((yyvsp[(1) - (3)].exp), MIN, (yyvsp[(3) - (3)].exp)); std::cout << "arithmetic_op_expression : expression MIN expression" << std::endl;;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 342 "test.ypp"
    {(yyval.exp) = new BooleanOpExp((yyvsp[(1) - (3)].exp), AND, (yyvsp[(3) - (3)].exp)); std::cout << "boolean_op_expression : expression AND expression" << std::endl;;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 343 "test.ypp"
    {(yyval.exp) = new BooleanOpExp((yyvsp[(1) - (3)].exp), OR, (yyvsp[(3) - (3)].exp)); std::cout << "boolean_op_expression : expression OR expression" << std::endl;;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 344 "test.ypp"
    {(yyval.exp) = new BooleanOpExp((yyvsp[(1) - (3)].exp), EQ, (yyvsp[(3) - (3)].exp)); std::cout << "boolean_op_expression : expression EQ expression" << std::endl;;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 345 "test.ypp"
    {(yyval.exp) = new BooleanOpExp((yyvsp[(1) - (3)].exp), NE, (yyvsp[(3) - (3)].exp)); std::cout << "boolean_op_expression : expression NE expression" << std::endl;;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 349 "test.ypp"
    {(yyval.exp) = new BooleanArithmeticOpExp((yyvsp[(1) - (3)].exp), GT, (yyvsp[(3) - (3)].exp)); std::cout << "boolean_arithmetic_op_expression : expression GT expression" << std::endl;;}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 350 "test.ypp"
    {(yyval.exp) = new BooleanArithmeticOpExp((yyvsp[(1) - (3)].exp), GE, (yyvsp[(3) - (3)].exp)); std::cout << "boolean_arithmetic_op_expression : expression GE expression" << std::endl;;}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 351 "test.ypp"
    {(yyval.exp) = new BooleanArithmeticOpExp((yyvsp[(1) - (3)].exp), LT, (yyvsp[(3) - (3)].exp)); std::cout << "boolean_arithmetic_op_expression : expression LT expression" << std::endl;;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 352 "test.ypp"
    {(yyval.exp) = new BooleanArithmeticOpExp((yyvsp[(1) - (3)].exp), LE, (yyvsp[(3) - (3)].exp)); std::cout << "boolean_arithmetic_op_expression : expression LE expression" << std::endl;;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 355 "test.ypp"
    {
                      char* identifier = new char[std::strlen((yyvsp[(1) - (4)].id)) + 1];
                      std::strcpy(identifier, (yyvsp[(1) - (4)].id));
                      std::cout << "function_expression : IDEN " << identifier << " LPAREN expressionlist RPAREN" << std::endl;
                      (yyval.exp) = new FunctionExp((yyvsp[(3) - (4)].explist), identifier);
                       
                    ;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 363 "test.ypp"
    {
                      char* identifier = new char[std::strlen((yyvsp[(1) - (3)].id)) + 1];
                      std::strcpy(identifier, (yyvsp[(1) - (3)].id));
                      std::cout << "function_expression : IDEN " << identifier << " LPAREN RPAREN" << std::endl;
                      (yyval.exp) = new FunctionExp(nullptr, identifier);
                    ;}
    break;



/* Line 1455 of yacc.c  */
#line 2085 "test.tab.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 376 "test.ypp"




int main(int argc, char* argv[]) {
    
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


    int tokenid;

    symbolhandler.pushSymbolTable(SymbolTable());

    yyin = fopen("./gotest.txt", "r");
 
    std::cout << "\n";
    std::cout << "Parsing instructions: " << "\n\n";
    yyparse();

    std::cout << "\n\nTypechecking AST:" << std::endl;
    thesyntree->typecheck();  

    std::cout << "\n\nInterpreting AST: \n";


    /* VoidFunctionStm main = VoidFunctionStm(nullptr, "main");
    main.interp();  */

    return 0;
}

void yyerror (char *s) {
    std::cerr << s << " " << yytext << std::endl;
}


/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IDENTIFIER = 258,
     CONSTANT = 259,
     INT = 260,
     VOID = 261,
     RETURN = 262
   };
#endif
/* Tokens.  */
#define IDENTIFIER 258
#define CONSTANT 259
#define INT 260
#define VOID 261
#define RETURN 262




/* Copy the first part of user declarations.  */
#line 1 "par.y"

#include "par.hpp"
#include <iostream>
int yylex (void);             
void yyerror (char const *);	


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 8 "par.y"
{
  std::string* RawStr;
  par::Decls* Decls;
  par::Exprs* Exprs;

  asg::TranslationUnit* TranslationUnit;
  asg::Type* Type;
  asg::Expr* Expr;
  asg::Decl* Decl;
  asg::FunctionDecl* FunctionDecl;
  asg::Stmt* Stmt;
  asg::CompoundStmt* CompoundStmt;
  asg::ExprStmt* ExprStmt;
  asg::ReturnStmt* ReturnStmt;
  asg::IfStmt* IfStmt;
  asg::WhileStmt* WhileStmt;
  asg::ContinueStmt* ContinueStmt;
  asg::BreakStmt* BreakStmt;
  asg::NullStmt* NullStmt;
}
/* Line 193 of yacc.c.  */
#line 138 "par.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 151 "par.tab.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   96

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  19
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  62
/* YYNRULES -- Number of states.  */
#define YYNSTATES  89

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   262

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      11,    12,     2,    17,    13,    18,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     8,
       2,    16,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     9,     2,    10,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    14,     2,    15,     2,     2,     2,     2,
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
       5,     6,     7
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     7,     9,    12,    14,    16,    17,
      22,    26,    28,    31,    33,    35,    37,    41,    46,    50,
      55,    57,    61,    64,    65,    68,    69,    74,    76,    79,
      81,    83,    85,    87,    89,    92,    95,    99,   101,   105,
     107,   111,   113,   115,   117,   119,   121,   125,   129,   131,
     133,   136,   138,   140,   142,   144,   148,   150,   154,   156,
     160,   163,   165
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      20,     0,    -1,    -1,    21,    22,    -1,    23,    -1,    22,
      23,    -1,    24,    -1,    26,    -1,    -1,    27,    29,    25,
      32,    -1,    27,    50,     8,    -1,    28,    -1,    28,    27,
      -1,     6,    -1,     5,    -1,     3,    -1,    29,     9,    10,
      -1,    29,     9,    40,    10,    -1,    29,    11,    12,    -1,
      29,    11,    30,    12,    -1,    31,    -1,    30,    13,    31,
      -1,    27,    29,    -1,    -1,    14,    15,    -1,    -1,    14,
      33,    34,    15,    -1,    35,    -1,    34,    35,    -1,    26,
      -1,    36,    -1,    32,    -1,    37,    -1,    38,    -1,    39,
       8,    -1,     7,     8,    -1,     7,    39,     8,    -1,    40,
      -1,    39,    13,    40,    -1,    41,    -1,    47,    16,    40,
      -1,    42,    -1,    43,    -1,    44,    -1,    45,    -1,    46,
      -1,    45,    17,    46,    -1,    45,    18,    46,    -1,    47,
      -1,    48,    -1,    18,    47,    -1,    49,    -1,     3,    -1,
       4,    -1,    51,    -1,    50,    13,    51,    -1,    29,    -1,
      29,    16,    52,    -1,    40,    -1,    14,    53,    15,    -1,
      14,    15,    -1,    52,    -1,    53,    13,    52,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    59,    59,    59,    70,    77,    87,    92,    97,    96,
     118,   139,   140,   148,   153,   161,   170,   192,   216,   229,
     250,   255,   263,   276,   277,   279,   278,   289,   294,   302,
     309,   313,   314,   315,   319,   327,   332,   340,   341,   351,
     352,   362,   366,   370,   374,   378,   379,   386,   396,   400,
     401,   411,   415,   425,   448,   453,   461,   462,   474,   491,
     495,   504,   508
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "CONSTANT", "INT", "VOID",
  "RETURN", "';'", "'['", "']'", "'('", "')'", "','", "'{'", "'}'", "'='",
  "'+'", "'-'", "$accept", "start", "@1", "translation_unit",
  "external_declaration", "function_definition", "@2", "declaration",
  "declaration_specifiers", "type_specifier", "declarator",
  "parameter_list", "parameter_declaration", "compound_statement", "@3",
  "block_item_list", "block_item", "statement", "expression_statement",
  "jump_statement", "expression", "assignment_expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "unary_expression", "postfix_expression",
  "primary_expression", "init_declarator_list", "init_declarator",
  "initializer", "initializer_list", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,    59,    91,
      93,    40,    41,    44,   123,   125,    61,    43,    45
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    19,    21,    20,    22,    22,    23,    23,    25,    24,
      26,    27,    27,    28,    28,    29,    29,    29,    29,    29,
      30,    30,    31,    32,    32,    33,    32,    34,    34,    35,
      35,    36,    36,    36,    37,    38,    38,    39,    39,    40,
      40,    41,    42,    43,    44,    45,    45,    45,    46,    47,
      47,    48,    49,    49,    50,    50,    51,    51,    52,    52,
      52,    53,    53
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     0,     4,
       3,     1,     2,     1,     1,     1,     3,     4,     3,     4,
       1,     3,     2,     0,     2,     0,     4,     1,     2,     1,
       1,     1,     1,     1,     2,     2,     3,     1,     3,     1,
       3,     1,     1,     1,     1,     1,     3,     3,     1,     1,
       2,     1,     1,     1,     1,     3,     1,     3,     1,     3,
       2,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,    14,    13,     3,     4,     6,     7,
       0,    11,     5,    15,     8,     0,    54,    12,     0,     0,
       0,    23,    10,     0,    52,    53,    16,     0,     0,    39,
      41,    42,    43,    44,    45,    48,    49,    51,    18,     0,
       0,    20,     0,    58,    57,    25,     9,    56,    55,    50,
      17,     0,     0,     0,    22,    19,     0,    60,    61,     0,
      24,    23,    46,    48,    47,    40,    21,     0,    59,     0,
      29,     0,    31,     0,    27,    30,    32,    33,     0,    37,
      62,    35,     0,    26,    28,    34,     0,    36,    38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     6,     7,     8,    21,     9,    10,    11,
      47,    40,    41,    72,    61,    73,    74,    75,    76,    77,
      78,    43,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    15,    16,    44,    59
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -44
static const yytype_int8 yypact[] =
{
     -44,    11,    78,   -44,   -44,   -44,    78,   -44,   -44,   -44,
      12,    78,   -44,   -44,    50,     6,   -44,   -44,    18,    64,
      30,    17,   -44,    12,   -44,   -44,   -44,    53,    27,   -44,
     -44,   -44,   -44,    68,   -44,    46,   -44,   -44,   -44,    12,
      75,   -44,     9,   -44,   -44,    39,   -44,    56,   -44,   -44,
     -44,    53,    53,    53,    71,   -44,    78,   -44,   -44,    62,
     -44,    35,   -44,   -44,   -44,   -44,   -44,    30,   -44,    42,
     -44,    12,   -44,     2,   -44,   -44,   -44,   -44,    65,   -44,
     -44,   -44,    66,   -44,   -44,   -44,    53,   -44,   -44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -44,   -44,   -44,   -44,    85,   -44,   -44,   -43,    -9,   -44,
      -7,   -44,    25,    72,   -44,   -44,    19,   -44,   -44,   -44,
      26,   -18,   -44,   -44,   -44,   -44,   -44,    38,   -26,   -44,
     -44,   -44,    73,   -38,   -44
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -57
static const yytype_int8 yytable[] =
{
      28,    49,    17,    14,    58,    24,    25,     4,     5,    69,
      39,     3,    24,    25,    22,    13,    45,    83,    70,    23,
      27,    24,    25,    42,    57,    63,    63,    27,    26,    80,
      70,    45,    54,    24,    25,    65,    27,    50,    24,    25,
       4,     5,    69,    79,    42,    24,    25,    39,    27,    45,
      81,    79,    71,    27,    60,    79,    24,    25,   -56,    18,
      27,    19,    53,   -56,    71,    18,    20,    19,    88,     4,
       5,    27,    20,    85,    87,    67,    38,    68,    86,    86,
      18,    66,    19,     4,     5,    51,    52,    55,    56,    62,
      64,    12,    84,    46,     0,    82,    48
};

static const yytype_int8 yycheck[] =
{
      18,    27,    11,    10,    42,     3,     4,     5,     6,     7,
      19,     0,     3,     4,     8,     3,    14,    15,    61,    13,
      18,     3,     4,    14,    15,    51,    52,    18,    10,    67,
      73,    14,    39,     3,     4,    53,    18,    10,     3,     4,
       5,     6,     7,    61,    14,     3,     4,    56,    18,    14,
       8,    69,    61,    18,    15,    73,     3,     4,     8,     9,
      18,    11,    16,    13,    73,     9,    16,    11,    86,     5,
       6,    18,    16,     8,     8,    13,    12,    15,    13,    13,
       9,    56,    11,     5,     6,    17,    18,    12,    13,    51,
      52,     6,    73,    21,    -1,    69,    23
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    20,    21,     0,     5,     6,    22,    23,    24,    26,
      27,    28,    23,     3,    29,    50,    51,    27,     9,    11,
      16,    25,     8,    13,     3,     4,    10,    18,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    12,    27,
      30,    31,    14,    40,    52,    14,    32,    29,    51,    47,
      10,    17,    18,    16,    29,    12,    13,    15,    52,    53,
      15,    33,    46,    47,    46,    40,    31,    13,    15,     7,
      26,    27,    32,    34,    35,    36,    37,    38,    39,    40,
      52,     8,    39,    15,    35,     8,    13,     8,    40
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 2:
#line 59 "par.y"
    {
      par::Symtbl::g = new par::Symtbl();
    ;}
    break;

  case 3:
#line 63 "par.y"
    {
      par::gTranslationUnit = (yyvsp[(2) - (2)].TranslationUnit);
      delete par::Symtbl::g;
    ;}
    break;

  case 4:
#line 71 "par.y"
    {
      (yyval.TranslationUnit) = par::gMgr.make<asg::TranslationUnit>();
      for (auto&& decl: *(yyvsp[(1) - (1)].Decls))
        (yyval.TranslationUnit)->decls.push_back(decl);
      delete (yyvsp[(1) - (1)].Decls);
    ;}
    break;

  case 5:
#line 78 "par.y"
    {
      (yyval.TranslationUnit) = (yyvsp[(1) - (2)].TranslationUnit);
      for (auto&& decl: *(yyvsp[(2) - (2)].Decls))
        (yyval.TranslationUnit)->decls.push_back(decl);
      delete (yyvsp[(2) - (2)].Decls);
    ;}
    break;

  case 6:
#line 88 "par.y"
    {
      (yyval.Decls) = new par::Decls();
      (yyval.Decls)->push_back((yyvsp[(1) - (1)].FunctionDecl));
    ;}
    break;

  case 7:
#line 92 "par.y"
    { (yyval.Decls) = (yyvsp[(1) - (1)].Decls); ;}
    break;

  case 8:
#line 97 "par.y"
    {
      auto funcDecl = (yyvsp[(2) - (2)].Decl)->dcst<asg::FunctionDecl>();
      ASSERT(funcDecl);
      // 设置当前全局的函数作用变量
      par::gCurrentFunction = funcDecl; 
      auto ty = par::gMgr.make<asg::Type>();
      if (funcDecl->type != nullptr)
        ty->texp = funcDecl->type->texp; 
      ty->spec = (yyvsp[(1) - (2)].Type)->spec, ty->qual = (yyvsp[(1) - (2)].Type)->qual;
      funcDecl->type = ty;

    ;}
    break;

  case 9:
#line 110 "par.y"
    {	
      (yyval.FunctionDecl) = par::gCurrentFunction;
      (yyval.FunctionDecl)->name = (yyvsp[(2) - (4)].Decl)->name;
      (yyval.FunctionDecl)->body = (yyvsp[(4) - (4)].CompoundStmt);
    ;}
    break;

  case 10:
#line 119 "par.y"
    {
      for (auto decl: *(yyvsp[(2) - (3)].Decls))
      {
        auto ty = par::gMgr.make<asg::Type>();
        if (decl->type != nullptr)
          ty->texp = decl->type->texp; // 保留前面 ArrayType 的texp
        ty->spec = (yyvsp[(1) - (3)].Type)->spec, ty->qual = (yyvsp[(1) - (3)].Type)->qual;
        decl->type = ty;
        auto varDecl = dynamic_cast<asg::VarDecl*>(decl);
        if (varDecl != nullptr)
        {
          if (varDecl->init != nullptr)
            varDecl->init->type = decl->type;
        }
      }
      (yyval.Decls) = (yyvsp[(2) - (3)].Decls);
    ;}
    break;

  case 11:
#line 139 "par.y"
    { (yyval.Type) = (yyvsp[(1) - (1)].Type); ;}
    break;

  case 12:
#line 141 "par.y"
    {
      (yyval.Type) = (yyvsp[(2) - (2)].Type);
      (yyval.Type)->spec = (yyvsp[(1) - (2)].Type)->spec;
    ;}
    break;

  case 13:
#line 149 "par.y"
    {
      (yyval.Type) = par::gMgr.make<asg::Type>();
      (yyval.Type)->spec = asg::Type::Spec::kVoid;
    ;}
    break;

  case 14:
#line 154 "par.y"
    {
      (yyval.Type) = par::gMgr.make<asg::Type>();
      (yyval.Type)->spec = asg::Type::Spec::kInt;
    ;}
    break;

  case 15:
#line 162 "par.y"
    {
      (yyval.Decl) = par::gMgr.make<asg::VarDecl>();
      (yyval.Decl)->name = std::move(*(yyvsp[(1) - (1)].RawStr));
      delete (yyvsp[(1) - (1)].RawStr);

      // 插入符号表
      par::Symtbl::g->insert_or_assign((yyval.Decl)->name, (yyval.Decl));
    ;}
    break;

  case 16:
#line 171 "par.y"
    {
      (yyval.Decl) = (yyvsp[(1) - (3)].Decl); 
      // 填充Type
      auto ty = par::gMgr.make<asg::Type>();
      if ((yyval.Decl)->type != nullptr)
        ty->texp=(yyval.Decl)->type->texp;
      auto p = par::gMgr.make<asg::ArrayType>();
      p->len = asg::ArrayType::kUnLen;
      if (ty->texp == nullptr)
      {
        ty->texp = p;
      }
      else
      {
        ty->texp->sub = p;
      }
      (yyval.Decl)->type = ty;

      // 插入符号表
      par::Symtbl::g->insert_or_assign((yyval.Decl)->name, (yyval.Decl));
    ;}
    break;

  case 17:
#line 193 "par.y"
    {
      (yyval.Decl) = (yyvsp[(1) - (4)].Decl); 
      // 填充Type
      auto ty = par::gMgr.make<asg::Type>();
      if ((yyval.Decl)->type != nullptr)
        ty->texp=(yyval.Decl)->type->texp;
      auto p = par::gMgr.make<asg::ArrayType>();
      auto integerLiteral = (yyvsp[(3) - (4)].Expr)->dcst<asg::IntegerLiteral>();
      ASSERT(integerLiteral);
      p->len = integerLiteral->val;
      if (ty->texp == nullptr)
      {
        ty->texp = p;
      }
      else
      {
        ty->texp->sub = p;
      }
      (yyval.Decl)->type = ty;

      // 插入符号表
      par::Symtbl::g->insert_or_assign((yyval.Decl)->name, (yyval.Decl));
    ;}
    break;

  case 18:
#line 217 "par.y"
    {
      (yyval.Decl) = par::gMgr.make<asg::FunctionDecl>();
      (yyval.Decl)->name = (yyvsp[(1) - (3)].Decl)->name;
      auto ty = par::gMgr.make<asg::Type>();
      auto p = par::gMgr.make<asg::FunctionType>();
      ty->texp = p;
      (yyval.Decl)->type = ty;

      // 插入符号表
      par::Symtbl::g->insert_or_assign((yyval.Decl)->name, (yyval.Decl));
    ;}
    break;

  case 19:
#line 230 "par.y"
    {
      auto p = par::gMgr.make<asg::FunctionDecl>();
      p->name = (yyvsp[(1) - (4)].Decl)->name;
      p->params = *(yyvsp[(3) - (4)].Decls);
      auto ty = par::gMgr.make<asg::Type>();
      auto functionType = par::gMgr.make<asg::FunctionType>();
      for (auto decl: *(yyvsp[(3) - (4)].Decls))
      {
        functionType->params.push_back(decl->type);
      }
      ty->texp = functionType;
      p->type = ty;
      (yyval.Decl) = p;

      // 插入符号表
      par::Symtbl::g->insert_or_assign((yyval.Decl)->name, (yyval.Decl));
    ;}
    break;

  case 20:
#line 251 "par.y"
    {
      (yyval.Decls) = new par::Decls();
      (yyval.Decls)->push_back((yyvsp[(1) - (1)].Decl));
    ;}
    break;

  case 21:
#line 256 "par.y"
    {
      (yyval.Decls) = (yyvsp[(1) - (3)].Decls);
      (yyval.Decls)->push_back((yyvsp[(3) - (3)].Decl));
    ;}
    break;

  case 22:
#line 264 "par.y"
    {
      // 保留之前定义的 Type
      auto ty = par::gMgr.make<asg::Type>();
      if ((yyvsp[(2) - (2)].Decl)->type != nullptr)
        ty->texp = (yyvsp[(2) - (2)].Decl)->type->texp;
      ty->spec = (yyvsp[(1) - (2)].Type)->spec, ty->qual = (yyvsp[(1) - (2)].Type)->qual;
      (yyvsp[(2) - (2)].Decl)->type = ty;
      (yyval.Decl) = (yyvsp[(2) - (2)].Decl);
    ;}
    break;

  case 23:
#line 276 "par.y"
    {(yyval.CompoundStmt) = par::gMgr.make<asg::CompoundStmt>();;}
    break;

  case 24:
#line 277 "par.y"
    { (yyval.CompoundStmt) = par::gMgr.make<asg::CompoundStmt>(); ;}
    break;

  case 25:
#line 279 "par.y"
    { new par::Symtbl(); ;}
    break;

  case 26:
#line 282 "par.y"
    {
      delete par::Symtbl::g; 	// 结束符号表作用域
      (yyval.CompoundStmt) = $block_item_list;
    ;}
    break;

  case 27:
#line 290 "par.y"
    {
      (yyval.CompoundStmt) = par::gMgr.make<asg::CompoundStmt>();
      (yyval.CompoundStmt)->subs.push_back((yyvsp[(1) - (1)].Stmt));
    ;}
    break;

  case 28:
#line 295 "par.y"
    {
      (yyval.CompoundStmt) = (yyvsp[(1) - (2)].CompoundStmt);
      (yyval.CompoundStmt)->subs.push_back((yyvsp[(2) - (2)].Stmt));
    ;}
    break;

  case 29:
#line 303 "par.y"
    {
      auto p = par::gMgr.make<asg::DeclStmt>();
      for (auto decl: *(yyvsp[(1) - (1)].Decls))
        p->decls.push_back(decl);
      (yyval.Stmt) = p;
    ;}
    break;

  case 30:
#line 309 "par.y"
    { (yyval.Stmt) = (yyvsp[(1) - (1)].Stmt); ;}
    break;

  case 31:
#line 313 "par.y"
    { (yyval.Stmt) = (yyvsp[(1) - (1)].CompoundStmt); ;}
    break;

  case 32:
#line 314 "par.y"
    { (yyval.Stmt) = (yyvsp[(1) - (1)].ExprStmt); ;}
    break;

  case 33:
#line 315 "par.y"
    { (yyval.Stmt) = (yyvsp[(1) - (1)].ReturnStmt); ;}
    break;

  case 34:
#line 320 "par.y"
    {
      (yyval.ExprStmt) = par::gMgr.make<asg::ExprStmt>();
      (yyval.ExprStmt)->expr = (yyvsp[(1) - (2)].Expr);
    ;}
    break;

  case 35:
#line 328 "par.y"
    {
      (yyval.ReturnStmt) = par::gMgr.make<asg::ReturnStmt>();
      (yyval.ReturnStmt)->func = par::gCurrentFunction;
    ;}
    break;

  case 36:
#line 333 "par.y"
    {
      (yyval.ReturnStmt) = par::gMgr.make<asg::ReturnStmt>();
      (yyval.ReturnStmt)->func = par::gCurrentFunction;
      (yyval.ReturnStmt)->expr = (yyvsp[(2) - (3)].Expr);
    ;}
    break;

  case 37:
#line 340 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr); ;}
    break;

  case 38:
#line 342 "par.y"
    {
      auto p = par::gMgr.make<asg::BinaryExpr>();
      p->op = asg::BinaryExpr::Op::kComma;
      p->lft = (yyvsp[(1) - (3)].Expr), p->rht = (yyvsp[(3) - (3)].Expr);
      (yyval.Expr) = p;
    ;}
    break;

  case 39:
#line 351 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr); ;}
    break;

  case 40:
#line 353 "par.y"
    {
      auto p = par::gMgr.make<asg::BinaryExpr>();
      p->op = asg::BinaryExpr::Op::kAssign;;
      p->lft = (yyvsp[(1) - (3)].Expr), p->rht = (yyvsp[(3) - (3)].Expr);
      (yyval.Expr) = p;
    ;}
    break;

  case 41:
#line 362 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr); ;}
    break;

  case 42:
#line 366 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr); ;}
    break;

  case 43:
#line 370 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr); ;}
    break;

  case 44:
#line 374 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr); ;}
    break;

  case 45:
#line 378 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr);;}
    break;

  case 46:
#line 380 "par.y"
    {
      auto p = par::gMgr.make<asg::BinaryExpr>();
      p->op = asg::BinaryExpr::Op::kAdd;
      p->lft = (yyvsp[(1) - (3)].Expr), p->rht = (yyvsp[(3) - (3)].Expr);
      (yyval.Expr) = p;
    ;}
    break;

  case 47:
#line 387 "par.y"
    {
      auto p = par::gMgr.make<asg::BinaryExpr>();
      p->op = asg::BinaryExpr::Op::kSub;
      p->lft = (yyvsp[(1) - (3)].Expr), p->rht = (yyvsp[(3) - (3)].Expr);
      (yyval.Expr) = p;
    ;}
    break;

  case 48:
#line 396 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr);;}
    break;

  case 49:
#line 400 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr);;}
    break;

  case 50:
#line 402 "par.y"
    {
      auto p = par::gMgr.make<asg::UnaryExpr>();
      p->op = asg::UnaryExpr::Op::kNeg;
      p->sub = (yyvsp[(2) - (2)].Expr);
      (yyval.Expr) = p;
    ;}
    break;

  case 51:
#line 411 "par.y"
    { (yyval.Expr) = (yyvsp[(1) - (1)].Expr); ;}
    break;

  case 52:
#line 416 "par.y"
    {
      // 查找符号表, 找到对应的Decl
      auto decl = par::Symtbl::resolve(*(yyvsp[(1) - (1)].RawStr));
      ASSERT(decl);
      delete (yyvsp[(1) - (1)].RawStr);
      auto p = par::gMgr.make<asg::DeclRefExpr>();
      p->decl = decl;
      (yyval.Expr) = p;
    ;}
    break;

  case 53:
#line 426 "par.y"
    {
      auto p = par::gMgr.make<asg::IntegerLiteral>();
      p->val = std::stoull(*(yyvsp[(1) - (1)].RawStr), nullptr, 10);
      delete (yyvsp[(1) - (1)].RawStr);
      (yyval.Expr) = p;
    ;}
    break;

  case 54:
#line 449 "par.y"
    {
      (yyval.Decls) = new par::Decls();
      (yyval.Decls)->push_back((yyvsp[(1) - (1)].Decl));
    ;}
    break;

  case 55:
#line 454 "par.y"
    {
      (yyval.Decls) = (yyvsp[(1) - (3)].Decls);
      (yyval.Decls)->push_back((yyvsp[(3) - (3)].Decl));
    ;}
    break;

  case 56:
#line 461 "par.y"
    { (yyval.Decl) = (yyvsp[(1) - (1)].Decl); ;}
    break;

  case 57:
#line 463 "par.y"
    {
      auto varDecl = (yyvsp[(1) - (3)].Decl)->dcst<asg::VarDecl>();
      ASSERT(varDecl);
      (yyvsp[(3) - (3)].Expr)->type = varDecl->type;
      varDecl->init = (yyvsp[(3) - (3)].Expr);
      (yyval.Decl) = varDecl;
    ;}
    break;

  case 58:
#line 475 "par.y"
    {
      auto callExpr = (yyvsp[(1) - (1)].Expr)->dcst<asg::CallExpr>();
      if (callExpr != nullptr)
      {
        auto implicitCastExpr = dynamic_cast<asg::ImplicitCastExpr*>(callExpr->head);
        auto declRefExpr = dynamic_cast<asg::DeclRefExpr*>(implicitCastExpr->sub);
        (yyval.Expr) = callExpr;
      }
      else
      {
        auto p = par::gMgr.make<asg::InitListExpr>();
        p->list.push_back((yyvsp[(1) - (1)].Expr));
        (yyval.Expr) = p;
      }
      (yyval.Expr)->type = (yyvsp[(1) - (1)].Expr)->type;
    ;}
    break;

  case 59:
#line 492 "par.y"
    {
      (yyval.Expr) = (yyvsp[(2) - (3)].Expr);
    ;}
    break;

  case 60:
#line 496 "par.y"
    {
      auto p = par::gMgr.make<asg::InitListExpr>();
      (yyval.Expr) = p;
    ;}
    break;

  case 61:
#line 505 "par.y"
    {
      (yyval.Expr) = (yyvsp[(1) - (1)].Expr);
    ;}
    break;

  case 62:
#line 509 "par.y"
    {
      auto initListExpr3 = (yyvsp[(3) - (3)].Expr)->dcst<asg::InitListExpr>();
      auto initListExpr1 = (yyvsp[(1) - (3)].Expr)->dcst<asg::InitListExpr>();
      for(auto exper: initListExpr3->list)
        initListExpr1->list.push_back(exper);
      (yyval.Expr) = initListExpr1;
    ;}
    break;


/* Line 1267 of yacc.c.  */
#line 1985 "par.tab.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 518 "par.y"



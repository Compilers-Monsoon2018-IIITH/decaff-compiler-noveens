/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */


#include <stdio.h>
#include "class_definition.h"
int fl = 0;
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern "C" int line_num;
extern union Node yylval;
extern "C" int errors;
void yyerror(const char *s);
class Prog* start = NULL;
int errors=0;


#line 83 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PROG = 258,
    CLASS = 259,
    LEFT_CURLY = 260,
    RIGHT_CURLY = 261,
    LEFT_SQUARE = 262,
    RIGHT_SQUARE = 263,
    LEFT_ROUND = 264,
    RIGHT_ROUND = 265,
    VOID = 266,
    INT = 267,
    BOOL = 268,
    IF = 269,
    ELSE = 270,
    FOR = 271,
    RET = 272,
    BREAK = 273,
    CONT = 274,
    NOT = 275,
    PLUS = 276,
    MINUS = 277,
    MUL = 278,
    DIV = 279,
    MOD = 280,
    EQ = 281,
    MINEQ = 282,
    PLUSEQ = 283,
    CALLOUT = 284,
    GT = 285,
    LT = 286,
    GE = 287,
    LE = 288,
    EQEQ = 289,
    NEQ = 290,
    ANDAND = 291,
    OROR = 292,
    ALPHA = 293,
    DIGIT = 294,
    TRUE = 295,
    FALSE = 296,
    SQUOT = 297,
    DQUOT = 298,
    COMMA = 299,
    SEMICOLON = 300,
    CHAR = 301,
    UNDERSCORE = 302,
    REGEX_HEX = 303,
    REGEX_ID = 304,
    REGEX_DECIMAL = 305,
    REGEX_CHAR = 306,
    REGEX_STRING = 307
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 182 "parser.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   280

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  150

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   110,   111,   114,   115,   118,   119,   120,
     123,   124,   127,   128,   129,   130,   133,   134,   137,   140,
     141,   144,   145,   148,   149,   152,   153,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   169,   170,
     171,   174,   175,   178,   179,   182,   183,   186,   187,   190,
     193,   194,   197,   198,   199,   200,   201,   202,   203,   204,
     207,   208,   211,   212,   213,   214,   217,   218,   219,   220,
     221,   224,   225,   226,   227,   230,   231,   234,   235,   238,
     239,   240,   243,   246,   247,   250,   251,   254,   257
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "PROG", "CLASS", "LEFT_CURLY",
  "RIGHT_CURLY", "LEFT_SQUARE", "RIGHT_SQUARE", "LEFT_ROUND",
  "RIGHT_ROUND", "VOID", "INT", "BOOL", "IF", "ELSE", "FOR", "RET",
  "BREAK", "CONT", "NOT", "PLUS", "MINUS", "MUL", "DIV", "MOD", "EQ",
  "MINEQ", "PLUSEQ", "CALLOUT", "GT", "LT", "GE", "LE", "EQEQ", "NEQ",
  "ANDAND", "OROR", "ALPHA", "DIGIT", "TRUE", "FALSE", "SQUOT", "DQUOT",
  "COMMA", "SEMICOLON", "CHAR", "UNDERSCORE", "REGEX_HEX", "REGEX_ID",
  "REGEX_DECIMAL", "REGEX_CHAR", "REGEX_STRING", "$accept", "program",
  "field_decl", "field_decls", "follow", "method_decl", "method_decls",
  "param", "block", "multi_var_decl", "multi_id", "multi_statement",
  "type", "statement", "assign_op", "method_call", "callout_call",
  "multi_expr", "multi_callout_arg", "method_name", "location", "expr",
  "callout_arg", "bin_op", "arith_op", "rel_op", "eq_op", "cond_op",
  "literal", "id", "int_literal", "bool_literal", "char_literal",
  "string_literal", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

#define YYPACT_NINF -66

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-66)))

#define YYTABLE_NINF -50

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,     6,    19,    32,   -66,   -66,    54,   -66,   -66,   -66,
      71,   -66,   -66,   -20,   -66,   -20,   -20,   -66,    36,    38,
      -1,    45,    50,   -33,   -66,   -66,    69,    54,    69,    54,
     -66,   -66,    87,   -66,   -66,   -20,   -66,   -20,    49,    54,
      -3,     4,   -66,   -66,     7,   -66,    69,   -66,    69,   -66,
      88,   -20,    30,    57,    58,    95,   -66,   -66,    60,    61,
     101,    64,    31,   -20,   -66,   -66,    67,    85,    67,    67,
      67,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   192,   -66,
     -66,   -66,   -66,   -66,   -66,    73,   -66,   -66,   102,   -66,
     -66,   -66,    67,    67,    56,   158,    67,   175,   243,   243,
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,    67,   -66,   -66,   -66,   -66,   -66,
      24,   -66,    67,   209,   141,   -66,   -66,    69,   226,   -66,
     243,   -66,   -66,    99,   -66,   -66,   104,    67,    13,   -66,
     -66,    69,   123,   243,    41,   -66,   -66,   -66,   -66,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     1,     3,    10,    25,    26,     4,
       0,     7,     2,     0,    11,     0,     0,    82,     0,     0,
       0,    16,    16,     0,     8,     5,     0,     0,     0,     0,
      84,    83,     0,    19,    14,     0,    12,     0,     0,    23,
       0,     0,     9,     6,     0,    21,     0,    17,     0,    18,
       0,     0,     0,     0,     0,     0,    37,    24,     0,     0,
       0,     0,    50,     0,    15,    13,     0,     0,     0,     0,
       0,    85,    86,    34,    87,    53,    54,    52,     0,    55,
      79,    81,    80,    35,    36,     0,    28,    29,    45,    38,
      39,    40,     0,     0,     0,     0,     0,     0,    58,    57,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    33,     0,    62,    63,    64,    65,    88,
       0,    41,     0,     0,     0,    22,    20,     0,     0,    59,
      56,    43,    47,     0,    27,    51,    31,     0,     0,    42,
      46,     0,     0,    60,     0,    61,    30,    32,    44,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   105,   -28,   -66,
     -66,   -66,    59,   -66,   -66,    82,    93,   -66,   -66,   -66,
      94,   -65,   -66,   -66,   -66,   -66,   -66,   -66,   -66,    -5,
     116,   -66,   -66,     2
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     6,     9,    16,    10,    14,    27,    34,    39,
      63,    44,    11,    57,    92,    75,    76,   122,   138,    60,
      77,    78,   144,   114,   115,   116,   117,   118,    79,    62,
      80,    81,    82,   120
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      36,    95,     1,    97,    98,    99,    23,    46,    18,     3,
      19,    20,    33,    49,    48,    30,    56,    31,    64,     4,
      65,    50,    68,    51,    52,    53,    54,   123,   124,    17,
      40,   128,    41,    69,   131,    70,    55,     5,    93,    68,
     -49,    47,    55,    24,    25,    21,    67,    22,    47,   130,
      69,   148,    70,    71,    72,    26,    17,   133,    94,    55,
      28,    30,    17,    31,    74,   119,     7,     8,   132,    15,
      71,    72,   142,   143,    33,    73,    68,    12,    30,    17,
      31,    74,    13,     7,     8,   149,    35,    69,    37,    70,
      89,    90,    91,    42,    43,    38,    55,    66,    45,   136,
     125,   126,    83,    84,    85,    86,    87,    71,    72,   139,
      88,    96,   121,   146,   147,    30,    17,    31,    74,   141,
     100,   101,   102,   103,   104,   119,    58,    29,    33,   105,
     106,   107,   108,   109,   110,   111,   112,    59,    61,    32,
     145,     0,     0,   140,   100,   101,   102,   103,   104,   135,
       0,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112,     0,   100,   101,   102,   103,   104,     0,   127,     0,
       0,   105,   106,   107,   108,   109,   110,   111,   112,   100,
     101,   102,   103,   104,     0,   129,     0,     0,   105,   106,
     107,   108,   109,   110,   111,   112,   100,   101,   102,   103,
     104,     0,     0,     0,     0,   105,   106,   107,   108,   109,
     110,   111,   112,   100,   101,   102,   103,   104,     0,     0,
       0,     0,   105,   106,   107,   108,   109,   110,   111,   112,
     100,   101,   102,   103,   104,     0,     0,   113,     0,   105,
     106,   107,   108,   109,   110,   111,   112,   100,   101,   102,
     103,   104,     0,     0,   134,     0,   105,   106,   107,   108,
     109,   110,   111,   112,   100,   101,   102,   103,   104,     0,
     137,     0,     0,   105,   106,   107,   108,   109,   110,   111,
     112
};

static const yytype_int16 yycheck[] =
{
      28,    66,     4,    68,    69,    70,     7,    10,    13,     3,
      15,    16,     5,     6,    10,    48,    44,    50,    46,     0,
      48,    14,     9,    16,    17,    18,    19,    92,    93,    49,
      35,    96,    37,    20,    10,    22,    29,     5,     7,     9,
       9,    44,    29,    44,    45,     9,    51,     9,    44,   114,
      20,    10,    22,    40,    41,    10,    49,   122,    63,    29,
      10,    48,    49,    50,    51,    52,    12,    13,    44,    10,
      40,    41,   137,   138,     5,    45,     9,     6,    48,    49,
      50,    51,    11,    12,    13,    44,    27,    20,    29,    22,
      26,    27,    28,    44,    45,     8,    29,     9,    39,   127,
      44,    45,    45,    45,     9,    45,    45,    40,    41,    10,
       9,    26,    10,   141,   142,    48,    49,    50,    51,    15,
      21,    22,    23,    24,    25,    52,    44,    22,     5,    30,
      31,    32,    33,    34,    35,    36,    37,    44,    44,    23,
     138,    -1,    -1,    44,    21,    22,    23,    24,    25,     8,
      -1,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37,    -1,    21,    22,    23,    24,    25,    -1,    10,    -1,
      -1,    30,    31,    32,    33,    34,    35,    36,    37,    21,
      22,    23,    24,    25,    -1,    10,    -1,    -1,    30,    31,
      32,    33,    34,    35,    36,    37,    21,    22,    23,    24,
      25,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    34,
      35,    36,    37,    21,    22,    23,    24,    25,    -1,    -1,
      -1,    -1,    30,    31,    32,    33,    34,    35,    36,    37,
      21,    22,    23,    24,    25,    -1,    -1,    45,    -1,    30,
      31,    32,    33,    34,    35,    36,    37,    21,    22,    23,
      24,    25,    -1,    -1,    45,    -1,    30,    31,    32,    33,
      34,    35,    36,    37,    21,    22,    23,    24,    25,    -1,
      44,    -1,    -1,    30,    31,    32,    33,    34,    35,    36,
      37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     4,    54,     3,     0,     5,    55,    12,    13,    56,
      58,    65,     6,    11,    59,    65,    57,    49,    82,    82,
      82,     9,     9,     7,    44,    45,    10,    60,    10,    60,
      48,    50,    83,     5,    61,    65,    61,    65,     8,    62,
      82,    82,    44,    45,    64,    65,    10,    44,    10,     6,
      14,    16,    17,    18,    19,    29,    61,    66,    68,    69,
      72,    73,    82,    63,    61,    61,     9,    82,     9,    20,
      22,    40,    41,    45,    51,    68,    69,    73,    74,    81,
      83,    84,    85,    45,    45,     9,    45,    45,     9,    26,
      27,    28,    67,     7,    82,    74,    26,    74,    74,    74,
      21,    22,    23,    24,    25,    30,    31,    32,    33,    34,
      35,    36,    37,    45,    76,    77,    78,    79,    80,    52,
      86,    10,    70,    74,    74,    44,    45,    10,    74,    10,
      74,    10,    44,    74,    45,     8,    61,    44,    71,    10,
      44,    15,    74,    74,    75,    86,    61,    61,    10,    44
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    57,    57,
      58,    58,    59,    59,    59,    59,    60,    60,    61,    62,
      62,    63,    63,    64,    64,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    67,    67,
      67,    68,    68,    69,    69,    70,    70,    71,    71,    72,
      73,    73,    74,    74,    74,    74,    74,    74,    74,    74,
      75,    75,    76,    76,    76,    76,    77,    77,    77,    77,
      77,    78,    78,    78,    78,    79,    79,    80,    80,    81,
      81,    81,    82,    83,    83,    84,    84,    85,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     0,     2,     4,     7,     0,     3,     6,
       0,     2,     5,     8,     5,     8,     0,     4,     4,     0,
       5,     0,     3,     0,     2,     1,     1,     4,     2,     2,
       7,     5,     7,     3,     2,     2,     2,     1,     1,     1,
       1,     3,     5,     4,     7,     0,     3,     0,     3,     1,
       1,     4,     1,     1,     1,     1,     3,     2,     2,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 107 "parser.y" /* yacc.c:1646  */
    { (yyval.Programs) = new Program((yyvsp[-2].FieldDeclLists), (yyvsp[-1].MethodDeclLists)); }
#line 1398 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 110 "parser.y" /* yacc.c:1646  */
    { (yyval.FieldDeclLists) = new FieldDeclList(); }
#line 1404 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 111 "parser.y" /* yacc.c:1646  */
    { (yyval.FieldDeclLists)->push_back((yyvsp[0].VariableLists)); }
#line 1410 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 114 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].VariableLists)->push_back((yyvsp[-1].TerminalVariables)); (yyvsp[-2].VariableLists)->set_type((yyvsp[-3].lit)); (yyval.VariableLists) = (yyvsp[-2].VariableLists); }
#line 1416 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 115 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-5].VariableLists)->push_back(new ArrayTerminalVariable((yyvsp[-4].TerminalVariables), (yyvsp[-2].num))); (yyvsp[-5].VariableLists)->set_type((yyvsp[-6].lit)); (yyval.VariableLists) = (yyvsp[-5].VariableLists); }
#line 1422 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 118 "parser.y" /* yacc.c:1646  */
    { (yyval.VariableLists) = new VariableList(); }
#line 1428 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 119 "parser.y" /* yacc.c:1646  */
    { (yyval.VariableLists)->push_back((yyvsp[-1].TerminalVariables)); }
#line 1434 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 120 "parser.y" /* yacc.c:1646  */
    { (yyval.VariableLists)->push_back(new ArrayTerminalVariable((yyvsp[-4].TerminalVariables), int((yyvsp[-2].num)))); }
#line 1440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 123 "parser.y" /* yacc.c:1646  */
    { (yyval.MethodDeclLists) = new MethodDeclList(); }
#line 1446 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 124 "parser.y" /* yacc.c:1646  */
    { (yyval.MethodDeclLists)->push_back((yyvsp[0].MethodDecls)); }
#line 1452 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "parser.y" /* yacc.c:1646  */
    { (yyval.MethodDecls) = new MethodDecl(string((yyvsp[-4].lit)), (yyvsp[-3].TerminalVariables), (yyvsp[0].Blocks)); }
#line 1458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 128 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-4].ParamLists)->push_back((yyvsp[-3].lit), (yyvsp[-2].TerminalVariables)); (yyval.MethodDecls) = new MethodDecl(string((yyvsp[-7].lit)), (yyvsp[-6].TerminalVariables), (yyvsp[-4].ParamLists), (yyvsp[0].Blocks)); }
#line 1464 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 129 "parser.y" /* yacc.c:1646  */
    { (yyval.MethodDecls) = new MethodDecl(string((yyvsp[-4].lit)), (yyvsp[-3].TerminalVariables), (yyvsp[0].Blocks)); }
#line 1470 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 130 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-4].ParamLists)->push_back((yyvsp[-3].lit), (yyvsp[-2].TerminalVariables)); (yyval.MethodDecls) = new MethodDecl(string((yyvsp[-7].lit)), (yyvsp[-6].TerminalVariables), (yyvsp[-4].ParamLists), (yyvsp[0].Blocks)); }
#line 1476 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 133 "parser.y" /* yacc.c:1646  */
    { (yyval.ParamLists) = new ParamList(); }
#line 1482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 134 "parser.y" /* yacc.c:1646  */
    { (yyval.ParamLists)->push_back((yyvsp[-2].lit), (yyvsp[-1].TerminalVariables)); }
#line 1488 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 137 "parser.y" /* yacc.c:1646  */
    { (yyval.Blocks) = new Block((yyvsp[-2].FieldDeclLists), (yyvsp[-1].StatementLists)); }
#line 1494 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 140 "parser.y" /* yacc.c:1646  */
    { (yyval.FieldDeclLists) = new FieldDeclList(); }
#line 1500 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 141 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].VariableLists)->push_back((yyvsp[-1].TerminalVariables)); (yyvsp[-2].VariableLists)->set_type((yyvsp[-3].lit)); (yyval.FieldDeclLists)->push_back((yyvsp[-2].VariableLists)); }
#line 1506 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 144 "parser.y" /* yacc.c:1646  */
    { (yyval.VariableLists) = new VariableList(); }
#line 1512 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 145 "parser.y" /* yacc.c:1646  */
    { (yyval.VariableLists)->push_back((yyvsp[-1].TerminalVariables)); }
#line 1518 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyval.StatementLists) = new StatementList(); }
#line 1524 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 149 "parser.y" /* yacc.c:1646  */
    { (yyval.StatementLists)->push_back((yyvsp[0].Statements)); }
#line 1530 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 152 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1536 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 153 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1542 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 156 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = new AssignStmt((yyvsp[-3].Locations), (yyvsp[-2].lit), (yyvsp[-1].Exprs)); }
#line 1548 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = (yyvsp[-1].MethodCalls); }
#line 1554 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 158 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = (yyvsp[-1].CalloutCalls); }
#line 1560 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 159 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = new IfElseStmt((yyvsp[-4].Exprs), (yyvsp[-2].Blocks), (yyvsp[0].Blocks)); }
#line 1566 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 160 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = new IfStmt((yyvsp[-2].Exprs), (yyvsp[0].Blocks)); }
#line 1572 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 161 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = new ForStmt((yyvsp[-5].TerminalVariables), (yyvsp[-3].Exprs), (yyvsp[-1].Exprs), (yyvsp[0].Blocks)); }
#line 1578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 162 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = new RetExpr((yyvsp[-1].Exprs)); }
#line 1584 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = new StringRetBrkContStatement((yyvsp[-1].lit)); }
#line 1590 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 164 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = new StringRetBrkContStatement((yyvsp[-1].lit)); }
#line 1596 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 165 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = new StringRetBrkContStatement((yyvsp[-1].lit)); }
#line 1602 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 166 "parser.y" /* yacc.c:1646  */
    { (yyval.Statements) = (yyvsp[0].Blocks); }
#line 1608 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1614 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 170 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1620 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 171 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1626 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 174 "parser.y" /* yacc.c:1646  */
    { (yyval.MethodCalls) = new MethodCall(); }
#line 1632 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].MethodArgInpLists)->push_back((yyvsp[-1].Exprs)); (yyval.MethodCalls) = new MethodCall((yyvsp[-2].MethodArgInpLists)); }
#line 1638 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval.CalloutCalls) = new CalloutCall((yyvsp[-1].lit)); }
#line 1644 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 179 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].CalloutArgLists)->push_back((yyvsp[-1].CalloutArgs)); (yyval.CalloutCalls) = new CalloutCall((yyvsp[-4].lit), (yyvsp[-2].CalloutArgLists)); }
#line 1650 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval.MethodArgInpLists) = new MethodArgInpList(); }
#line 1656 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 183 "parser.y" /* yacc.c:1646  */
    { (yyval.MethodArgInpLists)->push_back((yyvsp[-1].Exprs)); }
#line 1662 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval.CalloutArgLists) = new CalloutArgList(); }
#line 1668 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 187 "parser.y" /* yacc.c:1646  */
    { (yyval.CalloutArgLists)->push_back((yyvsp[-1].CalloutArgs)); }
#line 1674 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval.TerminalVariables) = (yyvsp[0].TerminalVariables); }
#line 1680 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 193 "parser.y" /* yacc.c:1646  */
    { (yyval.Locations) = new Location((yyvsp[0].TerminalVariables)); }
#line 1686 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 194 "parser.y" /* yacc.c:1646  */
    { (yyval.Locations) = new Location((yyvsp[-3].TerminalVariables), (yyvsp[-1].Exprs)); }
#line 1692 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 197 "parser.y" /* yacc.c:1646  */
    { (yyval.Exprs) = (yyvsp[0].Locations); }
#line 1698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 198 "parser.y" /* yacc.c:1646  */
    { (yyval.Exprs) = (yyvsp[0].MethodCalls); }
#line 1704 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 199 "parser.y" /* yacc.c:1646  */
    { (yyval.Exprs) = (yyvsp[0].CalloutCalls); }
#line 1710 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 200 "parser.y" /* yacc.c:1646  */
    { (yyval.Exprs) = new ExprIntCharBool((yyvsp[0].Literals)); }
#line 1716 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 201 "parser.y" /* yacc.c:1646  */
    { (yyval.Exprs) = new BinaryOpExpression((yyvsp[-2].Exprs), (yyvsp[-1].lit), (yyvsp[0].Exprs)); }
#line 1722 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 202 "parser.y" /* yacc.c:1646  */
    { (yyval.Exprs) = new UnaryOpExpression((yyvsp[-1].lit), (yyvsp[0].Exprs)); }
#line 1728 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 203 "parser.y" /* yacc.c:1646  */
    { (yyval.Exprs) = new UnaryOpExpression((yyvsp[-1].lit), (yyvsp[0].Exprs)); }
#line 1734 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 204 "parser.y" /* yacc.c:1646  */
    { (yyval.Exprs) = (yyvsp[-1].Exprs); }
#line 1740 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 207 "parser.y" /* yacc.c:1646  */
    { (yyval.CalloutArgs) = new CalloutArg((yyvsp[0].Exprs)); }
#line 1746 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 208 "parser.y" /* yacc.c:1646  */
    { (yyval.CalloutArgs) = new CalloutArg((yyvsp[0].lit)); }
#line 1752 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 211 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1758 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 212 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1764 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 213 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1770 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 214 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1776 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 217 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 218 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1788 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 219 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1794 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 220 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1800 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 221 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1806 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 224 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1812 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 225 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1818 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 226 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1824 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 227 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1830 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 230 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1836 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 231 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1842 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 234 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1848 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 235 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1854 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 238 "parser.y" /* yacc.c:1646  */
    { (yyval.Literals) = new Literal(int((yyvsp[0].num))); }
#line 1860 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 239 "parser.y" /* yacc.c:1646  */
    { (yyval.Literals) = new Literal(char((yyvsp[0].char_lit))); }
#line 1866 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 240 "parser.y" /* yacc.c:1646  */
    { (yyval.Literals) = new Literal(string((yyvsp[0].lit))); }
#line 1872 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 243 "parser.y" /* yacc.c:1646  */
    { (yyval.TerminalVariables) = new TerminalVariable(string((yyvsp[0].lit))); }
#line 1878 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 246 "parser.y" /* yacc.c:1646  */
    { (yyval.num) = int((yyvsp[0].num)); }
#line 1884 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 247 "parser.y" /* yacc.c:1646  */
    { (yyval.num) = int((yyvsp[0].num)); }
#line 1890 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 250 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1896 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 251 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 254 "parser.y" /* yacc.c:1646  */
    { (yyval.char_lit) = char((yyvsp[0].char_lit)); }
#line 1908 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 257 "parser.y" /* yacc.c:1646  */
    { (yyval.lit) = string((yyvsp[0].lit)); }
#line 1914 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1918 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 260 "parser.y" /* yacc.c:1906  */


int main(int argc, char **argv) {
	yyparse();
}
int yyerror(char *s) {
	fprintf(stderr, "error: %s\n", s);
}

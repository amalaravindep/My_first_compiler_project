#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define TEXTLEN 512
#define NSYMBOLS 1024

enum{
	T_EOF,
	T_PLUS,T_MINUS,
	T_STAR,T_SLASH,T_MODULUS,
	T_EQ,T_NE,
	T_LT,T_GT,T_LE,T_GE,
	T_INTLIT,T_SEMI,T_ASSIGN,T_IDENT,
	T_LBRACE,T_RBRACE,T_LPAREN,T_RPAREN,
	T_PRINT,T_INT,T_IF,T_ELSE
};

struct token{
	int token;
	int intvalue;
};

enum{
	A_ADD=1,A_SUBTRACT,A_MULTIPLY,A_DIVIDE,A_MODULUS,
	A_EQ,A_NE,A_LT,A_GT,A_LE,A_GE,
	A_INTLIT,
	A_IDENT,A_LVIDENT,A_ASSIGN,A_PRINT,A_GLUE,A_IF
};

struct ASTnode{
	int op;
	struct ASTnode *left;
	struct ASTnode *mid;
	struct ASTnode *right;
	union
	{
		int intvalue;
		int id;
	}v;
};

#define NOREG -1

struct symtable
{
	char *name;
};

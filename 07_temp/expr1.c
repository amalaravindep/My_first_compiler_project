#include "defs.h"
#include "data.h"
#include "decl.h"

static struct ASTnode *primary(void)
{
        struct ASTnode *n;
        int id;

        switch(Token.token)
        {
                case T_INTLIT:
                        n=mkastleaf(A_INTLIT,Token.intvalue);
                        break;
                case T_IDENT:
                        id=findglob(Text);
                        if(id==-1)
                                fatals("Unknown variable",Text);
                        n=mkastleaf(A_IDENT,id);
                        break;
                default:
                        fatald("Syntax error, token",Token.token);
        }
        scan(&Token);
        return(n);
}

static int arithop(int tokentype)
{
        if(tokentype > T_EOF && tokentype < T_INTLIT)
                return (tokentype);
        fatald("Syntax error, token",tokentype);
}

static int OpPrec[]={0,10,10,20,20,20,30,30,40,40,40,40};

static int op_precedence(int tokentype)
{
        int prec= OpPrec[tokentype];
        if(prec==0)
        {
                fatald("Syntax error, token",tokentype);
        }
        return (prec);
}

struct ASTnode *binexpr(int ptp)
{
        struct ASTnode *left,*right;
        int tokentype;
        left=primary();
        tokentype=Token.token;
        if(tokentype==T_SEMI)
                return (left);
        while(op_precedence(tokentype)>ptp)
        {
                scan(&Token);
                right=binexpr(OpPrec[tokentype]);
                if(left->op == T_INTLIT && right->op == T_INTLIT)
                {
                        if(tokentype == A_EQ || tokentype == A_NE || tokentype == A_GE ||
                        tokentype == A_LE || tokentype == A_LT || tokentype == A_GT)
                        {
                                int result=0;
                                        switch(tokentype)
                                        {
                                                case A_EQ: result=left->v.intvalue == right->v.intvalue;break;
                                                case A_NE: result=left->v.intvalue != right->v.intvalue;break;
                                                case A_GE: result=left->v.intvalue >= right->v.intvalue;break;
                                                case A_LE: result=left->v.intvalue <= right->v.intvalue;break;
                                                case A_GT: result=left->v.intvalue >  right->v.intvalue;break;
                                                case A_LT: result=left->v.intvalue <  right->v.intvalue;break;
                                        }
                                        freeast(left);
                                        freeast(right);
                                        left=mkastleaf(T_INTLIT,result);
                        }
                        else
                                mkastnode(arithop(tokentype),left,right,0);
                }
                tokentype=Token.token;
                if(tokentype==T_SEMI)
                        return (left);
        }
        return (left);
}

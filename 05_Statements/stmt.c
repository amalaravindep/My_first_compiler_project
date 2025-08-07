#include "defs.h"
#include "data.h"
#include "decl.h"

void statements(void)
{
	struct ASTnode *tree;
	int reg;
	while(1)
	{
		match(T_PRINT, "print");
		tree=binexpr(0);
		printf("%d\n",interpretAST(tree));
		reg=genAST(tree);
		genfreeregs();
		semi();
		if(Token.token==T_EOF)
			return;
	}
}

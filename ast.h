#ifndef AST_H
#define AST_H

typedef struct ASTnode
{
    int type;
    char text[100];
    struct ASTnode *left;
    struct ASTnode *right;
}ASTnode;

ASTnode *createastnode(int type, char *text, ASTnode *left, ASTnode *right);
void ASTtraverse(ASTnode *root, int depth);

#endif
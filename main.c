#include<stdio.h>
#include<string.h>
#include <stdlib.h>

#define NODE_SELECT 0
#define NODE_JOIN 1
#define NODE_TABLE 2
#define NODE_WHERE 3
#define NODE_COLUMN 4

typedef struct ASTnode
{
    int type;
    char text[100];
    struct ASTnode *left;
    struct ASTnode *right;
}ASTnode;

ASTnode *createnode(int type, char *text, ASTnode *left, ASTnode *right)
{//creating new node
    ASTnode *node=malloc(sizeof(ASTnode));
    node->type=type;
    strcpy(node->text,text);
    node->left=left;
    node->right=right;
    return node;
}


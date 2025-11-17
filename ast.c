#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

#define NODE_SELECT 0
#define NODE_JOIN 1
#define NODE_TABLE 2
#define NODE_WHERE 3

ASTnode *createastnode(int type, char *text, ASTnode *left, ASTnode *right)
{//creating new node
    ASTnode *node=malloc(sizeof(ASTnode));
    node->type=type;
    strcpy(node->text,text);
    node->left=left;
    node->right=right;
    return node;
}

void ASTtraverse(ASTnode *root, int depth)
{//preorder
    if(root==NULL)
    {
        //printf("no data\n");
        return;
    }
    for(int i=0;i<depth;i++)
    {
        printf(" ");
    }

    switch(root->type)
    {
        case NODE_SELECT:   printf("SELECT: %s\n",root->text);
                            break;
        case NODE_JOIN:     printf("JOIN: %s\n",root->text);
                            break;
        case NODE_TABLE:    printf("TABLE: %s\n",root->text);
                            break;
        case NODE_WHERE:    printf("WHERE: %s\n", root->text);
                            break;
    }
    ASTtraverse(root->left,depth+1);
    ASTtraverse(root->right,depth+1);
    
}
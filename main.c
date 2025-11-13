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

int cost_nested_loop(int rowsA,int rowsB)
{
    return rowsA*rowsB;
}
int cost_hash_join(int rowsA,int rowsB)
{
    return rowsA+rowsB;
}

int main()
{
/*
SELECT students.name,results.grade
FROM students
JOIN results 
ON students.rollnumber = results.rollnumber
WHERE students.age > 18;
*/

    ASTnode *tableStudents=createnode(NODE_TABLE,"students",NULL,NULL);
    ASTnode *tableResults=createnode(NODE_TABLE,"results",NULL,NULL);
    ASTnode *join=createnode(NODE_JOIN,"students.rollnumber = results.rollnumber",tableStudents,tableResults);
    ASTnode *where=createnode(NODE_WHERE, "students.age > 18",join,NULL);
    ASTnode *select=createnode(NODE_SELECT,"students.name, results.grade", where,NULL);

    printf("Query AST traversal\n");
    ASTtraverse(select,0);

    int rowsA=1;
    int rowsB=6;

    printf("cost estimation\n")
    printf("\n\nCost of Nested Loop = %d\n",cost_nested_loop(rowsA,rowsB));
    printf("Cost of Hash Join = %d\n",cost_hash_join(rowsA,rowsB));


    free(tableStudents);
    free(tableResults);
    free(join);
    free(where);
    free(select);

    return 0;

}
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

typedef struct table
{
    char tablename[50];
    int *rollnumbers;
    int count;
}Table;

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

double cost_nested_loop(int rowsA,int rowsB)
{
    return (double)rowsA*rowsB;
}
double cost_hash_join(int rowsA,int rowsB)
{
    return (double)rowsA+rowsB;
}


void nested_loop_join(Table A, Table B)
{
    int c=0;
    for(int i=0;i<A.count;i++)
    {
        for(int j=0; j<B.count;j++)
        {
            if(A.rollnumbers[i]==B.rollnumbers[j])
            {
                printf("Matches found Table A[%d]:%d\tTable B[%d]:%d\n",i,A.rollnumbers[i],j,B.rollnumbers[j]);
                c++;
            }
        }
    }
    if(c==0)
    {
        printf("nested loop join : NO matches found\n");
    }
    else
    {
    printf("Total mached rollnumbers from nested loop join=%d\n",c);
    }
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

    printf("\nCost Estimation\n");
    printf("Cost of Nested Loop = %.2f\n",cost_nested_loop(rowsA,rowsB));
    printf("Cost of Hash Join = %.2f\n",cost_hash_join(rowsA,rowsB));

    int rollnumbersA[]={3,4,5};
    int rollnumbersB[]={1,2,3,4,5,6,7};
    int countA=sizeof(rollnumbersA)/sizeof(rollnumbersA[0]);
    int countB=sizeof(rollnumbersB)/sizeof(rollnumbersB[0]);

    printf("\ncount of rollnumbersA= %d\n",countA);
    printf("count of rollnumbersB= %d\n",countB);

   
    Table A={"students",rollnumbersA,countA};
    Table B={"results",rollnumbersB,countB};

    nested_loop_join(A,B);

    //printf("rollnumbers =%d\n",A.rollnumbers);

    free(tableStudents);
    free(tableResults);
    free(join);
    free(where);
    free(select);

    return 0;

}
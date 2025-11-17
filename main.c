#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include "ast.h"
#include "optimizer.h"

#define NODE_SELECT 0
#define NODE_JOIN 1
#define NODE_TABLE 2
#define NODE_WHERE 3

int main()
{
/*
SELECT students.name,results.grade
FROM students
JOIN results 
ON students.rollnumber = results.rollnumber
WHERE students.age > 18;
*/

    ASTnode *tableStudents=createastnode(NODE_TABLE,"students",NULL,NULL);
    ASTnode *tableResults=createastnode(NODE_TABLE,"results",NULL,NULL);
    ASTnode *join=createastnode(NODE_JOIN,"students.rollnumber = results.rollnumber",tableStudents,tableResults);
    ASTnode *where=createastnode(NODE_WHERE, "students.age > 18",join,NULL);
    ASTnode *select=createastnode(NODE_SELECT,"students.name, results.grade", where,NULL);

    printf("Query AST traversal\n");
    ASTtraverse(select,0);

    int rollnumbersA[]={3,4,5};
    int rollnumbersB[]={1,2,3,4,5,6,7};
    int countA=sizeof(rollnumbersA)/sizeof(rollnumbersA[0]);
    int countB=sizeof(rollnumbersB)/sizeof(rollnumbersB[0]);

    printf("\ncount of rollnumbersA= %d\n",countA);
    printf("count of rollnumbersB= %d\n",countB);

   
    Table A={"students",rollnumbersA,countA};
    Table B={"results",rollnumbersB,countB};

    //nested_loop_join(A,B);
    //hash_join(A,B);

    select_join_algorithm(A,B);

    free(tableStudents);
    free(tableResults);
    free(join);
    free(where);
    free(select);

    return 0;

}
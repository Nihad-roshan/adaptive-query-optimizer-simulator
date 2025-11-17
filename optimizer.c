#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "optimizer.h"
#include "plan.h"
#include "cost_estimation.h"

#define HASH_SIZE 100

void nested_loop_join(Table A, Table B)
{
    printf("\nPerforming Nested Loop Join\n");

    Table *outer;
    Table *inner;

    if(A.count <=B.count)
    {
        outer=&A;
        inner=&B;
    }
    else
    {
        outer=&B;
        inner=&A;
    }

    printf("\nOuter table is %s with rollnumber count(rows) =%d\n",outer->tablename,outer->count);
    printf("inner table is %s with rollnumber count(rows) =%d\n\n",inner->tablename,inner->count);

    int maches=0;
    for(int i=0;i<outer->count;i++)
    {
        for(int j=0; j<inner->count;j++)
        {
            if(outer->rollnumbers[i]==inner->rollnumbers[j])
            {
                printf("Matches found Table outer[%d]:%d\tTable inner[%d]:%d\n",i,outer->rollnumbers[i],j,inner->rollnumbers[j]);
                maches++;
            }
        }
    }
    if(maches==0)
    {
        printf("\nnested loop join : NO matches found\n");
    }
    else
    {
    printf("\nTotal mached rollnumbers from nested loop join=%d\n",maches);
    }
}

void hash_join(Table A,Table B)
{
    printf("Performing Hash Join\n");
    
    Table *build;
    Table *probe;

    if(A.count<B.count)
    {
        build=&A;
        probe=&B;
    }
    else
    {
        build=&B;
        probe=&A;
    }

    printf("\nBuild Table is %s with rollnumber count(rows)=%d\n",build->tablename,build->count);
    printf("probe Table is %s with rollnumber count(rows)=%d\n\n",probe->tablename,probe->count);
    
    
    int maches=0,hash[HASH_SIZE];


    for(int i=0; i<HASH_SIZE;i++)
    {
        hash[i]=-1;
    }

    for(int i=0;i<build->count;i++)
    {//build
        hash[build->rollnumbers[i]%HASH_SIZE]=build->rollnumbers[i];
    }

    for(int i=0;i<probe->count;i++)
    {//probe
        //printf("\n-----\n");
        int h=probe->rollnumbers[i]%HASH_SIZE;
        if(hash[h]==probe->rollnumbers[i])
        {
            maches++;
            printf("Matches found =%d at hash[%d]\n",probe->rollnumbers[i],h);
        }
    }
    if(maches==0)
    {
    printf("\nhash join: No matches found\n");
    }
    else
    {
        printf("\nTotal maches found from hash join =%d\n",maches);
    }
}

void select_join_algorithm(Table A,Table B)
{
    if(A.count==0 || B.count==0)
    {
        printf("empty table found No matches\n");
        return;
    }
    printf("\nCost Estimation:\n");
    double cost_of_nested_loop=cost_nested_loop(A.count,B.count);
    double cost_of_hash_join= cost_hash_join(A.count,B.count);

    printf("Cost of Nested Loop = %.2f\n",cost_of_nested_loop);
    printf("Cost of Hash Join = %.2f\n",cost_of_hash_join);

    if(cost_of_nested_loop < cost_of_hash_join)
    {
        printf("\nchoosing Nested Loop Join\n");
        nested_loop_join(A,B);
    }
    else
    {
        printf("\nchoosing Hash Loop Join\n");
        hash_join(A,B);
    }

    plannode *p_scantableA=createplannode(PLAN_TABLE_SCAN,A.tablename,NULL,NULL);
    plannode *p_scantableB=createplannode(PLAN_TABLE_SCAN,B.tablename,NULL,NULL);

    plannode *p_joinnode;
    if(cost_of_nested_loop<cost_of_hash_join)
    {
        p_joinnode=createplannode(PLAN_NESTEDLOOP,"students.rollnumber = results.rollnumber",p_scantableA,p_scantableB);
    }
    else
    {
        p_joinnode=createplannode(PLAN_HASHJOIN,"students.rollnumber = results.rollnumber",p_scantableA,p_scantableB);
    }

    plannode *P_filternode=createplannode(PLAN_WHERE_FILTER,"students.age > 18",p_joinnode,NULL);
    plannode *p_projectnode=createplannode(PLAN_SELECT_OUTPUT,"students.name, results.grade",P_filternode,NULL);

    printf("\n\nQuery execution plan tree\n\n");
    print_plan(p_projectnode,0);

    free(p_scantableA);
    free(p_scantableB);
    free(p_joinnode);
    free(P_filternode);
    free(p_projectnode);
    
}
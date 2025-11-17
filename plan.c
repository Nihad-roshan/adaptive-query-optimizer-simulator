#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "plan.h"

plannode *createplannode(plantype type,char *info,plannode *left,plannode *right)
{
    plannode *node=malloc(sizeof(plannode));
    node->type=type;
    strcpy(node->info,info);
    node->left=left;
    node->right=right;
    return node;
}

void print_plan(plannode *root,int depth)
{
    if(root==NULL)
    {
        //printf("--1--");
        return;
    }

    for(int i=0;i<depth;i++)
    {
        printf(" ");
    }
    //printf("---2---");

    switch(root->type)
    {
        case PLAN_SELECT_OUTPUT: printf("PROJECT: %s\n",root->info);
                                 break;
        case PLAN_WHERE_FILTER: printf("FILTER: %s\n",root->info);
                                break;
        case PLAN_NESTEDLOOP: printf("NESTED LOOP JOIN: %s\n",root->info);
                              break;
        case PLAN_HASHJOIN: printf("HASH JOIN: %s\n",root->info);
                            break;
        case PLAN_TABLE_SCAN: //printf("--4--");
                                printf("SEQ SCAN: %s\n",root->info);
                               // printf("--5--");
                                break;
    }

    print_plan(root->left,depth+1);
    print_plan(root->right,depth+1);
}
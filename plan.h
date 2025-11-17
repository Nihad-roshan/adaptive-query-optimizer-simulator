#ifndef PLAN_H
#define PLAN_H

typedef enum{PLAN_SELECT_OUTPUT,PLAN_WHERE_FILTER,PLAN_NESTEDLOOP,PLAN_HASHJOIN,PLAN_TABLE_SCAN}plantype;

typedef struct plannode
{
    plantype type;
    char info[100];
    struct plannode *left;
    struct plannode *right;
}plannode;

plannode *createplannode(plantype type,char *info,plannode *left,plannode *right);

void print_plan(plannode *root,int depth);

#endif
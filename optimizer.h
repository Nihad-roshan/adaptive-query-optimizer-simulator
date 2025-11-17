#ifndef OPT_H
#define OPT_H

#include "plan.h"

typedef struct table
{
    char tablename[50];
    int *rollnumbers;
    int count;
}Table;

void nested_loop_join(Table A, Table B);

void hash_join(Table A,Table B);

void select_join_algorithm(Table A,Table B);

#endif
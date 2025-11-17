#include "cost_estimation.h"

double cost_nested_loop(int rowsA,int rowsB)
{
    return (double)rowsA*rowsB;
}
double cost_hash_join(int rowsA,int rowsB)
{
    return (double)rowsA+rowsB;
}
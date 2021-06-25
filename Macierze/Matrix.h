
#ifndef _MATRIX_
#define _MATRIX_

int CreateMatrix( double*** pTab, int dim );
void DeleteMatrix( double*** pTab, int dim );
void TransMatrix( double** pTab, int dim );
void InverseMatrix( double** pInversed, double** pTab, int dim, double det );
double Det( double** pTab, int dim );
void LayoutEq( double** pInv, double* pB, double* pRes, int dim );
void PrintMatrix( double** pTab, int dim );

#endif
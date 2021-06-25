#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ComplMatrix( double** pTab, double** pOutTab, int dim );
void Complement( double** pOutTab, double** pTab,  int row, int col, int dim );


int CreateMatrix( double*** pTab, int dim )
{
	double** pTemp = *pTab = (double**)malloc( dim*sizeof( double* ) );
	if( !(*pTab ) ) return 0;
	for( int i = 0; i<dim; i++, pTemp++ )
	{
		*pTemp = (double*)malloc( dim*sizeof( double ) );
		if( !(*pTemp ) ) return 0;
		memset( *pTemp, 0, dim*sizeof( double ) );
	}
	return 1;
}
void DeleteMatrix( double*** pTab, int dim )
{
	double** pTemp = *pTab;
	for( int i = 0; i<dim; i++, pTemp++ )
	{
		free( *pTemp );
	}
	free( *pTab );
	*pTab = NULL;
}
void TransMatrix( double** pTab, int dim )
{
	double** pMatrix = pTab;
	for( int i = 0; i<dim-1; i++, pTab++ )
	{
		double* pRow = *pTab+i+1;
		for( int j = i+1; j<dim; j++, pRow++ )
		{
			double x = *pRow;
			*pRow = pMatrix[j][i];
			pMatrix[j][i] = x;
		}
	}
}
void InverseMatrix( double** pInversed, double** pTab, int dim, double det )
{
	ComplMatrix( pTab, pInversed, dim );
	TransMatrix( pInversed, dim );
	for( int i = 0; i<dim; i++, pInversed++ )
	{
		double* pRow = *pInversed;
		for( int j = 0; j<dim; j++, pRow++ )
		{
			*pRow /= det;
		}
	}
}
double Det( double** pTab, int dim )
{
	if( dim==1 ) return **pTab;
	if( dim==2 ) return **pTab * pTab[1][1] - ( pTab[0][1]*pTab[1][0] );
	double** pcuttab = NULL;
	if( !CreateMatrix( &pcuttab, dim-1 ) )
	{
		printf( "Error: Matrix cannot be created det will be zero" );
		return 0;
	}
	double res = 0;
	double* pRow = *pTab;
	int znak = 1;
	for( int i = 0; i<dim; i++, pRow++ )
	{
		Complement( pcuttab, pTab, 0, i, dim );
		res += *pRow*Det( pcuttab, dim-1 )*znak;
		znak = -znak;
	}

	DeleteMatrix( &pcuttab, dim-1 );
	return res;
}
void PrintMatrix( double** pTab, int dim )
{
	for( int i = 0; i<dim; i++, pTab++ )
	{
		double* pRow = *pTab;
		for( int j = 0; j<dim; j++, pRow++ )
		{
			printf("%f\t",*pRow);
		}
		printf("\n");
	}
}
void Complement( double** pOutTab, double** pTab,  int row, int col, int dim )
{
	for( int i = 0; i<dim; i++, pTab++ )
	{
		if( i==row ) continue;
		double* pRow = *pTab;
		double* pOutRow = *pOutTab++;
		for( int j = 0; j<dim; j++, pRow++ )
		{
			if( j==col ) continue;
			*pOutRow++ = *pRow;
		}
	}
}
void ComplMatrix( double** pTab, double** pOutTab, int dim )
{
	double** pcuttab = NULL;
	if( !CreateMatrix( &pcuttab, dim-1 ) )
	{
		printf( "ERROR: Matrix cannot be created\n" );
		return;
	}
	for( int i = 0; i<dim; i++, pOutTab++ )
	{
		double* pOutRow = *pOutTab;
		int znak = (i%2)? -1 : 1;
		for( int j = 0; j<dim; j++, pOutRow++ )
		{
			Complement( pcuttab, pTab, i, j, dim );
			*pOutRow = znak*Det( pcuttab, dim-1 );
			znak = -znak;

		}
	}
	DeleteMatrix( &pcuttab, dim-1 );
}
void LayoutEq( double** pInv, double* pVector, double* pResult, int dim )
{
	for( int i = 0; i<dim; i++, pResult++, pInv++ )
	{
		double* pRow = *pInv;
		double* pVectorRow = pVector;
		for( int j = 0; j<dim; j++, pVectorRow++, pRow++ )
		{
			*pResult += *pRow * *pVectorRow;
		}
	}
}
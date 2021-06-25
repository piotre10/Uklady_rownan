#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define _DEBUG_
#define EPSILON 1e-200
void ReadData( FILE* fin, double** pMatrix, double* b, int dim );
void PrintVector( double* pVector, int length );
int CreateVector( double** pVector, int size );
void DeleteVector( double** pVector );

int main( int argc, char* argv[] )
{
	if (argc != 2)
	{
		printf( "Usage: %s <input file>", argv[0] );
		return 1;
	}
	FILE* fin = NULL;
	fin = fopen( argv[1], "r" );
	if ( !fin )
	{
		printf( "Error1: File cannot be open" );
		return -1;
	}
	int m_dim = 0;
	fscanf ( fin, "%d", &m_dim );
	if( !m_dim )
	{
		printf( "Error2: Wrong input data" );
		return -2;
	}
#ifdef _DEBUG_
	printf( "--------------DEBUG------------------\n" );
	printf( "Dim: %d\n", m_dim );
#endif 
	double** pMatrix = NULL;
	if( !CreateMatrix(&pMatrix, m_dim) )
	{
		printf( "Error3: Creating matrix went wrong" );
		return -3;
	}

	double* pVector = NULL;
	if( !CreateVector(&pVector, m_dim) )
	{
		printf( "Error4: Creating vector went wrong" );
		return -4;
	}

	ReadData( fin, pMatrix, pVector, m_dim );

#ifdef _DEBUG_
	printf( "Macierz wejsciowa:\n" );
	PrintMatrix( pMatrix, m_dim );
	printf( "Wektor wyrazow wolnych:\n" );
	PrintVector( pVector, m_dim );
#endif

	double det = Det( pMatrix, m_dim );
#ifdef _DEBUG_
	printf( "\nDet: %f \n", det );
#endif 
	if ( fabs( det )<EPSILON )
	{
		printf( "det is 0 cannot solve this" );
		return 2;
	}
	double** pInversedMatrix = NULL;
	if ( !CreateMatrix(&pInversedMatrix, m_dim) )
	{
		printf( "Error5: Creating matrix went wrong" );
		return -5;
	}
	InverseMatrix( pInversedMatrix, pMatrix, m_dim, det );
#ifdef _DEBUG_
	printf( "Inversed Matrix: \n");
	PrintMatrix( pInversedMatrix, m_dim );
	printf( "############ END OF DEBUG ##################\n" );
#endif 
	double* pResult = NULL;
	if ( !CreateVector(&pResult, m_dim) )
	{
		printf( "Error6: Creating vector went wrong" );
		return -6;
	}
	
	LayoutEq( pInversedMatrix, pVector, pResult,m_dim );
	printf( "Solution:\n" );
	PrintVector( pResult, m_dim );

	DeleteVector( &pVector );
	DeleteVector( &pResult );
	DeleteMatrix( &pInversedMatrix, m_dim );
	DeleteMatrix( &pMatrix, m_dim );

	return 0;
}
void ReadData( FILE* fin, double** pMatrix, double* b, int dim )
{
	for( int i = 0; i<dim; i++, b++, pMatrix++ )
	{
		double* p_row_temp = *pMatrix;
		for( int j = 0; j<dim; j++, p_row_temp++ )
		{
			fscanf( fin, "%lf", p_row_temp );
		}
		fscanf( fin, "%lf", b );
	}
	fclose( fin );
}
int CreateVector( double** pVector, int size )
{
	*pVector = (double*)malloc( size*sizeof( double ) );
	if( !(*pVector )) return 0;
	memset( *pVector, 0, size*sizeof( double ) );
	return 1;
}
void DeleteVector( double** pVector )
{
	free( *pVector );
	*pVector = NULL;
}
void PrintVector( double* pVector, int length )
{
	for( int i = 0; i<length; i++, pVector++ )
	{
		printf("%f\t", *pVector);
	}
}
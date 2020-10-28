#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int *num1, int *num2)
{
	int temp = *num1;
	*num1 =  *num2;
	*num2 = temp;
}

void OrderWithOmp ()
{
    int SIZE =1<<10;
	int A[SIZE];

	for(int i=0;i<SIZE;i++)
	{
	    A[i]=rand()%SIZE;
	}

	int N = SIZE;
	int i=0, j=0;
	int first;
	double start,end;

//	start=omp_get_wtime();

	for( i = 0; i < N-1; i++ )
	{
		first = i % 2;

		#pragma omp parallel for default(none),shared(A,first,N)
		for( j = first; j < N-1; j += 1 )
		{
			if( A[ j ] > A[ j+1 ] )
			{
				swap( &A[ j ], &A[ j+1 ] );
			}
		}
	}

//    end=omp_get_wtime();

    printf("\n-------------------------\n");
    printf("Time with OMP  = %f",(end-start));
}

void OrderWithoutOmp ()
{
    int SIZE =1<<14;
	int A[SIZE];

	for(int i=0;i<SIZE;i++)
	{
	    A[i]=rand()%SIZE;
	}

	int N = SIZE;
	int i=0, j=0;
	int first;
	double start,end;

	for( i = 0; i < N-1; i++ )
	{
		first = i % 2;

		for( j = first; j < N-1; j += 1 )
		{
			if( A[ j ] > A[ j+1 ] )
			{
				swap( &A[ j ], &A[ j+1 ] );
			}
		}
	}

//	for(i=0;i<N;i++)
//	{
//		printf(" %d",A[i]);
//	}

    printf("\n-------------------------\n");
    printf("Time without OMP = %f",(end-start));
}

int main (int argc, char *argv[]) {
	OrderWithOmp();
	OrderWithoutOmp();
}

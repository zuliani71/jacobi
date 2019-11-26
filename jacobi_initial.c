/* Jacobi solver for Laplace equation.
 * Description: This code solves the Laplace equation using Jacobi iterative
 *              method on a square grid, given the boundary conditions
 *
 * Author: G.P. Brandino
 * Copyright: 2019 eXact-lab s.r.l.
 * License: GPLv2
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void setBoundaryConditions(double* grid, double* gridNew, int dimension){
  // Note that the borders are never modified by the update, so we need to
  // set up b.c. on BOTH the buffers
  int i;
  double increment = 100.0 / ( dimension + 1 );

  for( i=1; i <= dimension + 1; ++i ) {
      grid[ i * ( dimension + 2 ) ] = i * increment;
      grid[ ( ( dimension + 1 ) * ( dimension + 2 ) ) + ( dimension + 1 - i ) ] = i * increment;
      gridNew[ i * ( dimension + 2 ) ] = i * increment;
      gridNew[ ( ( dimension + 1 ) * ( dimension + 2 ) ) + ( dimension + 1 - i ) ] = i * increment;
  }

}


void update(double* grid, double* gridNew, int dimension){

  int i,j;
  for( i = 1 ; i <= dimension; ++i ) {
      for( j = 1; j <= dimension; ++j ) {
          gridNew[ ( i * ( dimension + 2 ) ) + j ] = 0.25 *
          ( grid[ ( ( i - 1 ) * ( dimension + 2 ) ) + j ]
          + grid[ ( i * ( dimension + 2 ) ) + ( j + 1 ) ]
          + grid[ ( ( i + 1 ) * ( dimension + 2 ) ) + j ]
          + grid[ ( i * ( dimension + 2 ) ) + ( j - 1 ) ] );
      }
  }
}

void printOutput(double* grid, int dimension) {

  int i,j;
  FILE *file;
  file = fopen( "solution.dat", "w+" );

  for( i = 0; i < dimension + 2; ++i ){
      for( j = 0; j < dimension + 2; ++j ){
          fprintf(file, "%f ", grid[ ( i * ( dimension + 2 ) ) + j ] );
      }
      fprintf(file, "\n");
  }

  fclose( file );
}

int main(int argc, char* argv[]){

    size_t i, j, it;
    double *grid, *gridNew, *gridTmp;

    size_t dimension = 0, iterations = 0;
    size_t dimensionByte = 0;

    // check on input parameters
    if(argc != 3) {
        fprintf(stderr,"\nwrong number of arguments. Usage: ./a.out dimension iterations \n");
        return 1;
    }

    dimension = atoi(argv[1]);
    iterations = atoi(argv[2]);

    printf("m size = %zu\n", dimension);
    printf("number of iter = %zu\n", iterations);

    dimensionByte = sizeof(double) * ( dimension + 2 ) * ( dimension + 2 );
    grid = ( double* )malloc( dimensionByte );
    gridNew = ( double* )malloc( dimensionByte );

    //fill initial values
    for( i = 0; i < (dimension + 2) * (dimension + 2); ++i ) {
        grid[i] = 0;
        gridNew[i] = 0;
    }

    // set up boundary conditions
    setBoundaryConditions(grid, gridNew, dimension);

    // start the iterations of the algorithm
    for( it = 0; it < iterations; ++it ) {

        update(grid, gridNew, dimension);
        // swap the pointers
        gridTmp = grid;
        grid = gridNew;
        gridNew = gridTmp;
    }

    printOutput(grid, dimension);

    free( grid );
    free( gridNew );

    return 0;
}

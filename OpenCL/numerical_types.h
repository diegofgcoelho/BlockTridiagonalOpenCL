/*
 * numerical_types.h
 *
 *  Created on: Oct 11, 2017
 *      Author: Diego Coelho, PhD Candidate, University of Calgary
 *
 *      Description:
 *      This file contains the necessary numerical types used in the OpenCL implementation.
 */

#ifndef NUMERICAL_TYPES_H_
#define NUMERICAL_TYPES_H_

#define bsize 4
#define nblockrow 1000

/*
 * This represents a small bsize by bsize dense matrix,
 * which will be the off-diagonal blocks of the block tridiagonal matrix.
 * The data is organized in a way that rows are represented in contigous area.
 * It means that the first bsize elements in the array data are the elements
 * of the first row, the second set of bsize values are the elements of the
 * second row and so on.
 */
typedef struct{
	double data[bsize*bsize];
} block;

/*
 * This represents a small bsize by bsize dense symmetric matrix,
 * which will be the diagonal blocks of the block tridiagonal matrix.
 * The data is organized such that the elements represent the upper
 * triangular matrix. The first set of bsize elements represents the
 * first row. The second set of bsize-1 values represents the matrix
 * elements from the diagonal to the end of the row. The third set of
 * bsize-2 values represents the values of the third row from the
 * diagonal up to the end of the row and so on.
 */

typedef struct{
	double data[bsize*(bsize+1)/2];
} sblock;


/*
 * This represents a symmetric block tridiagonal matrix with
 * real entries.
 */

typedef struct{
	block offdiagonal[nblockrow-1];
	sblock diagonal[nblockrow];
} sblocktrid;

/*
 * This represents a symmetric block pentadiagonal matrix with
 * real entries. The blocks on off-diagonal are organized in row
 * ordered manner, i.e., offdiagonal[0] and offdiagonal[0] are the
 * off-diagonal elements of the first 'row' of blocks.
 */

typedef struct{
	block offdiagonal[2*nblockrow-2];
	sblock diagonal[nblockrow];
} sblockpent;

//Functions for the block type

/*
 * This function perform the multiplication of two blocks,
 * A and B and returns it in the block C, i.e., C = A*B.
 */

void multiplydd(block *A, block *B, block *C);

//Functions for the sblock type

/*
 * This function perform the multiplication of two blocks,
 * a dense nonsymmetric A and dense symmetric B and returns it in the block C, i.e., C = A*B.
 */

void multiplyds(block *A, sblock *B, block *C);

/*
 * This function perform the multiplication of two blocks,
 * a dense nonsymmetric A and dense symmetric B and returns it in the block C, i.e., C = A*B.
 */

void multiplysd(sblock *A, block *B, block *C);

/*
 * This function perform the multiplication of two blocks,
 * both dense symmetric A and B and returns it in the block C, i.e., C = A*B.
 */

void multiplyss(sblock *A, sblock *B, sblock *C);


/*
 * This function simply prints the block A in the screen in a organized manner.
 */

void printblock(block A);

/*
 * This function simply prints the sblock A in the screen in a organized manner.
 */

void printsblock(sblock A);

#endif /* NUMERICAL_TYPES_H_ */

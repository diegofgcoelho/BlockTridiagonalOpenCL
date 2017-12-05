/*
 * numerical_types.c
 *
 *  Created on: Nov 27, 2017
 *      Author: Diego Coelho, PhD Candidate, University of Calgary
 *
 *      Description:
 *      This file contains the functions necessary for the numerical types used in the OpenCL implementation.
 */

#include "numerical_types.h"

#include <stdio.h>

//Functions for the block type
void multiplydd(block *A, block *B, block *C){
	/*
	 * This function perform the multiplication of two blocks,
	 * A and B and returns it in the block C, i.e., C = A*B.
	 */

	for(unsigned int i = 0; i < bsize; i++){
		for(unsigned int j = 0; j < bsize; j++){
			(*C).data[j+bsize*i] = 0.0;
			for(unsigned int k = 0; k < bsize; k++){
				(*C).data[j+bsize*i] += (*A).data[bsize*i+k]*(*B).data[j+bsize*k];
			}
		}
	}
}

//Functions for the sblock type
void multiplyds(block *A, sblock *B, block *C){
	/*
	 * This function perform the multiplication of two blocks,
	 * a dense nosymmetric A and dense symmetric B and returns it in the block C, i.e., C = A*B.
	 */

	for(unsigned int i = 0; i < bsize; i++){
		for(unsigned int j = 0; j < bsize; j++){
			(*C).data[j+bsize*i] = 0.0;
			unsigned int BColpos = j;
			for(unsigned int k = 0; k < j; k++){
				(*C).data[j+bsize*i] += (*A).data[bsize*i+k]*(*B).data[BColpos];
				BColpos = BColpos+(bsize-1-k);
			}
			for(unsigned int k = j; k < bsize; k++){
				(*C).data[j+bsize*i] += (*A).data[bsize*i+k]*(*B).data[BColpos];
				BColpos++;
			}
		}
	}
}

void multiplysd(sblock *A, block *B, block *C){
	/*
	 * This function perform the multiplication of two blocks,
	 * a dense nonsymmetric A and dense symmetric B and returns it in the block C, i.e., C = A*B.
	 */

	for(unsigned int i = 0; i < bsize; i++){
		for(unsigned int j = 0; j < bsize; j++){
			(*C).data[j+bsize*i] = 0.0;
			unsigned int BRowpos = i;
			for(unsigned int k = 0; k < i; k++){
				(*C).data[j+bsize*i] += (*A).data[BRowpos]*(*B).data[bsize*k+j];
				BRowpos = BRowpos+(bsize-1-k);
			}
			for(unsigned int k = i; k < bsize; k++){
				(*C).data[j+bsize*i] += (*A).data[BRowpos]*(*B).data[bsize*k+j];
				BRowpos++;
			}
		}
	}
}

//TODO
void multiplyss(sblock *A, sblock *B, sblock *C){
	/*
	 * This function perform the multiplication of two blocks,
	 * both dense symmetric A and B and returns it in the block C, i.e., C = A*B.
	 */


	unsigned int CElepos = 0;
	for(unsigned int i = 0; i < bsize; i++){
		for(unsigned int j = i; j < bsize; j++){
			(*C).data[CElepos] = 0.0;
			unsigned int ARowpos = i;
			unsigned int BColpos = j;
			for(unsigned int k = 0; k < i; k++){
				printf("CElepos = %d, ARowpos = %d, BColpos = %d\n", CElepos, ARowpos, BColpos);
				(*C).data[CElepos] += (*A).data[ARowpos]*(*B).data[BColpos];
				ARowpos = ARowpos+(bsize-1-k);
				BColpos = BColpos+(bsize-1-k);
			}
			for(unsigned int k = i; k < j; k++){
				printf("CElepos = %d, ARowpos = %d, BColpos = %d\n", CElepos, ARowpos, BColpos);
				(*C).data[CElepos] += (*A).data[ARowpos]*(*B).data[BColpos];
				ARowpos++;
				BColpos = BColpos+(bsize-1-k);
			}
			for(unsigned int k = i; k < j; k++){
				printf("CElepos = %d, ARowpos = %d, BColpos = %d\n", CElepos, ARowpos, BColpos);
				(*C).data[CElepos] += (*A).data[ARowpos]*(*B).data[BColpos];
				ARowpos++;
				BColpos++;
			}
			CElepos++;
		}
	}
}


void printblock(block A){
	/*
	 * This function simply prints the block A in the screen in a organized manner.
	 */

	printf("\n[");
	for(unsigned int i = 0; i < bsize; i++){
		for(unsigned int j = 0; j < bsize; j++){
			printf("  %.5f", A.data[i*bsize+j]);
		}
		printf("\n");
	}
	printf("]\n");
}

void printsblock(sblock A){
	/*
	 * This function simply prints the sblock A in the screen in a organized manner.
	 */

	printf("\nUpper Triangular Part\n[");
	unsigned int Apos = 0;
	for(unsigned int i = 0; i < bsize; i++){
		for(unsigned int j = i; j < bsize; j++){
			Apos++;
			printf("  %.5f", A.data[Apos]);
		}
		printf("\n");
	}
	printf("]\n");
}

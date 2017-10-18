/*
 * kernel.cl
 *
 *  Created on: Oct 11, 2017
 *      Author: Diego Coelho, PhD Candidate, University of Calgary
 *
 *      Description:
 *      This file contains the kernels that will be run in the GPU
 */
 
 __kernel void squared_row(__global sblocktrid* input, __global sblockpent* output, __global cl_uint nrows){
 	//This kernel computes the square of a symmetric block tridiagonal matrix. The result,
 	//naturally, is a symmetric block pentadiagonal matrix.  
 	
 	//input represents the input symmetric block tridiagonal matrix
 	//output represents the resulting symmetric block pentadiagonal matrix
 	//nrows is the number of rows that each work item must process
 
  	size_t id = global_id(0);
  	
  	
 
 
 }
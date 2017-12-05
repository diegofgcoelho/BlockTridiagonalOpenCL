/*
 * test_numerical_types.cpp
 *
 *  Created on: Oct 17, 2017
 *      Author: Diego Coelho, PhD Candidate, University of Calgary
 *
 *      Description:
 *      This file contains the testing functions for the necessary numerical types used in the OpenCL implementation.
 */

#include "test_numerical_types.h"

void test_multplydd(){
	//Defining test matrices
	Eigen::MatrixXd A = Eigen::MatrixXd::Random(bsize, bsize);
	Eigen::MatrixXd B = Eigen::MatrixXd::Random(bsize, bsize);
	Eigen::MatrixXd R;
	//block and sblock objects to store the test matrices
	block Ab;
	block Bb;
	block Rb;
	//Converting the test matrices to the block and sblock types
	{
		unsigned int Bpos = 0;//Sore the position of Bb elements
		for(unsigned int i = 0; i < A.rows(); i++){
			for(unsigned int j = 0; j < A.cols(); j++){
				Ab.data[i*A.cols()+j] = A(i,j);
				Bb.data[i*B.cols()+j] = B(i,j);
			}
		}
	}

	//Multiplying the matrices using Eigen library
	R = A*B;
	//Multiplying the matrices using multiplydd library
	multiplydd(&Ab, &Bb, &Rb);

	std::cout << "\n\n********************Testing mulplydd*****************\n" << std::endl;
	std::cout << "Input matrices, A and B, dense matrices:" << std::endl;
	std::cout << A << "\n" << std::endl;
	std::cout << B << std::endl;

	std::cout << "Eigen output is" << std::endl;
	std::cout << R << std::endl;

	std::cout << "multiplydd output is" << std::endl;
	printblock(Rb);

}


void test_multplyds(){
	//Defining test matrices
	Eigen::MatrixXd A = Eigen::MatrixXd::Random(bsize, bsize);
	Eigen::MatrixXd S = Eigen::MatrixXd::Random(bsize, bsize); S = S*S.transpose();
	Eigen::MatrixXd R;

	//block and sblock objects to store the test matrices
	block Ab;
	sblock Bb;
	block Rb;
	//Converting the test matrices to the block and sblock types
	{
		unsigned int Bpos = 0;//Sore the position of Bb elements
		for(unsigned int i = 0; i < A.rows(); i++){
			for(unsigned int j = 0; j < A.cols(); j++){
				Ab.data[i*A.cols()+j] = A(i,j);
				if(j >= i){
					Bb.data[Bpos] = S(i,j);
					Bpos++;
				}
			}
		}
	}

	//Multiplying the matrices using Eigen library
	R = A*S;
	//Multiplying the matrices using multiplyds library
	multiplyds(&Ab, &Bb, &Rb);

	std::cout << "\n\n********************Testing mulplyds*****************\n" << std::endl;
	std::cout << "Input matrices, A and S, dense and symmetric dense, respectively:" << std::endl;
	std::cout << A << "\n" << std::endl;
	std::cout << S << std::endl;

	std::cout << "Eigen output is" << std::endl;
	std::cout << R << std::endl;

	std::cout << "multiplyds output is" << std::endl;
	printblock(Rb);

}

void test_multplysd(){
	//Defining test matrices
	Eigen::MatrixXd A = Eigen::MatrixXd::Random(bsize, bsize);
	Eigen::MatrixXd S = Eigen::MatrixXd::Random(bsize, bsize); S = S*S.transpose();
	Eigen::MatrixXd R;

	//block and sblock objects to store the test matrices
	block Ab;
	sblock Bb;
	block Rb;
	//Converting the test matrices to the block and sblock types
	{
		unsigned int Bpos = 0;//Sore the position of Bb elements
		for(unsigned int i = 0; i < A.rows(); i++){
			for(unsigned int j = 0; j < A.cols(); j++){
				Ab.data[i*A.cols()+j] = A(i,j);
				if(j >= i){
					Bb.data[Bpos] = S(i,j);
					Bpos++;
				}
			}
		}
	}

	//Multiplying the matrices using Eigen library
	R = S*A;
	//Multiplying the matrices using multiplyds library
	multiplysd(&Bb, &Ab, &Rb);


	std::cout << "\n\n********************Testing mulplysd*****************\n" << std::endl;
	std::cout << "Input matrices, S and A, symmetric dense and dense, respectively:" << std::endl;
	std::cout << S << "\n" << std::endl;
	std::cout << A << std::endl;

	std::cout << "Eigen output is" << std::endl;
	std::cout << R << std::endl;

	std::cout << "multiplysd output is" << std::endl;
	printblock(Rb);

}


void test_multplyss(){
	//Defining test matrices
	Eigen::MatrixXd A = Eigen::MatrixXd::Random(bsize, bsize); A = A*A.transpose();
	Eigen::MatrixXd S = Eigen::MatrixXd::Random(bsize, bsize); S = S*S.transpose();
	Eigen::MatrixXd R;

	//block and sblock objects to store the test matrices
	sblock Ab;
	sblock Bb;
	sblock Rb;
	//Converting the test matrices to the block and sblock types
	{
		unsigned int Bpos = 0;//Sore the position of Bb elements
		for(unsigned int i = 0; i < A.rows(); i++){
			for(unsigned int j = 0; j < A.cols(); j++){
				if(j >= i){
					Bb.data[Bpos] = S(i,j);
					Ab.data[Bpos] = A(i,j);
				}
			}
		}
	}

	//Multiplying the matrices using Eigen library
	R = S*A;
	//Multiplying the matrices using multiplyds library
	multiplyss(&Bb, &Ab, &Rb);


	std::cout << "\n\n********************Testing mulplyss*****************\n" << std::endl;
	std::cout << "Input matrices, S and A, symmetric dense and dense, respectively:" << std::endl;
	std::cout << S << "\n" << std::endl;
	std::cout << A << std::endl;

	std::cout << "Eigen output is" << std::endl;
	std::cout << R << std::endl;

	std::cout << "multiplyss output is" << std::endl;
	printsblock(Rb);

}

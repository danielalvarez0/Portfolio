/*
*LFSR.hpp
*Author: Daniel Alvarez
*Created on: 10/07/17
*/

#ifndef LFSR_HPP_
#define LFSR_HPP_
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <vector>
class LFSR 
{
	
public: 
		LFSR(std::string seed, int t);

		int step(); // perform one step and return new rightmost bit as int 

		int generate(int k); // simulate k steps and return a kit bit integer as a decimal number

		std::string toString(); // return the LFSR object as a string
		
		int getTap() {return tap;}

private:
		std::vector<int> bitVec;
		int tap;
};
#endif

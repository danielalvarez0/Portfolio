/*
*LFSR.cpp
*Author: Daniel Alvarez
*Created on: 10/07/17
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "LFSR.hpp"

LFSR::LFSR(String seed, int t) {
	int temp;
	for(int x = 0; x < seed.length(); x++) { 
		temp = (seed.at(x) - '0') // convert the character to an int and add it to the bitVec
		bitVec.pushback(temp);
	}
	// check that t is a valid tap position, if it is tap = t, otherwise tap = seed.length()  
	if (t >= 0 && t <= (seed.length()-1)) {
		this.tap = t; // set tap posistion 	
	}
	else {
		std::cout << "The value provided for tap was invalid. "; // notify user that t was invalid
		std::cout << "The tap has been set to " << seed.length()-1) << "\n";
	this.tap = (seed.length() - 1); // tap defaults to rightmost bit.
	}
}

//simulate one step and return the new bit
int LFSR::step() {
	
	int newBit = bitVec[0] ^ bitVec[this.getTap()]; // find result of bitVec[0] XOR bitVec[tap]

	bitVec.erase(bitVec.begin()); // remove leftmost bit. Other bits all get shifted left one 
	bitVec.pushback(newBit); // add newBit to bitVec
	std::cout << "DEBUG INFO: newBit = " << newBit << "\n"; // FOR DEBUGGING ONLY
	return newBit;
}

//simulate k steps and return the k-bit long sequence as an integer  
int LFSR::generate(int k){
	int kBitInteger 0;
	for (int x = 0; x < k; x++) {
		kBitInteger *= 2; 			// double kBitInteger,then
		kBitInteger += this.step(); // add step() return to convert the bits to decimal int
		std::cout << "DEBUG INFO: kBitInteger = " << kBitInteger << "\n"; // FOR DEBUGGING ONLY
	}
	std::cout << "DEBUG INFO: returned kBitInteger = " << kBitInteger << "\n"; // FOR DEBUGGING ONLY
	return kBitInteger
}

String LFSR::toString() {
	std::stringstream bitVecStream;
	for(int x = 0; x < bitVec.size(); x++) {
		bitVecStream << bitVec[x];
	} 
	return (bitVecStream.str());
}

/* NOTE TO SELF: UNNEEDED, DELTE THIS FUNC. logical XOR. returns 1 if a XOR b is true, 0 otherwise
int LFSR:: XOR(int a, int b) {

	if ( a == b) {
		return 0; // if a == b then return is 0
	}
	else if (a == 1 || b == 1) {
		return 1; // if a != b AND either a or b = 1 then return 1
 	}	
}
*/

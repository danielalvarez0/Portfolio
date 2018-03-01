Name: Daniel Alvarez
LFSR representation:
	 I used a vector of ints as my register of bits. In the constructor a for loop grabs each character in the string, converts it to an int, and then adds it to the vector using pushback(). When step() is called it first finds and stores the result of bit[0] XOR bit[tap] (note: bit[0] is the leftmost bit) in a temporary int variable. Then I call the erase(myVector.begin()) to remove the current leftmost bit and use pushback(the_temporary_int_variable) to add the new rightmost bit. I chose to use a vector because they are easy to resize and because using the erase() and pushback() functions means that when I remove the leftmost bit all the other bits have their positions shifted automatically which is much easier for me.

Additional test 1:
	This test  checks that the constructor correctly sets tap to the rightmost bit if the value recieved in not a valid value for tap. 

Additional test 2:
	This test Checks that my code functions correctly when the seed is only a single bit. (the code won't provide any useful output, step() will always return a 0, but the code should run successfully and without errors). 

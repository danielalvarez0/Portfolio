/*
*boosttest.cpp 
*Modified by: Daniel Alvarez -note: This is the boosttest file posted on the blackboard site with
*	some additional tests added. This was not written solely by me and I am not claiming full
* 	ownership.
*	
*	TLDR: I took the example boosttest from blackboard and added some things. 
*		  I am not trying to plagiarize.
*Last Modified on: 10/12/17
*/

#include "LFSR.hpp"
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(fiveBitsTapAtTwo) {

	LSFR lsfr1("00111", 2);
	BOOST_REQUIRE(lsfr1.step() == 1);
	BOOST_REQUIRE(lsfr1.step() == 1);
	BOOST_REQUIRE(lsfr1.step() == 0);
	BOOST_REQUIRE(lsfr1.step() == 0);
	BOOST_REQUIRE(lsfr1.step() == 0);
	BOOST_REQUIRE(lsfr1.step() == 1);
	BOOST_REQUIRE(lsfr1.step() == 1);
	BOOST_REQUIRE(lsfr1.step() == 0);

	LSFR lsfr2("00111", 2);	
	BOOST_REQUIRE(lsfr2.generate(8) == 198);
}
// Additional test 1
BOOST_AUTO_TEST_CASE(fiveBitsTapOutOfBounds) {
	LSFR lsfr3("00111", 5); //5 is not a valid value for tap. Greatest possible value is 4.
	BOOST_REQUIRE(lsfr3.getTap() == 4);// tap should default to rightmost bit

	LSFR lsfr3("00111", -1); //-1 is not a valid value for tap. Lowest possible value is 0.
	BOOST_REQUIRE(lsfr3.getTap() == 4);// tap should default to rightmost bit
}

// Additional test 2
BOOST_AUTO_TEST_CASE(oneBitTapZero) {
	LSFR lsfr4("1", 1);
	BOOST_REQUIRE(lsfr4.step() == 0); 
	BOOST_REQUIRE(lsfr4.step() == 0); 

}

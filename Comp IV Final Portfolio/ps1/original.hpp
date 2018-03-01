/* original.hpp
*Author: Daniel Alvarez
* created on: 9/24/17
*/

#ifndef ORIGINAL_HPP_
#define ORIGINAL_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp>
class original : public sf::Drawable 
{

public:
	// constructor: inputs are recursion depth and side length of square
	original(int depth, int sideLength, sf::Vector2f pos);
	~original();  // destructor

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;	
	sf::RectangleShape _square; 
	int _depth; //depth of this square

	original* ULchild;  
	original* UMchild;
	original* URchild;
	original* MLchild;
	original* MRchild;
	original* BLchild;  
	original* BMchild;
	original* BRchild;
};
#endif

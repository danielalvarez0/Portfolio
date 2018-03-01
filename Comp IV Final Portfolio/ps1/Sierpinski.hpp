/* Sierpinski.hpp
*Author: Daniel Alvarez
* created on: 9/17/17
*/

#ifndef SIERPINSKI_HPP_
#define SIERPINSKI_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp>
class Sierpinski : public sf::Drawable 
{

public:
	// constructor: inputs are recursion depth and vectors containing coords of 3 corner points
	Sierpinski(int depth, sf::Vector2f top, sf::Vector2f right, sf::Vector2f left);
	~Sierpinski();  // destructor

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;	
	sf::ConvexShape _tri; // triangle object
	int _depth; //depth of this triangle

	sf::Vector2f top; // co-ords of top point
	sf::Vector2f right; // co-ords of right point
	sf::Vector2f left; // co-ords of left point

	// triangles that make up the next level of the fratal
	Sierpinski* topChild;  
	Sierpinski* rightChild;
	Sierpinski* leftChild;
};
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Sierpinski.hpp"

void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(_tri);
	if (topChild != NULL) {
		topChild->draw(target, states);
		rightChild->draw(target, states);
		leftChild->draw(target, states);
	}

}

// Constructor for the first level of the fractal
/* builds an isosceles triangle sized to fill the window
Sierpinski::Sierpinski(int depth, sf::Vector2f winSize) {

	_depth = depth;
	_tri.setPointCount(3);
	_tri.setPoint(0, sf::Vector2f(winSize.x/2, 0));
	_tri.setPoint(1, sf::Vector2f(winSize.x, winSize.y));
	_tri.setPoint(2, sf::Vector2f(0, winSize.y));
	switch(_depth % 5) {
	case 0 : 
	_tri.setFillColor(sf::Color::White);
		break;
	case 1 : 
	_tri.setFillColor(sf::Color::Red);
		break;
	case 2 : 
	_tri.setFillColor(sf::Color::Magenta);
		break;
	case 3 : 
	_tri.setFillColor(sf::Color::Green);
		break;
	case 4 : 
	_tri.setFillColor(sf::Color::Yellow);
		break;
	default: 
	_tri.setFillColor(sf::Color::Blue);
		break;
	}
	int nextDepth = depth - 1;// decrement depth and check if children  should be null
	if (0 == nextDepth) {
		topChild = nullptr;	
		rightChild = nullptr;	
		leftChild = nullptr;
	}
	else {
	sf::Vector2f midTR = ( 3 *(winSize.x)/4, winSize.y/2); //  midpoint of top and right
	sf::Vector2f midTL = ( (winSize.x)/4, winSize.y/2); //  midpoint of top and left
	sf::Vector2f midLR = ( winSize.x/2, winSize.y); //  midpoint of left and right

	topChild = new Sierpinski(nextDepth, sf::Vector2f(winSize.x/2, 0), midTR, midTL);
	rightChild = new Sierpinski(nextDepth, midTR, sf::Vector2f(winSize.x, winSize.y), midLR);
	leftChild = new Sierpinski(nextDepth, midTL, midLR, sf::Vector2f(0, winSize.y));
	}
}
*/
// creates a Sierpinski triangle fractal.
// depth is recursion depth. top, right, and left are vectors containing
// the x-y coordinates of the points of the triangle
Sierpinski::Sierpinski(int depth, sf::Vector2f top, sf::Vector2f right, sf::Vector2f left)
{
	_depth = depth;
	_tri.setPointCount(3);
	_tri.setPoint(0,top);		
	_tri.setPoint(1,right);
	_tri.setPoint(2,left);	
	switch(_depth % 5) {
	case 0 : 
	_tri.setFillColor(sf::Color::White);
		break;
	case 1 : 
	_tri.setFillColor(sf::Color::Red);
		break;
	case 2 : 
	_tri.setFillColor(sf::Color::Magenta);
		break;
	case 3 : 
	_tri.setFillColor(sf::Color::Green);
		break;
	case 4 : 
	_tri.setFillColor(sf::Color::Yellow);
		break;
	default: 
	_tri.setFillColor(sf::Color::Blue);
		break;
	}
	int nextDepth = depth - 1;// decrement depth and check if children  should be null
	if (0 == nextDepth) {
		topChild = NULL;	
		rightChild = NULL;
		leftChild = NULL;
	}
	else {
	sf::Vector2f midTR((right.x + top.x)/2, (right.y + top.y)/2); //  midpoint of top and right
	sf::Vector2f midTL((left.x + top.x)/2, (left.y + top.y)/2); //  midpoint of top and left
	sf::Vector2f midLR((right.x + left.x)/2, left.y); //  midpoint of left and right
	
	topChild = new Sierpinski(nextDepth, top, midTR, midTL);
	rightChild = new Sierpinski(nextDepth, midTR, right, midLR);
	leftChild = new Sierpinski(nextDepth, midTL, midLR, left);
	}
}

// destructor
Sierpinski::~Sierpinski() {
	if (topChild != NULL) {
		delete(topChild);
		delete(rightChild);
		delete(leftChild);
	}
}


int main(int argc, char* argv[])
{
//argv[1] = depth,  argv[2]= window size
if (argc != 3) {
	std::cout << "Invalid number of arguments. please come back when you have 2 arguments." <<"\n"; 
	//system("pause");
	return 0;
}
else {
	int winSideLength = atoi(argv[2]);
	sf::RenderWindow window(sf::VideoMode(winSideLength, winSideLength), "Sierpinski fractal");
   	
	sf::Vector2f top(winSideLength/2,0);	
	sf::Vector2f right(winSideLength, winSideLength);
	sf::Vector2f left(0, winSideLength);
	Sierpinski fractal(atoi(argv[1]), top, right, left);
	while (window.isOpen())
    	{	
      		sf::Event event;
        	while (window.pollEvent(event))
        	{
			if (event.type == sf::Event::Closed)
			{
	                window.close();
			}
		}
        window.clear();
        window.draw(fractal);
        window.display();
    	}
    return 0;
   }
}

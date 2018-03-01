#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "original.hpp"

void original::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
	target.draw(_square);
	if (URchild != NULL) {
		ULchild->draw(target, states);
		UMchild->draw(target, states);
		URchild->draw(target, states);
		MLchild->draw(target, states);
		MRchild->draw(target, states);
		BLchild->draw(target, states);
		BMchild->draw(target, states);
		BRchild->draw(target, states);
	}
}

// creates a sierpinski carpet
// depth is recursion depth. side is side length and pos is the coords of the top left corner
original::original(int depth, int side,sf::Vector2f pos)
{
	_depth = depth;
	_square.setSize(sf::Vector2f(side, side));
	_square.setPosition(pos);
	_square.setFillColor(sf::Color::White);
	int nextDepth = depth - 1;// decrement depth and check if children  should be null
	if (0 == nextDepth) {
		ULchild = NULL;
		UMchild = NULL;
		URchild = NULL;
		MLchild = NULL;
		MRchild = NULL;
		BLchild = NULL;
		BMchild = NULL;
		BRchild = NULL;
	}
	else {
		ULchild = new original(nextDepth, side/3, sf::Vector2f(pos.x-(2*side/3),(pos.y-2*side/3)));
		UMchild = new original(nextDepth, side/3, sf::Vector2f(pos.x+(side/3),(pos.y-(2*side/3))));
		URchild = new original(nextDepth, side/3, sf::Vector2f((pos.x+(4*side/3)),(pos.y-(2*side/3))));
		MLchild = new original(nextDepth, side/3, sf::Vector2f((pos.x-(2*side/3)),pos.y+(side/3)));
		MRchild = new original(nextDepth, side/3, sf::Vector2f((pos.x+(4*side/3)),pos.y+(side/3)));
		BLchild = new original(nextDepth, side/3, sf::Vector2f((pos.x-(2*side/3)),(pos.y+(4*side/3))));
		BMchild = new original(nextDepth, side/3, sf::Vector2f(pos.x+(side/3),(pos.y+(4*side/3))));
		BRchild = new original(nextDepth, side/3, sf::Vector2f((pos.x+(4*side/3)),(pos.y+(4*side/3))));
	}
}

// destructor
original::~original() {
	if (ULchild != NULL) {
		delete(ULchild);
		delete(UMchild);
		delete(URchild);
		delete(MLchild);
		delete(MRchild);
		delete(BLchild);
		delete(BMchild);
		delete(BRchild);
	}
}


int main(int argc, char* argv[])
{
//argv[1] = depth,  argv[2]= window size
if (argc != 3) {
	std::cout << "Invalid number of arguments. please come back when you have 2 arguments." <<"\n"; 
	return 0;
}
else {
	int winSideLength = atoi(argv[2]);
	sf::RenderWindow window(sf::VideoMode(winSideLength, winSideLength), "original fractal");
	
	original fractal(atoi(argv[1]), winSideLength/3,sf::Vector2f(winSideLength/3,winSideLength/3));
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

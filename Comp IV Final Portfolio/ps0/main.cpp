#include <SFML/Graphics.hpp>

int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML first homework");
    //sf::CircleShape shape(100.f);
    //shape.setFillColor(sf::Color::Green);
	sf::Texture tex;
	tex.loadFromFile("./sprite.png");	
	sf::Sprite sprite;
	sprite.setTexture(tex);	
	sprite.setPosition(101, 400);
	//int countRight = 0;
	//int countLeft = 0;
	bool goRight = true; // tells the sprite which direction to move
    while (window.isOpen())
    {	
	if (goRight) {
		//sprite.move(9,0);
		sprite.setPosition(sprite.getPosition().x + 9,0);
	}
	else {
		sprite.setPosition(sprite.getPosition().x - 9, 0);
	}
	// check if direction should reverse
	if (goRight && sprite.getPosition().x >=600) {
	goRight = false;
	}
	else if (!goRight && sprite.getPosition().x <= 100) {
		goRight = true;
	}

        sf::Event event;
        while (window.pollEvent(event))
        {
		if (event.type == sf::Event::Closed){
	                window.close();
		}
		// makes sprite scale change in response to up and down arrow keys
		
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up){
			sprite.scale(1.5,1.5);
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down){
			sprite.scale(0.6666,0.6666);
		}
		//This is my "Something else" When the window is resized the sprite rotates 45 degrees
		else if (event.type == sf::Event::Resized) {
			sprite.rotate(45);
		}        
	}

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

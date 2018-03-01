// using SFML to load a file, manipulate its pixels, write it to disk


#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>
#include "LFSR.hpp"

using namespace std;
class PhotoMagic {
public:
	sf::Image transform(sf::Image pic, LFSR lfsr)
	{
		// p is a pixel
		sf::Color p;
		
		sf::Vector2u size = pic.getSize();
		for (int x = 0; x < (int)size.x; x++) {
			for (int y = 0; y < (int)size.y; y++) {
				int redNum = lfsr.generate(8);
				int greenNum = lfsr.generate(8);
				int blueNum = lfsr.generate(8);
				p = pic.getPixel(x, y);
				p.r = p.r ^ redNum;
				p.g = p.g ^ greenNum;
				p.b = p.b ^ blueNum;
				pic.setPixel(x, y, p);
			}
		}
		return pic;
}
};
	int main(int argc, char* argv[])
	{
		string inputfile = argv[1];
		string outputfile = argv[2];
		string seed = argv[3];
		int tap = atoi(argv[4]);
		PhotoMagic pm ;
		LFSR lfsr(seed, tap);

		sf::Image inImage;
		sf::Image outImage;
		if (!inImage.loadFromFile(inputfile))
			return -1;
		outImage = pm.transform(inImage, lfsr);

		sf::Vector2u size = inImage.getSize();
		sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Input Image");
		sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Output Image");
		sf::Texture texture1;
		sf::Texture texture2;
		texture1.loadFromImage(inImage);
		texture2.loadFromImage(outImage);

		sf::Sprite sprite1;
		sprite1.setTexture(texture1);
		
		sf::Sprite sprite2;
		sprite2.setTexture(texture2);

		while (window1.isOpen() && window2.isOpen()) {
			sf::Event event;
			while (window1.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window1.close();
			}
			while (window2.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window2.close();
			}
			window1.clear();
			window1.draw(sprite1);
			window1.display();
			window2.clear();
			window2.draw(sprite2);
			window2.display();
			sleep(1);
		}

		//   write the file
		if (!outImage.saveToFile(outputfile))
			return -1;

		return 0;
	}


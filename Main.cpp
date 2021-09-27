#include <iostream>
#include "Frame.h"

int main()
{
	const sf::Vector2<unsigned int> frameSize{ 1000, 1000 };
	const sf::Vector2<unsigned int> gridSize{ 20, 20 };

	Frame* mainFrame = new Frame(frameSize, "Game Of Life", gridSize);

	return 0;
}
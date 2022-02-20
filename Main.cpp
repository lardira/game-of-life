#include <iostream>
#include "Frame.h"

/*Rules
	For a space that is populated:
	*Each cell with one or no neighbors dies, as if by solitude.
	*Each cell with four or more neighbors dies, as if by overpopulation.
	*Each cell with two or three neighbors survives.

	For a space that is empty or unpopulated:
	*Each cell with three neighbors becomes populated.*/

int main()
{
	const sf::Vector2<unsigned int> frameSize{ 1000, 1000 };
	const sf::Vector2<unsigned int> gridSize{ 50, 50 };

	Frame* mainFrame = new Frame(frameSize, "Game Of Life", gridSize);

	return 0;
}
#pragma once
#include <SFML/Graphics.hpp>

#include "Grid.h"

class Frame
{
public:
	Frame(sf::Vector2<unsigned int> frameSize, sf::String frameTitle, sf::Vector2<unsigned int> gridSize);
	~Frame();

	sf::Vector2<int> GetMousePosition(sf::RenderWindow* window);

private:
	void PollEvents(sf::RenderWindow* window);
	void RunGame(sf::RenderWindow* window);

	bool isSimulating = false;
	sf::RenderWindow* window = nullptr;
	const sf::Vector2<unsigned int> headerSize{ 7, 30 }; // based on Window's windows' headers toolbars
	sf::Vector2<unsigned int> frameSize;
	Grid grid;
};

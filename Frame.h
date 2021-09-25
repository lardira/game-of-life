#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"

class Frame
{
private:
	sf::Vector2<unsigned int> frameSize;
	const sf::Vector2<unsigned int> headerSize{ 7, 30 }; // based on Window's windows' headers toolbars
	Grid grid;
public:
	Frame();
	~Frame() = default;
	Frame(sf::Vector2<unsigned int> frameSize, sf::String frameTitle, sf::Vector2<unsigned int> gridSize);

	sf::Vector2<int> GetMousePosition(sf::RenderWindow& window);
	
private:
	void PollEvents(sf::RenderWindow& window);
};


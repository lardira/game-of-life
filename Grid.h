#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Grid
{
private:
	sf::Vector2<unsigned int> gridSize;

	struct Cell
	{
		sf::Color currentColor = sf::Color::Black;
	};

public:
	Grid();
	~Grid() = default;
	Grid(sf::Vector2<unsigned int> gridSize);

	sf::Vector2<int> GetCell(sf::Vector2<unsigned int>& frameSize, sf::Vector2<int>& mousePos);
};


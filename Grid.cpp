#include "Grid.h"

Grid::Grid(sf::Vector2<unsigned int> gridSize = { 10, 10 })
	: gridSize(gridSize)
{
}

Grid::Grid()
	: gridSize( 10, 10 )
{
}

sf::Vector2<int> Grid::GetCell(sf::Vector2<unsigned int>& frameSize, sf::Vector2<int>& mousePos)
{
	int x = std::lround((float)mousePos.x / (float)frameSize.x * gridSize.x); 
	int y = std::lround((float)mousePos.y / (float)frameSize.y * gridSize.y);
	sf::Vector2<int> cellPos {x, y};
	return cellPos;
}

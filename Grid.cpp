#include "Grid.h"

Grid::Grid(sf::Vector2<unsigned int> gridSize = { 10, 10 }, sf::Vector2<unsigned int> frameSize = { 800, 800 })
	: gridSize(gridSize), frameSize(frameSize)
{
	cellSize = { (float)(frameSize.x / gridSize.x - lineSize), (float)(frameSize.y / gridSize.y - lineSize)};
}

Grid::Grid()
	: gridSize( 10, 10 ), frameSize( 800, 800 )
{
	cellSize = { (float)(frameSize.x / gridSize.x - lineSize), (float)(frameSize.y / gridSize.y - lineSize)};
}

sf::Vector2<int> Grid::GetCell(sf::Vector2<int>& mousePos) const 
{
	int x = std::lround((float)mousePos.x / (float)frameSize.x * gridSize.x); 
	int y = std::lround((float)mousePos.y / (float)frameSize.y * gridSize.y);
	sf::Vector2<int> cellPos {x, y};
	return cellPos;
}

sf::Vector2<float> Grid::GetCellPosition(sf::Vector2<int> cell) const
{
	return { (float)(cell.x * frameSize.x / gridSize.x), (float)(cell.y * frameSize.y / gridSize.y)};
}

sf::Vector2<unsigned int> Grid::GetGridSize() const
{
	return gridSize;
}

std::vector<Grid::Cell> Grid::GetCells()
{
	std::vector<Cell> cells;
	for (int a = 0; a < gridSize.x; a++)
		for (int b = 0; b < gridSize.y; b++)
		{
			Grid::Cell cell;
			cell.size = cellSize;
			cell.cellShape = sf::RectangleShape{ cell.size };
			cell.positon = GetCellPosition(sf::Vector2i(a, b));
			cell.cellShape.setPosition(cell.positon);
			cell.cellShape.setFillColor(cell.currentColor);
			cells.push_back(cell);
		}
	return cells;
}
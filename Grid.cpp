#include "Grid.h"

Grid::Grid(sf::Vector2<unsigned int> gridSize = { 10, 10 }, sf::Vector2<unsigned int> frameSize = { 800, 800 })
	: gridSize(gridSize), frameSize(frameSize)
{
	cellSize = { (float)(frameSize.x / gridSize.x - lineSize), (float)(frameSize.y / gridSize.y - lineSize) }; 
	FillCells(cells);
}

Grid::Grid()
	: gridSize( 10, 10 ), frameSize( 800, 800 )
{
	cellSize = { (float)(frameSize.x / gridSize.x - lineSize), (float)(frameSize.y / gridSize.y - lineSize)}; 
	FillCells(cells);
}

sf::Vector2<int> Grid::GetCellID(sf::Vector2<int>& mousePos) const 
{
	//TODO::get rid of this embarrasing shit
	int x = std::floor((float)mousePos.x / frameSize.x * (float)gridSize.x);
	int y = std::floor((float)mousePos.y / frameSize.y * (float)gridSize.y);
	sf::Vector2<int> cellID {x, y};
	return cellID;
}

void Grid::SetCellSize(sf::Vector2<float> newSize)
{
	for (auto& cell : cells)
		cell.size = newSize;
}

sf::Vector2<float> Grid::GetCellPosition(sf::Vector2<int> cell) const
{
	return { (float)(cell.x * frameSize.x / gridSize.x), (float)(cell.y * frameSize.y / gridSize.y)};
}

sf::Vector2<unsigned int> Grid::GetGridSize() const
{
	return gridSize;
}

Grid::Cell& Grid::GetCellByPos(sf::Vector2<int>& mousePos)
{
	return Grid::GetCellByID(Grid::GetCellID(mousePos));
}

void Grid::FillCells(std::vector<Grid::Cell>& cells)
{
	cells.clear();

	for (unsigned int a = 0; a < gridSize.x; a++)
		for (unsigned int b = 0; b < gridSize.y; b++)
		{
			Grid::Cell cell;
			cell.size = cellSize;
			cell.cellShape = sf::RectangleShape{ cell.size };
			cell.position = GetCellPosition(sf::Vector2i(a, b));
			cell.cellShape.setPosition(cell.position);
			cell.cellShape.setFillColor(cell.currentColor);
			cells.push_back(cell);
		}
}

std::vector<Grid::Cell>& Grid::GetCells()
{
	return cells;
}

Grid::Cell& Grid::GetCellByID(sf::Vector2<int> cellID)
{
	unsigned int id = cellID.x * gridSize.x + cellID.y;
	return cells[id];
}

void Grid::SetColor(Grid::Cell& cell, sf::Color color)
{
	cell.currentColor = color;
	cell.cellShape.setFillColor(color);
}

void Grid::SetState(Grid::Cell& cell, bool isAlive)
{
	cell.isAlive = isAlive;

	if (isAlive)
		Grid::SetColor(cell, cell.alive);
	else
		Grid::SetColor(cell, cell.dead);
}

void Grid::OnFrameResized(sf::Vector2<unsigned int> newFrameSize)
{
	frameSize = newFrameSize;
	Grid::SetCellSize({ (float)(frameSize.x / gridSize.x - lineSize), (float)(frameSize.y / gridSize.y - lineSize) });
}

void Grid::Simulate(bool state)
{

}
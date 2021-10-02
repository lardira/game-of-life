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
	return {(float)(cell.x * frameSize.x / gridSize.x), (float)(cell.y * frameSize.y / gridSize.y)};
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
			cell.id = { (int)a, (int)b };
			cells.push_back(cell);
		}
}

std::vector<Grid::Cell>& Grid::GetCells()
{
	return cells;
}

int Grid::CountAliveCells(Grid::Cell& cell)
{
	int count = 0;
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
		{
			int colToCheck = cell.id.x - 1 + col;
			int rowToCheck = cell.id.y - 1 + row;

			//check grid boundaries
			if (colToCheck < 0 || rowToCheck < 0) continue;
			if (colToCheck > gridSize.x - 1 || rowToCheck > gridSize.y - 1) continue;
			
			auto& checkedCell = GetCellByID({ colToCheck, rowToCheck });
			if (checkedCell.isAlive && checkedCell.id != cell.id)
				count++;
		}

	return count; //it shouldn't count itself
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

void Grid::Reset()
{
	for (auto& id : aliveCellsID)
	{
		auto& cell = GetCellByID(id);
		cell.isAlive = false;
		Grid::SetColor(cell, cell.dead);
	}
	aliveCellsID.clear();
}

void Grid::ChangeState(Grid::Cell& cell)
{
	cell.isAlive = !cell.isAlive;

	if (cell.isAlive)
	{
		Grid::SetColor(cell, cell.alive);
		aliveCellsID.push_back(cell.id);
		std::cout << "Added cell of: " << cell.id.x << ", " << cell.id.y << '\n';
	}
	else
	{
		Grid::SetColor(cell, cell.dead);
		auto result = std::find(aliveCellsID.begin(), aliveCellsID.end(), cell.id);
		if (result != aliveCellsID.end())
			aliveCellsID.erase(result);

		std::cout << "Deleted cell at: " << cell.id.x << ", " << cell.id.y << '\n';
	}
}

void Grid::OnFrameResized(sf::Vector2<unsigned int> newFrameSize)
{
	frameSize = newFrameSize;
	Grid::SetCellSize({ (float)(frameSize.x / gridSize.x - lineSize), (float)(frameSize.y / gridSize.y - lineSize) });
}


/*Rules
	For a space that is populated:
	*Each cell with one or no neighbors dies, as if by solitude.
	*Each cell with four or more neighbors dies, as if by overpopulation.
	*Each cell with two or three neighbors survives.

	For a space that is empty or unpopulated:
	*Each cell with three neighbors becomes populated.*/
void Grid::Simulate(bool isSimulating)
{
	std::vector<sf::Vector2i> cellsToPopulate, cellsToDie;

	if (isSimulating && aliveCellsID.size() > 0)
	{
		for (auto& cellID : aliveCellsID)
		{
			auto& cell = GetCellByID(cellID);
			
			//checks for cells to populate
			//(although extremely inefficient);
			for (int row = 0; row < 3; row++)
				for (int col = 0; col < 3; col++)
				{
					int colToCheck = cell.id.x - 1 + col;
					int rowToCheck = cell.id.y - 1 + row;

					//check grid boundaries
					if (colToCheck < 0 || rowToCheck < 0) continue;
					if (colToCheck > gridSize.x - 1 || rowToCheck > gridSize.y - 1) continue;

					auto& cellNearNeighbours = GetCellByID({ colToCheck, rowToCheck });
					if (CountAliveCells(cellNearNeighbours) == 3)
						cellsToPopulate.push_back(cellNearNeighbours.id);
				}

			//checks for cells to die
			int neighbours = CountAliveCells(cell);
			if (neighbours > 3 || neighbours < 2)
				cellsToDie.push_back(cell.id);
		}

		for (auto& id : cellsToDie)
			ChangeState(GetCellByID(id));
		for (auto& id : cellsToPopulate)
			ChangeState(GetCellByID(id));
	}
}
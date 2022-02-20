#pragma once
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

class Grid
{
public:
	struct Cell
	{
		const sf::Color alive = sf::Color::Black, dead = sf::Color::White;

		sf::RectangleShape cellShape;
		sf::Vector2i id;
		sf::Vector2f size;
		bool isAlive = false;
		sf::Color currentColor = dead;
	};

public:
	Grid();
	Grid(sf::Vector2<unsigned int> gridSize, sf::Vector2<unsigned int> frameSize);

	sf::Vector2<int> GetCellID(sf::Vector2<int>& mousePos) const;
	sf::Vector2<float> GetCellPosition(sf::Vector2<int> cell) const;
	sf::Vector2<unsigned int> GetGridSize() const;
	Grid::Cell& GetCellByID(sf::Vector2<int> cellID);
	Grid::Cell& GetCellByPos(sf::Vector2<int>& mousePos);
	std::vector<Cell>& GetCells();
	
	void SetCellSize(sf::Vector2<float> newSize);
	void SetColor(Cell& cell, sf::Color color);
	void ChangeState(Grid::Cell& cell);

	void OnFrameResized(sf::Vector2<unsigned int> newFrameSize);

	void Run(bool isSimulating);
	void Reset();

private:
	void FillCells(std::vector<Cell>& cells);
	int CountAliveCells(Cell& cell);

	sf::Vector2<unsigned int> gridSize;
	sf::Vector2<unsigned int> frameSize;

	int lineSize = 2;
	std::vector<Cell> cells;
	std::vector<sf::Vector2<int>> aliveCellsID;
	sf::Vector2<float> cellSize;
};


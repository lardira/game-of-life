#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Grid
{
public:
	struct Cell
	{
		const sf::Color alive = sf::Color::Black, dead = sf::Color::White;

		sf::RectangleShape cellShape;
		sf::Vector2f position{ 0.f, 0.f };
		sf::Vector2f size;
		bool isAlive = false;
		sf::Color currentColor = dead;
	};

private:
	sf::Vector2<unsigned int> gridSize;
	sf::Vector2<unsigned int> frameSize;

	int lineSize = 2;
	std::vector<Cell> cells;
	sf::Vector2<float> cellSize;

public:
	Grid();
	~Grid() = default;
	Grid(sf::Vector2<unsigned int> gridSize, sf::Vector2<unsigned int> frameSize);

	sf::Vector2<int> GetCellID(sf::Vector2<int>& mousePos) const;
	sf::Vector2<float> GetCellPosition(sf::Vector2<int> cell) const;
	sf::Vector2<unsigned int> GetGridSize() const;
	Grid::Cell& GetCellByID(sf::Vector2<int> cellID);
	Grid::Cell& GetCellByPos(sf::Vector2<int>& mousePos);
	std::vector<Cell>& GetCells();
	
	void SetCellSize(sf::Vector2<float> newSize);
	void SetColor(Cell& cell, sf::Color color);
	void SetState(Grid::Cell& cell, bool isAlive);

	void OnFrameResized(sf::Vector2<unsigned int> newFrameSize);

	void Simulate(bool state);

private:
	void FillCells(std::vector<Cell>& cells);
};


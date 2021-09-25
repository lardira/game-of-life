#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Grid
{
private:
	sf::Vector2<unsigned int> gridSize;
	sf::Vector2<unsigned int> frameSize;

	sf::Vector2<float> cellSize;
	int lineSize = 2;

public:
	struct Cell
	{
		enum State
		{
			Alive = 1,
			Dead = 0
		};

		State currentState = Dead;
		sf::RectangleShape cellShape;
		sf::Vector2f positon{ 0.f, 0.f };
		sf::Vector2f size;
		sf::Color currentColor = sf::Color::White;
	};

	Grid();
	~Grid() = default;
	Grid(sf::Vector2<unsigned int> gridSize, sf::Vector2<unsigned int> frameSize);

	sf::Vector2<int> GetCell(sf::Vector2<int>& mousePos) const;
	sf::Vector2<float> GetCellPosition(sf::Vector2<int> cell) const;
	sf::Vector2<unsigned int> GetGridSize() const;
	std::vector<Cell> GetCells();
};


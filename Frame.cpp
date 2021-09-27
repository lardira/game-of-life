#include "Frame.h"
#include <iostream>

Frame::Frame(sf::Vector2<unsigned int> frameSize = { 800, 800 }, sf::String frameTitle = "Hello, there!", sf::Vector2<unsigned int> gridSize = { 10, 10 })
    : frameSize(frameSize), grid(gridSize, frameSize)
{
    sf::RenderWindow window(sf::VideoMode(frameSize.x, frameSize.y),  frameTitle);
    window.setFramerateLimit(15);

    while (window.isOpen())
    {
        PollEvents(window);

        window.clear();
        for (auto& cell : grid.GetCells())
            window.draw(cell.cellShape);
        window.display();

        grid.Simulate(isSimulating);
    }
}

void Frame::PollEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:
        {
            auto mousePos = GetMousePosition(window);
            Grid::Cell& cell = grid.GetCellByPos(mousePos);
            grid.SetState(cell, true);
            break;
        }

        case sf::Event::Resized:
            grid.OnFrameResized(window.getSize());
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
                isSimulating = !isSimulating;
            break;

        default:
            break;
        }
    }
}

sf::Vector2<int> Frame::GetMousePosition(sf::RenderWindow& window)
{
    int width = sf::Mouse::getPosition().x - window.getPosition().x - headerSize.x;
    int height = sf::Mouse::getPosition().y - window.getPosition().y - headerSize.y;
    return { width, height };
}
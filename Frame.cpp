#include <iostream>

#include "Frame.h"

Frame::Frame(sf::Vector2<unsigned int> frameSize = { 800, 800 },
             sf::String frameTitle = "Game Of Life", 
             sf::Vector2<unsigned int> gridSize = { 30, 30 })
    : frameSize(frameSize), grid(gridSize, frameSize)
{
    window = new sf::RenderWindow(sf::VideoMode(frameSize.x, frameSize.y),  frameTitle);
    window->setFramerateLimit(10);
    RunGame(window);
}

Frame::~Frame()
{
    delete(window);
}

void Frame::RunGame(sf::RenderWindow* window)
{
    while (window->isOpen())
    {
        PollEvents(window);

        window->clear();
        for (auto& cell : grid.GetCells())
            window->draw(cell.cellShape);
        window->display();

        grid.Run(isSimulating);
    }
}

void Frame::PollEvents(sf::RenderWindow* window)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window->close();
            break;

        case sf::Event::MouseButtonPressed:
        {
            auto mousePos = GetMousePosition(window);
            Grid::Cell& cell = grid.GetCellByPos(mousePos);
            grid.ChangeState(cell);
            break;
        }

        case sf::Event::Resized:
            grid.OnFrameResized(window->getSize());
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
                isSimulating = !isSimulating;
            if (event.key.code == sf::Keyboard::R)
            {
                Frame::isSimulating = false;
                grid.Reset();
            }
            break;

        default:
            break;
        }
    }
}

sf::Vector2<int> Frame::GetMousePosition(sf::RenderWindow* window)
{
    int width = sf::Mouse::getPosition().x - window->getPosition().x - headerSize.x;
    int height = sf::Mouse::getPosition().y - window->getPosition().y - headerSize.y;
    return { width, height };
}
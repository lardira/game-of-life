#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Logger
{
private:
	int loggerLevel = 0;
public:
	Logger() = default;
	~Logger() = default;

	template<typename T>
	static inline void PrintVector(std::string name, sf::Vector3<T> vector);
	template<typename T>
	static inline void PrintVector(std::string name, sf::Vector2<T> vector);

	template<typename T>
	static inline void PrintVector(sf::Vector3<T> vector);
	template<typename T>
	static inline void PrintVector(sf::Vector2<T> vector);
};

template<typename T>
static inline void Logger::PrintVector(std::string name, sf::Vector3<T> vector)
{
	std::cout << name << " ";
	std::cout << '(' << vector.x << ", " << vector.y << ", " << vector.z << ')' << '\n';
}

template<typename T>
static inline void Logger::PrintVector(std::string name, sf::Vector2<T> vector)
{
	std::cout << name << " ";
	std::cout << '(' << vector.x << ", " << vector.y << ')' << '\n';
}

template<typename T>
static inline void Logger::PrintVector(sf::Vector3<T> vector)
{
	std::cout << '(' << vector.x << ", " << vector.y << ", " << vector.z << ')' << '\n';
}

template<typename T>
static inline void Logger::PrintVector(sf::Vector2<T> vector)
{
	std::cout << '(' << vector.x << ", " << vector.y << ')' << '\n';
}
